/*******************************************************************************
* 文 件 名: sequential_list_example.cpp
* 文件描述: 顺序表
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <cstdlib>
#include <typeinfo>
#include <cstdio>
#include <string.h>
#include <cassert>

#pragma pack(push)
#pragma pack(1)

struct uvc_streaming_control {
    uint16_t bmHint;
    uint8_t  bFormatIndex;
    uint8_t  bFrameIndex;
    uint32_t dwFrameInterval;
    uint16_t wKeyFrameRate;
    uint16_t wPFrameRate;
    uint16_t wCompQuality;
    uint16_t wCompWindowSize;
    uint16_t wDelay;
    uint32_t dwMaxVideoFrameSize;
    uint32_t dwMaxPayloadTransferSize;
    uint32_t dwClockFrequency; // UVC 1.1 and later
    uint8_t  bmFramingInfo;    // UVC 1.5 and later
    uint8_t  bPreferedVersion; // UVC 1.5 and later
    uint8_t  bMinVersion;      // UVC 1.5 and later
    uint8_t  bMaxVersion;      // UVC 1.5 and later
};

class A
{
public:
    A(const std::string &name):
        name_(name), data_(NULL), len_(0), ex_(NULL){};
    virtual ~A(){}

    std::string name_;
    uint8_t *data_;
    uint32_t len_;
    void *ex_;
    
    explicit virtual operator std::string() const
    {
        std::ostringstream os;
        os    <<    "{";
        os    <<    toString();
        os    <<    "}";
        return os.str();
    }
    
    virtual std::string toString() const
    {
        std::ostringstream os;
        os  << std::hex;
        os  << "["         <<   (uint64_t)this << "]";
        os  << name_;
        os  << "|ex_:"     <<    ex_;
        os  << "|data_:"   <<    (uint64_t)data_;
        os  << "|len_:"    <<    len_;
        return os.str();
    }
    
    /**
     *  @brief 读取数据
     *  @arg data 要读取的数据
     *  size 数据实际长度
     *  reserve 需要预留的扩展长度
     *  @exception logic_error invalid_argument bad_alloc
     */
    virtual void ReadData(uint8_t* data, uint32_t size, uint32_t reserve = 0)
    {
        if (data_ || len_){
            printf("invalid data_:%p, len_:%d\n", data_, len_);
            throw std::logic_error("invalid data_/len_");
        }
        if (data == NULL || size == 0){
            printf("invalid data:%p, size:%d\n", data, size);
            throw std::invalid_argument("invalid data/size");
        }

        data_   = new uint8_t[size + reserve];
        if (!data_)
            throw std::bad_alloc();
        
        len_    = size;
        memcpy(this->data_, data, size);
    }
    
    virtual A& operator=(const A& obj)
    {
        assert(data_ == NULL && len_ == 0);
        ex_     = obj.ex_;
        ReadData(obj.data_, obj.len_);
        return *this;
    };
};

#define USB_CTRLRSP_UVCPROBE        "hejian"
class B: public A
{
public:
    B(): A(USB_CTRLRSP_UVCPROBE), rsp_(NULL) {}
    ~B(){}
    
    struct uvc_streaming_control *rsp_;
};

#define DATA_LEN 26
int main()
{
    uint8_t data = 100;
    uint8_t ex[DATA_LEN] = { 0 };
    for (int i = 0; i < DATA_LEN; i++) {
        ex[i] = i;
    }
    //A test("whl");
    B test;
    test.name_ = "hj";
    test.data_ = &data;
    test.len_  = DATA_LEN;
    test.ex_   = ex;
    
    A *rsp = &test;
    std::cout << typeid(*rsp).name() << std::endl;
    
    B *probe_rsp = dynamic_cast<B *>(rsp);
    if (probe_rsp == nullptr) {
        std::cerr << "dynamic_cast failed" << std::endl;
        return -1;
    }
    // 将 ex_ 指针转换为 uvc_streaming_control 指针并赋值给 rsp_
    probe_rsp->rsp_ = reinterpret_cast<uvc_streaming_control *>(probe_rsp->ex_);

    if (probe_rsp->rsp_ == nullptr) {
        std::cerr << "probe_rsp->rsp_ is nullptr" << std::endl;
        return -1;
    }
    
    printf("sizeof(struct uvc_streaming_control): %ld\n", sizeof(struct uvc_streaming_control));
    
    struct uvc_streaming_control *p = (struct uvc_streaming_control *)malloc(sizeof(struct uvc_streaming_control));
    if (p == nullptr) {
        std::cerr << "malloc failed" << std::endl;
        return -1;
    }
    
    *p = *(probe_rsp->rsp_);
    
    free(p);
    p = NULL;
    return 0;
}
