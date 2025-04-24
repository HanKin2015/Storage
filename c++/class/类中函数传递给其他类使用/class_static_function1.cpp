/*******************************************************************************
* 文 件 名: class_static_function1.cpp
* 文件描述: 类中静态函数使用成员变量
* 备    注: 使用静态函数的重要性是要把此函数传递给其他类使用，并不需要写成静态函数就可以使用
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

class Car {
public:
    Car(std::function<int(const char *car_type)> get_real_time_passwd_cb)
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);
        m_get_real_time_passwd_cb = get_real_time_passwd_cb;
    }
    ~Car() { printf("%d: %s\n", __LINE__, __FUNCTION__); }

    // 汽车启动需要获取实时的密码，这个需要从Person中获取
    void start()
    {
        int passwd = m_get_real_time_passwd_cb("I am BBA");
        printf("current password is <%d>\n", passwd);
    }

private:
    std::function<int(const char *car_type)> m_get_real_time_passwd_cb;
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
        m_car = std::make_shared<Car>(std::bind(&Person::get_real_time_passwd, this, std::placeholders::_1));
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
    
    // 未访问成员变量
    int get_real_time_passwd(const char *car_type)
    {
        printf("%d: %s\n", __LINE__, __FUNCTION__);
        printf("today drive car type is <%s>\n", car_type);
        if (strcmp(car_type, "I am BBA") == 0) {
            return 12345;
        }
        return 54321;
    }

private:
    std::shared_ptr<Car> m_car;
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