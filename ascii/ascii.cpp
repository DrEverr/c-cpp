#include <iostream>
#include <ranges>
#include <format>

int main(){
    std::cout << "Printable ASCII characters: [32, 126]\n";

    auto printable_chars =
    std::views::iota(32, 127) | std::views::transform(
        [](int c){ return static_cast<char>(c); }
    );

    for (char c : printable_chars){
        std::cout << c << ((c + 1) % 32 ? ' ' : '\n');
    }

    std::cout << '\n';
    return 0;
}