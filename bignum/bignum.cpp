#include "bignum.hpp"

#include <algorithm>
#include <stdexcept>

BigNum::BigNum() : number("0"), isNegative(false) {}

BigNum::BigNum(std::string num) {
	if (num[0] == '-') {
		isNegative = true;
		num = num.substr(1);
	} else {
		isNegative = false;
	}

	if (num.empty()) {
		throw std::invalid_argument("error: received empty value");
	}

	for (char c : num) {
		if (!std::isdigit(c)) {
			throw std::invalid_argument("received value with invalid character in value '" + num + "'");
		}
	}

	if (num.length() > 1) {
		uint leading_zeros = 0;
		for (char c : num) {
			if (c != '0') {
				break;
			} else {
				leading_zeros++;
			}
		}
		num = num.substr(leading_zeros);
	}

	number = num;
}

BigNum::BigNum(long long num) {
	if (num < 0) {
		isNegative = true;
		num = -num;
	} else {
		isNegative = false;
	}

	number = std::to_string(num);
}

std::string BigNum::get_number() const {
	return (isNegative ? "-" : "") + number;
}

std::ostream& operator<<(std::ostream& os, const BigNum& bn) {
	os << bn.get_number();
	return os;
}

BigNum BigNum::operator+(const BigNum& other) const {
	if (isNegative && !other.isNegative) {
		return other - BigNum(number);
	}
	if (!isNegative && other.isNegative) {
		return *this - BigNum(other.number);
	}

	std::string num1 = number, num2 = other.number;
	std::string result = "";
	bool negativeResult = isNegative && other.isNegative;

	int i = num1.length() - 1, j = num2.length() - 1;
	int a = 0, b = 0, sum = 0, carry = 0;

	while (i >= 0 || j >= 0 || carry) {
		a = i >= 0 ? num1[i] - '0' : 0;
		b = j >= 0 ? num2[j] - '0' : 0;
		sum = a + b + carry;

		result.push_back((sum % 10) + '0');
		carry = sum / 10;

		i--; j--;
	}

	std::reverse(result.begin(), result.end());
	return negativeResult ? BigNum("-" + result) : BigNum(result);
}

BigNum BigNum::operator-(const BigNum& other) const {
	if (isNegative && !other.isNegative) {
		return BigNum("-" + (BigNum(number) + other).number);
	}
	if (!isNegative && other.isNegative) {
		return *this + BigNum(other.number);
	}

	std::string num1 = number, num2 = other.number;
	std::string result = "";
	bool negativeResult = false;

	int i = num1.length() - 1, j = num2.length() - 1;
	int a = 0, b = 0, sum = 0, carry = 0;

	if (i < j || (i == j && num1 < num2)) {
		std::swap(num1, num2);
		i = num1.length() - 1;
		j = num2.length() - 1;
		negativeResult = true;
	}

	while (i >= 0) {
		a = num1[i] - '0';
		b = j >= 0 ? num2[j] - '0' : 0;
		if (a < b + carry) {
			a += 10;
			result.push_back((a - b - carry) + '0');
			carry = 1;
		} else {
			result.push_back((a - b - carry) + '0');
			carry = 0;
		}

		i--; j--;
	}
	std::reverse(result.begin(), result.end());
	return negativeResult ? BigNum("-" + result) : BigNum(result);
}
