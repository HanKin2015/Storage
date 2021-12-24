#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <iostream>
#include <sstream>


#define CPP_CLEAR(obj) do {\
        if (obj) \
            delete obj; \
        obj = NULL; \
    }while(0)

#define C_CLEAR(mem) do {\
        if (mem) \
                free(mem); \
        mem = NULL; \
    }while(0)

class Object
{
public:
    std::string    name_;
    uint8_t*       data_;
    uint32_t       len_;
    char*          ex_;

    explicit virtual operator std::string() const
    {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        std::ostringstream os;
        os    <<    "{";
        os    <<    toString();
        os    <<    "}";
        return os.str();
    }
    
public:
    // choose to be override or not
    // warning: explicit conversion operators only available with -std=c++11 or -std=gnu++11
    virtual std::string toString() const
    {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        std::ostringstream os;
        os  << std::hex ;
        os  << "["         <<   (uint64_t)this << "]";
        os  << name_;
        os  << "|ex_:"     <<    ex_;
        os  << "|data_:"   <<    (uint64_t)data_;
        os  << "|len_:"    <<    len_;
        return os.str();
    }
    
    explicit virtual operator const char*() const
    {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        std::string str = "";       // 问题所在
        str += (std::string)*this;
        return str.c_str();
    }
    
    void log(const char* fmt, ...) const
    {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        va_list va;
        char msg[512] = "";

        va_start(va, fmt);
        vsprintf(msg, fmt, va);
        va_end(va);

        printf("msg: %s\n", msg);
        return;
    }

    virtual void Dump(const char *lvl) const
    {
        std::string str = this->toString();
        fprintf(stderr, "[%s] %s\n", lvl, str.c_str());
        fprintf(stderr, "[%s] %s\n", lvl, str.data());
        //fprintf(stderr, lvl, "%s\n", (const char*)(*this));
        log("%s\n", (const char*)(*this));
    }
    
    virtual void DumpData(const char *lvl) const
    {
        std::ostringstream os;
        uint32_t i = 0;
        os << "data_: 0x" << std::hex << (uint64_t)data_ << " ";
        os << "len_: 0x" << std::hex << (uint32_t)len_ << " ";

        for (i = 0 ; i < len_  &&  i < 16 ; i++)
            os <<  std::hex << " 0x" <<(uint32_t)(data_[i]);

        fprintf(stderr, lvl, "%s\n", os.str().c_str());
    }
    
public:
    Object(const std::string& name):
        name_(name),data_(NULL),len_(0),ex_(NULL){};
        
    Object(const Object& object):
        name_(object.name_),
        data_(object.data_),len_(object.len_),ex_(object.ex_){};
        
    virtual ~Object(){
        CPP_CLEAR(data_);
    }
};



int main()
{
    Object *obj = new Object("hejian");
    uint8_t *data = (uint8_t *)"abcd";
    uint32_t len = 12345;
    char *ex = (char *)"hello wolrd";
    
    obj->data_ = data;
    obj->len_  = len;
    obj->ex_   = ex;
    
    obj->Dump("info");
    return 0;
}
