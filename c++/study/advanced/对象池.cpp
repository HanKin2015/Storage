/*******************************************************************************
* 文 件 名: 对象池.cpp
* 文件描述: 对象池（Object Pool） 是一种创建和管理对象的设计模式，旨在通过复用已创建的对象来提高性能和资源利用率
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <functional>
#include <stdexcept>

template<typename T>
class ObjectPool {
public:
    // 对象工厂函数类型
    using FactoryFunction = std::function<std::shared_ptr<T>()>;

    // 构造函数：指定初始大小、最大大小和对象工厂
    ObjectPool(size_t initialSize, size_t maxSize, FactoryFunction factory)
        : maxSize_(maxSize), factory_(factory) {
        for (size_t i = 0; i < initialSize; ++i) {
            pool_.push(factory_());
        }
    }

    // 禁止拷贝
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;

    // 获取对象
    std::shared_ptr<T> acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (pool_.empty()) {
            if (currentSize_ < maxSize_) {
                // 创建新对象
                auto obj = factory_();
                currentSize_++;
                return std::shared_ptr<T>(obj.get(), [this](T* ptr) {
                    this->release(std::shared_ptr<T>(this->factory_(), [](T*){}));
                });
            } else {
                throw std::runtime_error("Object pool is full and cannot create more objects");
            }
        }

        // 从池中取出对象
        auto obj = pool_.front();
        pool_.pop();
        return std::shared_ptr<T>(obj.get(), [this](T* ptr) {
            this->release(obj);
        });
    }

    // 返回对象数量
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return currentSize_;
    }

private:
    // 返回对象到池中
    void release(std::shared_ptr<T> obj) {
        std::lock_guard<std::mutex> lock(mutex_);
        pool_.push(obj);
    }

    mutable std::mutex mutex_;          // 线程安全锁
    std::queue<std::shared_ptr<T>> pool_; // 存储空闲对象
    size_t currentSize_ = 0;            // 当前池中的对象总数
    size_t maxSize_;                    // 池的最大容量
    FactoryFunction factory_;           // 对象工厂函数
};