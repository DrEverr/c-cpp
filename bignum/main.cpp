#include <iostream>
#include "bignum.hpp"

int main() {
	BigNum a("23213125423567");
	BigNum b("43222665457656856644");
	std::cout << a << " + " << b << " = " << a + b << "\n";
	std::cout << a << " - " << b << " = " << a - b << "\n";

	return 0;
}