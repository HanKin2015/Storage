#include <iostream>
#include <functional>

class ScopeGuard {
public:
    ScopeGuard(std::function<void()> func) : func_(func) {}
    ~ScopeGuard() { func_(); }
private:
    std::function<void()> func_;
};

int main() {
    std::cout << "Enter main" << std::endl;

    {
        ScopeGuard guard([]() { std::cout << "Exit scope" << std::endl; });
        std::cout << "Inside scope" << std::endl;
    }

    std::cout << "Leave main" << std::endl;
    return 0;
}
