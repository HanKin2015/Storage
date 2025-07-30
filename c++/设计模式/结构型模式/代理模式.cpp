/*******************************************************************************
* 文 件 名: 代理模式.cpp
* 文件描述: 用于控制对某个对象的访问，增强功能而不改变原有接口。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>

class Image {
public:
    virtual void display() const = 0;
    virtual ~Image() = default;
};

class RealImage : public Image {
private:
    std::string filename;
    void loadFromDisk() const {
        std::cout << "Loading " << filename << std::endl;
    }
public:
    explicit RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk();
    }
    void display() const override {
        std::cout << "Displaying " << filename << std::endl;
    }
};

class ProxyImage : public Image {
private:
    mutable RealImage* realImage;  // 关键修改：声明为mutable
    std::string filename;
    mutable bool isLoaded;  // 关键修改：声明为mutable
public:
    explicit ProxyImage(const std::string& filename) 
        : realImage(nullptr), filename(filename), isLoaded(false) {}
    
    ~ProxyImage() override {
        delete realImage;
    }
    
    void display() const override {
        std::cout << "[Proxy] Checking permissions..." << std::endl;
        
        if (!isLoaded) {
            realImage = new RealImage(filename);  // 现在合法
            isLoaded = true;  // 现在合法
        }
        
        std::cout << "[Proxy] Logging access to " << filename << std::endl;
        realImage->display();
        std::cout << "[Proxy] Applying cache policy..." << std::endl;
    }
};

void clientCode(const Image& image) {
    image.display();
}

int main() {
    ProxyImage proxy("example.jpg");
    
    std::cout << "First display:" << std::endl;
    clientCode(proxy);
    
    std::cout << "\nSecond display:" << std::endl;
    clientCode(proxy);
    
    return 0;
}