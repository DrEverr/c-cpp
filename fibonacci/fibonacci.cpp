#include <iostream>
#include <iostream>
#include <coroutine>

#include "generator.hpp"

co::generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        auto temp = a;
        a = b;
        b = temp + b;
    }
}

int main() {
    std::cout << "Fibonacci sequence:\n";
    auto fib = fibonacci();
    for (int i = 0; i < 20; ++i) {
        std::cout << fib() << " ";
    }
    std::cout << std::endl;
    return 0;
}