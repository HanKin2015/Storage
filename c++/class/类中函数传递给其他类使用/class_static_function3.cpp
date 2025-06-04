/*******************************************************************************
* 文 件 名: class_static_function3.cpp
* 文件描述: 类中静态函数使用成员变量
* 备    注: bind函数绑定两个参数
* 作    者: HanKin
* 创建日期: 2025.04.24
* 修改日期：2025.04.24
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <functional>
#include <memory>
#include <cstring>
#include <string> // 添加此行以支持 std::string

class Car {
public:
    Car(std::function<int(const char *car_type, int person_num)> get_real_time_passwd_cb)
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);
        m_get_real_time_passwd_cb = get_real_time_passwd_cb;
    }
    ~Car() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    // 汽车启动需要获取实时的密码，这个需要从Person中获取
    void start()
    {
        int passwd = m_get_real_time_passwd_cb("I am BBA", 10);
        printf("current password is <%d>\n", passwd);
    }

private:
    std::function<int(const char *car_type, int person_num)> m_get_real_time_passwd_cb;
};

class Person {
public:
    Person()
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);

        // error: invalid use of non-static member function
        //m_car = std::make_shared<Car>(get_real_time_passwd);

        // 使用 lambda 表达式将成员函数绑定到实例
        //m_car = std::make_shared<Car>([this](const char *car_type) { return this->get_real_time_passwd(car_type); });

        // 使用 std::bind 将成员函数绑定到实例
        m_car = std::make_shared<Car>(std::bind(&Person::get_real_time_passwd, this, std::placeholders::_1, std::placeholders::_2));
        m_name = "I am a driver";
    }
    ~Person() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    static Person* Instance() {
        static Person instance_;
        return &instance_;
    }

    void drive_car()
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);
        m_car->start();
        return;
    }
    
    // 访问成员变量，不受影响呢，因此不需要将此函数转换为静态函数
    int get_real_time_passwd(const char *car_type, int person_num)
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);
        printf("hallo, %s, today drive car type is <%s>\n", m_name.c_str(), car_type);
        if (strcmp(car_type, "I am BBA") == 0) {
            return 12345;
        }
        return 54321;
    }

private:
    std::shared_ptr<Car> m_car;
    std::string m_name;
};

int main()
{
    std::shared_ptr<Person> obj = std::make_shared<Person>();
    obj->drive_car();
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #./a.out
41: Person
21: Car
58: drive_car
65: get_real_time_passwd
today drive car type is <I am BBA>
current password is <12345>
49: ~Person
24: ~Car
*/