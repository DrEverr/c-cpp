#include <iostream>
#include <cmath>
#include <format>

// Function to calculate the diagonal of a cube given its volume
double cubeDiagonal(double volume) {
    // Calculate the side length of the cube
    double sideLength = std::cbrt(volume);

    // Calculate the main diagonal of the cube
    double diagonal = sideLength * std::sqrt(3);

    // Round the result to two decimal places and return
    return std::round(diagonal * 100) / 100;
}

int main() {
    std::cout << std::format("cubeDiagonal(8) -> {:.2f}\n", cubeDiagonal(8)); // 3.46
    std::cout << std::format("cubeDiagonal(343) -> {:.2f}\n", cubeDiagonal(343)); // 12.12
    std::cout << std::format("cubeDiagonal(1157.625) -> {:.2f}\n", cubeDiagonal(1157.625)); // 18.19
    return 0;
}