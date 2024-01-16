#include <boost/fiber/all.hpp>
#include <iostream>

void fiber_func() {
    std::cout << "Hello, fibers!" << std::endl;
}

int main() {
    boost::fibers::fiber f(fiber_func);
    f.join();
    return 0;
}
