/*******************************************************************************
* 文 件 名: class.h
* 文件描述: 探究读写文件速度效率
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.16
* 修改日期：2025.04.16
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstdint>

class IUsbDeviceChannel {
public:
    // 这个必须在前面，否则error: ‘WriteCb’ has not been declared
    // WriteCb 被定义为一个指向函数的指针
    typedef void (*WriteCb)(void *priv, uint8_t *data, int32_t length);

    // 参数类型为 WriteCb *，这实际上是一个指向指针的指针。应该将其更改为 WriteCb
    void set_write_cb(WriteCb write_cb)
    {
        m_write_cb = write_cb;
    }

    virtual void execute_callback() = 0;    // 项目中不需要这一步，主要是为了调用子类中的私有函数
    
    WriteCb m_write_cb; // m_write_cb 应该是一个函数指针，而不是指向函数指针的指针
};

class UsbRedirChannel: public IUsbDeviceChannel {
public:
    UsbRedirChannel() { printf("%d:%s\n", __LINE__, __FUNCTION__); };
    ~UsbRedirChannel() { printf("%d:%s\n", __LINE__, __FUNCTION__); };

    void execute_callback() override
    {
        usbredir_write_cb();
    }

private:
    void usbredir_write_cb()
    {
        printf("%d:%s\n", __LINE__, __FUNCTION__);
        if (m_write_cb) {
            m_write_cb(NULL, (uint8_t *)"usbredir", 0);
        }
    }
};

class UsbVideoChannel: public IUsbDeviceChannel {
public:
    UsbVideoChannel() { printf("%d:%s\n", __LINE__, __FUNCTION__); };
    ~UsbVideoChannel() { printf("%d:%s\n", __LINE__, __FUNCTION__); };

    void execute_callback() override
    {
        usbvideo_write_cb();
    }

private:
    void usbvideo_write_cb()
    {
        printf("%d:%s\n", __LINE__, __FUNCTION__);
        if (m_write_cb) {
            m_write_cb(NULL, (uint8_t *)"usbvideo", 0);
        }
    }
};
