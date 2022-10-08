#include <string>
#include "BigInt.h"
#include <iostream>

int BigInt::is_number(std::string& str_num) {
	if ((str_num[0] == '+' || str_num[0] == '-' || (str_num[0] >= '0' && str_num[0] <= '9')) == 0) return 0;
	for (int i = 1; i < str_num.size(); i++) {
		if ((str_num[i] >= '0' && str_num[i] <= '9') == 0) return 0;
	}
	return 1;
}

char BigInt::set_sign(char symbol) {
	if (symbol == '-') return '-';
	else if (symbol == '+' || (symbol >= '0' && symbol <= '9')) return '+';
	return 0; //i don't use it
}

int BigInt::digits_in_highest_digit(BigInt& num, int used_digits) {	//returns number of used digits in highest unzero digit
	int i = 0;
	unsigned int tmp = num.number[used_digits - 1];
	for (; tmp > 0;) {
		tmp = tmp >> 1;
		i++;
	}
	if (used_digits == 1 && i == 0) return 1;		//	when number = zero
	return i;
}

int BigInt::digits_in_highest_digit(const BigInt& num, int used_digits) {	//returns number of used digits in highest unzero digit
	int i = 0;
	unsigned int tmp = num.number[used_digits - 1];
	for (; tmp > 0;) {
		tmp = tmp >> 1;
		i++;
	}
	if (used_digits == 1 && i == 0) return 1;		//	when number = zero
	return i;
}

int BigInt::digits_in_highest_digit(const BigInt& num, int used_digits) const {	//returns number of used digits in highest unzero digit
	int i = 0;
	unsigned int tmp = num.number[used_digits - 1];
	for (; tmp > 0;) {
		tmp = tmp >> 1;
		i++;
	}
	if (used_digits == 1 && i == 0) return 1;		//	when number = zero
	return i;
}

int BigInt::used_digits(BigInt& num) {	//return number of highest unzero digit
	int i = num.number.size() - 1;
	if (i == 0) return 1;
	for (; i >= 0;) {
		if (num.number[i] == 0) {
			i--;
		}
		else break;
	}
	if (i == -1) i = 0;
	return i + 1;
}

int BigInt::used_digits(const BigInt& num) {	//return number of highest unzero digit
	int i = num.number.size() - 1;
	if (i == 0) return 1;
	for (; i >= 0;) {
		if (num.number[i] == 0) {
			i--;
		}
		else break;
	}
	if (i == -1) i = 0;
	return i + 1;
}

int BigInt::used_digits(const BigInt& num) const {	//funny, but without this doesn't compile ==
	int i = num.number.size() - 1;
	if (i == 0) return 1;
	for (;i >= 0;) {
		if (num.number[i] == 0) {
			i--;
		}
		else break;
	}
	if (i == -1) i = 0;
	return i + 1;
}

void BigInt::carry(BigInt& number, long long new_number, int num_index) { //carry ����������
	int num_size = number.number.size();
	int num_used_digits = used_digits(number);
	for (int i = num_index;;) {
		if (i == num_size - 1) {//add new digit
			number.number.resize(num_size + 1);
			num_size++;
		}
		if (new_number >= base) { //carry up
			number.number[i] = (unsigned int)new_number % base;
			new_number = new_number / base + number.number[i + 1];
			i++;
		}
		else if (new_number < 0) {
			if (i == num_used_digits - 1) {
				if (number.sign == '+') number.sign = '-';//maybe bug because i change sign in +=
				else number.sign = '+';
				number.number[i] = (unsigned int)(-new_number);
				break;
			}
			number.number[i] = base + new_number;
			new_number = number.number[i + 1] - 1;
			i++;
		}
		else {
			number.number[i] = (unsigned int)new_number;
			break;
		}
	}
}

void BigInt::carry(BigInt& number, long long new_number, int num_index) const { //carry ����������
	int num_size = number.size();
	int num_used_digits = used_digits(number);
	for (int i = num_index;;) {
		if (i == num_size - 1) {//add new digit
			number.number.resize(num_size + 1);
			number.number[i + 1] = 0;
			num_size++;
		}
		if (new_number >= base) { //carry up
			number.number[i] = (unsigned int)new_number % base;
			new_number = new_number / base + number.number[i + 1];
			i++;
		}
		else if (new_number < 0) {
			if (i == num_used_digits - 1) {
				if (number.sign == '+') number.sign = '-';
				else number.sign = '+';
				number.number[i] = (unsigned int)(-new_number);
				break;
			}
			number.number[i] = base + new_number;
			new_number = number.number[i + 1] - 1;
			number.number[i + 1]--;
			i++;
		}
		else {
			number.number[i] = (unsigned int)new_number;
			break;
		}
	}
}

void IncreaseDecNum(vector<int> &number, int bit) {
	for (int i = 0; i < number.size(); i++) {
		if (number[i] >= 1000000000) {
			if (i + 1 == number.size()) {
				number.resize(number.size() + 1);
				number[number.size() - 1] = 0;
			}
			number[i + 1] += 1;
			number[i] = number[i] % 1000000000;
		}
		number[i] = number[i] * 2;
		if (number[i] >= 1000000000) {
			if (i + 1 == number.size()) {
				number.resize(number.size() + 1);
				number[number.size() - 1] = 0;
			}
			number[i + 1] += 1;
			number[i] = number[i] % 1000000000;
		}
	}
	if (bit == 1) {
		number[0]++;
		for (int i = 0; number[i] >= 1000000000; i++) {
			if (i + 1 == number.size()) number.resize(number.size() + 1);
			number[number.size() - 1] = 0;
			number[i + 1] += 1;
			number[i] = number[i] % 1000000000;
		}
	}
}
