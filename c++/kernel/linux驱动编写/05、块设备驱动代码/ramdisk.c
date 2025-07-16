/*******************************************************************************
* 文 件 名: char.c
* 文件描述: linux驱动编写（块设备驱动代码）
* 备    注: 基于内存的块设备驱动程序，模拟了多个虚拟硬盘
*           新内核已全面采用 Multi-Queue Block I/O (blk-mq) 架构，传统的 request_fn 机制已被弃用
* 作    者: HanKin
* 创建日期: 2025.07.15
* 修改日期：2025.07.15
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
 
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/vmalloc.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>

#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/blkdev.h>
#include <linux/genhd.h>
 
#define RAMHD_NAME "ramhd"
#define RAMHD_MAX_DEVICE 2
#define RAMHD_MAX_PARTITIONS 4

// 采用 CHS（柱面 - 磁头 - 扇区）寻址模型（256 柱面 ×4 磁头 ×16 扇区）
#define RAMHD_SECTOR_SIZE 512
#define RAMHD_SECTORS 16
#define RAMHD_HEADS 4
#define RAMHD_CYLINDERS 256
 
#define RAMHD_SECTOR_TOTAL (RAMHD_SECTORS * RAMHD_HEADS *RAMHD_CYLINDERS)
#define RAMHD_SIZE (RAMHD_SECTOR_SIZE * RAMHD_SECTOR_TOTAL) //8mb

typedef struct {
    unsigned char* data;          // 存储设备数据的内存指针
    struct request_queue* queue;  // 请求队列
    struct gendisk* gd;           // 通用磁盘结构
} RAMHD_DEV;

// 存储所有设备的数据缓冲区
static char* sdisk[RAMHD_MAX_DEVICE] = {NULL};

// 指向各设备的管理结构
static RAMHD_DEV* rdev[RAMHD_MAX_DEVICE] = {NULL};

static dev_t ramhd_major;
 
static int ramhd_space_init(void)
{
    int i;
    int err = 0;
    for (i = 0; i < RAMHD_MAX_DEVICE; i++) {
        sdisk[i] = vmalloc(RAMHD_SIZE);
        if(!sdisk[i]){
            err = -ENOMEM;
            return err;
        }
        
        memset(sdisk[i], 0, RAMHD_SIZE);
    }
    
    return err;
}
 
static void ramhd_space_clean(void)
{
    int i;
    for (i = 0; i < RAMHD_MAX_DEVICE; i++) {
        vfree(sdisk[i]);
    }
}
 
static int ramhd_open(struct block_device* bdev, fmode_t mode)
{
    return 0;
}
 
static int ramhd_release(struct gendisk*gd, fmode_t mode)
{
    return 0;
}

// 处理HDIO_GETGEO命令，返回设备几何信息（CHS 参数）
static int ramhd_ioctl(struct block_device* bdev, fmode_t mode, unsigned int cmd, unsigned long arg)
{
    int err;
    struct hd_geometry geo;
    
    switch(cmd)
    {
        case HDIO_GETGEO:
            err = !access_ok(VERIFY_WRITE, arg, sizeof(geo));
            if(err)
                return -EFAULT;
                
            geo.cylinders = RAMHD_CYLINDERS;
            geo.heads = RAMHD_HEADS;
            geo.sectors = RAMHD_SECTORS;
            geo.start = get_start_sect(bdev);
            
            if(copy_to_user((void*)arg, &geo, sizeof(geo)))
                return -EFAULT;
            
            return 0;
    }
    
    return -ENOTTY;
}

// 块设备操作
static struct block_device_operations ramhd_fops = {
    .owner = THIS_MODULE,
    .open = ramhd_open,
    .release = ramhd_release,
    .ioctl = ramhd_ioctl,    // 处理设备控制命令
};

// 请求直接处理bio（块 I/O 请求）
static int ramhd_make_request(struct request_queue* q, struct bio* bio)
{
    char* pRHdata;
    char* pBuffer;
    struct bio_vec* bvec;
    int i;
    int err = 0;
    
    // 从bio获取扇区位置和数据方向
    struct block_device* bdev = bio->bi_bdev;
    RAMHD_DEV* pdev = bdev->bd_disk->private_data;
    
    if (((bio->bi_sector * RAMHD_SECTOR_SIZE) + bio->bi_size) > RAMHD_SIZE) {
        err = -EIO;
        return err;
    }

    pRHdata = pdev->data + (bio->bi_sector * RAMHD_SECTOR_SIZE);
    // 通过bio_for_each_segment遍历请求中的每个数据段
    bio_for_each_segment(bvec, bio, i) {
        pBuffer = kmap(bvec->bv_page) + bvec->bv_offset;    // 使用kmap映射物理页到内核虚拟地址
        switch(bio_data_dir(bio)){
            case READ:
                memcpy(pBuffer, pRHdata, bvec->bv_len); // 通过memcpy完成内存与用户缓冲区的数据传输
                flush_dcache_page(bvec->bv_page);
                break;
                
            case WRITE:
                flush_dcache_page(bvec->bv_page);
                memcpy(pRHdata, pBuffer, bvec->bv_len);
                break;
                
            default:
                kunmap(bvec->bv_page);
                goto out;
        }
        
        kunmap(bvec->bv_page);
        pRHdata += bvec->bv_len;
    }
    
out:
    bio_endio(bio, err);
    return 0;
}
 
static int alloc_ramdev(void)
{
    int i;
    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        rdev[i] = kzalloc(sizeof(RAMHD_DEV), GFP_KERNEL);
        if(!rdev[i]){
            return -ENOMEM;
        }
    }
    
    return 0;
}
 
static void clean_ramdev(void)
{
    int i;

    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        if(rdev[i]) {
            kfree(rdev[i]);
        }
    }
}

static int __init ramhd_init(void)
{
    int i;

    // 1. 分配内存空间
    ramhd_space_init();
    alloc_ramdev();
    
    // 2. 注册块设备（动态分配主设备号）
    ramhd_major = register_blkdev(0, RAMHD_NAME);
    
    // 3. 初始化每个设备（0 表示自动分配）
    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        rdev[i]->data = sdisk[i];
        // 设置请求队列
        rdev[i]->queue = blk_alloc_queue(GFP_KERNEL);
        blk_queue_make_request(rdev[i]->queue, ramhd_make_request);
        
        // 初始化通用磁盘结构
        rdev[i]->gd = alloc_disk(RAMHD_MAX_PARTITIONS);
        rdev[i]->gd->major = ramhd_major;
        rdev[i]->gd->first_minor = i * RAMHD_MAX_PARTITIONS;
        rdev[i]->gd->fops = &ramhd_fops;
        rdev[i]->gd->queue = rdev[i]->queue;
        rdev[i]->gd->private_data = rdev[i];
        sprintf(rdev[i]->gd->disk_name, "ramhd%c", 'a' +i);
        // 根据内核版本选择不同的方法
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0)
            // 新方法：使用 set_capacity() 的返回值
            set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
        #else
            // 旧方法：设置标志
            rdev[i]->gd->flags |= GENHD_FL_SUPPRESS_PARTITION_INFO;
        #endif
        set_capacity(rdev[i]->gd, RAMHD_SECTOR_TOTAL);
        // ...设置其他参数...
        add_disk(rdev[i]->gd);  // 向系统添加磁盘
    }
    
    return 0;
}
 
static void __exit ramhd_exit(void)
{
    int i;
    for(i = 0; i < RAMHD_MAX_DEVICE; i++){
        del_gendisk(rdev[i]->gd);  // 从系统移除磁盘
        put_disk(rdev[i]->gd);     // 减少引用计数
        blk_put_queue(rdev[i]->queue);  // 清理请求队列
    }
    
    clean_ramdev();          // 释放设备结构
    ramhd_space_clean();     // 释放内存空间
    unregister_blkdev(ramhd_major, RAMHD_NAME);  // 注销块设备
}
 
module_init(ramhd_init);
module_exit(ramhd_exit);
 
MODULE_AUTHOR("dennis__chen@ AMDLinuxFGL");
MODULE_DESCRIPTION("The ramdisk implementation with request function");
MODULE_LICENSE("GPL");