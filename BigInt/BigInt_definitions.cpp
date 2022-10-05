#include <iostream>
#include "BigInt.h"

BigInt& BigInt::operator=(const BigInt& num_2) {
	sign = num_2.sign;
	number = num_2.number;
	return *this;
}

BigInt BigInt::operator~() const {
	BigInt tmp = (*this);
	if (sign == '+') {
		tmp.sign = '-';
		carry(tmp, ((long long)tmp.number[0]) + 1, 0);
	}
	else {
		tmp.sign = '+';
		carry(tmp, ((long long)tmp.number[0]) - 1, 0);
	}
	return tmp;
}

BigInt& BigInt::operator++() {
	if (sign == '+') carry(*this, ((long long)number[0]) + 1, 0);
	else carry(*this, ((long long)number[0]) - 1, 0);
	return *this;
}

const BigInt BigInt::operator++(int) {
	const BigInt temp = *this;
	if (sign == '+') carry(*this, ((long long)number[0]) + 1, 0);
	else carry(*this, ((long long)number[0]) - 1, 0);
	return temp;
}

BigInt& BigInt::operator--() {
	if (sign == '-') carry(*this, ((long long)number[0]) + 1, 0);
	else carry(*this, ((long long)number[0]) - 1, 0);
	return *this;
}

const BigInt BigInt::operator--(int) {
	const BigInt temp = *this;
	if (sign == '-') carry(*this, ((long long)number[0]) + 1, 0);
	else carry(*this, ((long long)number[0]) - 1, 0);
	return temp;
}

BigInt& BigInt::operator+=(const BigInt& num_2) {
	int num_2_digits = used_digits(num_2);
	long long tmp = 0;
	if ((*this).sign == num_2.sign) {
		for (int i = 0; i < num_2_digits; i++) {
			tmp = (long long)(*this).number[i] + (long long)num_2.number[i];
			carry((*this), tmp, i);
		}
	}
	else {
		for (int i = 0; i < num_2_digits; i++) {
			tmp = (long long)(*this).number[i] - (long long)num_2.number[i];
			carry((*this), tmp, i);
		}
	}
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& num_2) {
	int num_1_digits = used_digits(*this);
	int num_2_digits = used_digits(num_2);
	long long tmp = 0;
	BigInt num_1_tmp = *this;
	for (int i = 0; i < num_1_digits; i++) {
		number[i] = 0;
	}
	for (int i = 0; i < num_2_digits; i++) {
		for (int j = 0; j < num_1_digits; j++) {
			tmp = (long long)num_1_tmp.number[j] * (long long)num_2.number[i];
			carry(*this, tmp, i + j);
		}
	}
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& num_2) {
	BigInt tmp = num_2;
	tmp = -tmp;
	*this += tmp;
	return *this;
}

BigInt& BigInt::operator/=(const BigInt& num_2) {
	BigInt tmp = *this;
	BigInt mul = 0;
	int digit_pos = 0;
	for (; mul * num_2 < *this;) {
		for (int j = 0; mul * num_2 < *this;) {
			if (j % 32 == 0) mul.number[j / 32] = 0;
			carry(mul, (long long)(1 << (j % 32)), j / 32);
		}

	}
	return *this;
}

BigInt& BigInt::operator^=(const BigInt& num_2) {
	int num_2_digits = used_digits(num_2);
	int num_1_digits = used_digits(*this);
	number.resize(max(num_1_digits, num_2_digits));
	for (int i = 0; i < num_2_digits && i < num_1_digits; i++) {
		number[i] ^= num_2.number[i];
	}
	for (int j = num_1_digits; j < num_2_digits; j++) number[j] = num_2.number[j] ^ 0;
	return *this;
}

BigInt& BigInt::operator%=(const BigInt& num_2) {
	return *this;
}

BigInt& BigInt::operator&=(const BigInt& num_2) {
	int num_2_digits = used_digits(num_2);
	int num_1_digits = used_digits(*this);
	for (int i = 0; i < num_2_digits; i++) {
		number[i] &= num_2.number[i];
	}
	for (int j = num_2_digits; j < num_1_digits; j++) number[j] = 0;
	return *this;
}

BigInt& BigInt::operator|=(const BigInt& num_2) {
	int num_2_digits = used_digits(num_2);
	int num_1_digits = used_digits(*this);
	number.resize(max(num_1_digits, num_2_digits));
	for (int i = 0; i < num_2_digits && i < num_1_digits; i++) {
		number[i] |= num_2.number[i];
	}
	for (int j = num_1_digits; j < num_2_digits; j++) number[j] = num_2.number[j];
	return *this;
}

BigInt BigInt::operator+() const {	// unary +
	return *this;
}

BigInt BigInt::operator-() const {	// unary -
	BigInt temp = *this;
	if (sign == '+') temp.sign = '-';
	else temp.sign = '+';
	return temp;
}

BigInt::operator int() const {
	BigInt tmp = *this;
	int answer = number[0] << 1 >> 1;
	if (sign == '-') {
		answer = ~answer + 1;
		if (number[0] == 2'147'483'648) answer = -2'147'483'648;
	}
	return answer;
}

BigInt::operator std::string() const {
	string str = "";
	if (sign == '-') str.push_back('-');
	vector<int>dec_num(1);
	long long tmp = 0;
	long long decs[9] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
	int dec_base = 1000000000;
	int bit = 0;
	long long index = (used_digits(*this))* 32 - 1;
	for (long long i = index; i >= 0; i--) {
		bit = (number[i / 32] >> (i % 32)) & 1;
		IncreaseDecNum(dec_num, bit);
	}
	int size = dec_num.size(), flag = 0;
	for (int j = 8; j >= 0; j--) {
		bit = (dec_num[size - 1] / decs[j]) % 10;
		if (flag == 0 && bit != 0) flag = 1;
		if(flag) str.push_back((char)bit + 48);
	}
	for (int i = size - 2; i >= 0; i--) {
		for (int j = 8; j >= 0; j--) {
			bit = (dec_num[i] / decs[i]) % 10;
			str.push_back((char)bit + 48);
		}
	}
	return str;
}

size_t BigInt::size() const {
	size_t answer = number.size() * sizeof(unsigned int) + sizeof(sign) + sizeof(default_size) + sizeof(base);
	return answer;
}

BigInt operator+(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp += num_2;
}

BigInt operator-(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp -= num_2;
}

BigInt operator*(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp *= num_2;
}

BigInt operator/(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp /= num_2;
}

BigInt operator^(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp ^= num_2;
}

BigInt operator%(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp %= num_2;
}

BigInt operator&(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp &= num_2;
}

BigInt operator|(const BigInt& num_1, const BigInt& num_2) {
	BigInt tmp(num_1);
	return tmp |= num_2;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	o << (std::string)i;
	return o;
}

