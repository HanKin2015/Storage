#include <coroutine>
#include <iostream>
#include <iterator>
#include <memory>

template<typename T>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        T value_;
        std::suspend_always yield_value(T value) {
            value_ = value;
            return {};
        }
        Generator get_return_object() {
            return Generator(handle_type::from_promise(*this));
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {
            std::exit(1);
        }
    };

    handle_type coro_;

    Generator(handle_type h) : coro_(h) {}
    ~Generator() {
        if (coro_) coro_.destroy();
    }
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) : coro_(other.coro_) {
        other.coro_ = nullptr;
    }
    Generator& operator=(Generator&& other) {
        if (this != &other) {
            coro_ = other.coro_;
            other.coro_ = nullptr;
        }
        return *this;
    }

    T next() {
        if (!coro_) {
            throw std::runtime_error("Attempt to get value from an empty generator");
        }
        coro_.resume();
        if (coro_.done()) {
            coro_.destroy();
            coro_ = nullptr;
            throw std::runtime_error("Attempt to get value from a finished generator");
        }
        return coro_.promise().value_;
    }
};

Generator<int> generate_numbers(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}

int main() {
    auto numbers = generate_numbers(0, 10);
    try {
        while (true) {
            std::cout << numbers.next() << std::endl;
        }
    } catch (const std::runtime_error&) {
        // Generator is finished
    }
    return 0;
}
