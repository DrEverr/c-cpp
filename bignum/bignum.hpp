#pragma once

#include <iostream>
#include <string>

class BigNum {
private:
	std::string number;
	bool isNegative;

public:
	BigNum();
	BigNum(std::string num);
	BigNum(long long num);

	BigNum operator+(const BigNum& other) const;
	BigNum operator-(const BigNum& other) const;

	std::string get_number() const;
	friend std::ostream& operator<<(std::ostream& os, const BigNum& bn);
};
