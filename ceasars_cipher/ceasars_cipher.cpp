#include <iostream>
#include <string>
#include <ranges>

std::string caesarCipher(const std::string& text, int shift) {
    std::string result;

    // Traverse the text using ranges
    for (char c : text | std::views::transform([shift](char c) {
        if (std::isalpha(c)) {
            char base = std::islower(c) ? 'a' : 'A';
            return static_cast<char>((c - base + shift) % 26 + base);
        }
        return c;
    })) {
        result += c;
    }

    return result;
}

int main() {
    std::string text;
    int shift;

    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    std::cout << "Enter shift: ";
    std::cin >> shift;

    std::string encryptedText = caesarCipher(text, shift);
    std::cout << "Encrypted text: " << encryptedText << std::endl;

    return 0;
}