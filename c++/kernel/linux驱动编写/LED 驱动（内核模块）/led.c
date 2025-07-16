#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/version.h>

#define LED_GPIO 12               // LED连接的GPIO引脚
#define DEVICE_NAME "led_device"  // 设备名称
#define CLASS_NAME "led_class"    // 类名称

static dev_t dev_num;             // 设备号
static struct cdev led_cdev;      // 字符设备结构
static struct class *led_class;   // 设备类
static struct device *led_device; // 设备实例

// 打开设备
static int led_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "LED device opened\n");
    return 0;
}

// 关闭设备
static int led_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "LED device closed\n");
    return 0;
}

// 写入数据（控制LED亮灭）
static ssize_t led_write(struct file *filp, const char __user *buf,
                         size_t count, loff_t *f_pos) {
    char c;
    
    if (count < 1)
        return -EINVAL;
    
    // 从用户空间复制数据
    if (copy_from_user(&c, buf, 1))
        return -EFAULT;
    
    // 根据输入控制LED
    if (c == '1') {
        gpio_set_value(LED_GPIO, 1);  // 点亮LED
        printk(KERN_INFO "LED turned on\n");
    } else if (c == '0') {
        gpio_set_value(LED_GPIO, 0);  // 熄灭LED
        printk(KERN_INFO "LED turned off\n");
    } else {
        return -EINVAL;  // 无效输入
    }
    
    return 1;  // 成功写入1字节
}

// 文件操作结构体（关联write等函数）
static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .write = led_write,  // 绑定write函数
};

// 初始化函数
static int __init led_init(void) {
    int ret;
    
    // 1. 请求GPIO
    ret = gpio_request(LED_GPIO, "led");
    if (ret) {
        printk(KERN_ERR "Failed to request GPIO %d\n", LED_GPIO);
        return ret;
    }
    
    // 2. 设置GPIO为输出，初始低电平（LED灭）
    ret = gpio_direction_output(LED_GPIO, 0);
    if (ret) {
        printk(KERN_ERR "Failed to set GPIO %d direction\n", LED_GPIO);
        gpio_free(LED_GPIO);
        return ret;
    }
    
    // 3. 分配设备号（动态分配）
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate device number\n");
        gpio_free(LED_GPIO);
        return ret;
    }
    
    // 4. 初始化字符设备
    cdev_init(&led_cdev, &led_fops);
    led_cdev.owner = THIS_MODULE;
    
    // 5. 添加字符设备到系统
    ret = cdev_add(&led_cdev, dev_num, 1);
    if (ret < 0) {
        printk(KERN_ERR "Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        gpio_free(LED_GPIO);
        return ret;
    }
    
    // 6. 创建设备类
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0)
    led_class = class_create(CLASS_NAME);
#else
    led_class = class_create(THIS_MODULE, CLASS_NAME);
#endif
    if (IS_ERR(led_class)) {
        printk(KERN_ERR "Failed to create class\n");
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        gpio_free(LED_GPIO);
        return PTR_ERR(led_class);
    }
    
    // 7. 创建设备节点（/dev/led_device）
    led_device = device_create(led_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(led_device)) {
        printk(KERN_ERR "Failed to create device\n");
        class_destroy(led_class);
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        gpio_free(LED_GPIO);
        return PTR_ERR(led_device);
    }
    
    printk(KERN_INFO "LED driver initialized (GPIO %d)\n", LED_GPIO);
    return 0;
}

// 退出函数
static void __exit led_exit(void) {
    // 清理资源
    device_destroy(led_class, dev_num);
    class_destroy(led_class);
    cdev_del(&led_cdev);
    unregister_chrdev_region(dev_num, 1);
    gpio_set_value(LED_GPIO, 0);  // 退出时关闭LED
    gpio_free(LED_GPIO);
    printk(KERN_INFO "LED driver exited\n");
}

// 模块入口/出口
module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple GPIO LED driver");