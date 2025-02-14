#include <iostream>
#include <string>
#include <sstream>

std::string compressString(const std::string &str) {
    std::ostringstream compressed;
    int count = 1;

    for (size_t i = 0; i < str.length(); ++i) {
        if (i + 1 < str.length() && str[i] == str[i + 1]) {
            ++count;
        } else {
            if (isdigit(str[i]) || str[i] == '_') {
                compressed << '_'; // Use an underscore to separate the digit or underscore character from the count
            }
            compressed << str[i];
            compressed << count;
            count = 1;
        }
    }

    return compressed.str();
}

std::string uncompressString(const std::string &str) {
    std::ostringstream uncompressed;
    for (size_t i = 0; i < str.length(); ++i) {
        char ch = str[i];
        if (ch == '_') {
            ++i;
            ch = str[i];
        }
        ++i;
        int count = str[i] - '0';
        while (i + 1 < str.length() && isdigit(str[i + 1])) {
            count = count * 10 + (str[++i] - '0');
        }
        uncompressed << std::string(count, ch);
    }
    return uncompressed.str();
}

int main() {
    std::string input = "AAABB__33333....???CCCCCDDDDDDDDDDDD444444";
    std::cout << "Original string: " << input << std::endl;

    std::string compressed = compressString(input);
    std::cout << "Compressed string: " << compressed << std::endl;

    std::string uncompressed = uncompressString(compressed);
    std::cout << "Uncompressed string: " << uncompressed << std::endl;
    return 0;
}