#include <string>
#include "BigInt.h"

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
	int tmp = num.number[used_digits - 1];
	for (; tmp > 0;) {
		tmp = tmp >> 1;
		i++;
	}
	if (used_digits == 1 && i == 0) return 1;		//	when number = zero
	return i;
}

int BigInt::digits_in_highest_digit(const BigInt& num, int used_digits) {	//returns number of used digits in highest unzero digit
	int i = 0;
	int tmp = num.number[used_digits - 1];
	for (; tmp > 0;) {
		tmp = tmp >> 1;
		i++;
	}
	if (used_digits == 1 && i == 0) return 1;		//	when number = zero
	return i;
}

int BigInt::digits_in_highest_digit(const BigInt& num, int used_digits) const {	//returns number of used digits in highest unzero digit
	int i = 0;
	int tmp = num.number[used_digits - 1];
	for (; tmp > 0;) {
		tmp = tmp >> 1;
		i++;
	}
	if (used_digits == 1 && i == 0) return 1;		//	when number = zero
	return i;
}

int BigInt::used_digits(BigInt& num) {	//return number of highest unzero digit
	int i = num.number.size() - 1;
	for (; num.number[i] == 0; i--);
	return i + 1;
}

int BigInt::used_digits(const BigInt& num) {	//return number of highest unzero digit
	int i = num.number.size() - 1;
	for (; num.number[i] == 0; i--);
	return i + 1;
}

int BigInt::used_digits(const BigInt& num) const {	//funny, but without this doesn't compile ==
	int i = num.number.size() - 1;
	if (i == 0) return 1;
	for (; num.number[i] == 0; i--);
	return i + 1;
}

void BigInt::carry(BigInt& number, long long new_number, int num_index) { //carry ����������
	int num_1_digits = used_digits(*this);
	for (int i = num_index;; i++) {
		if (new_number >= base) {		//if change base, make <=
			if (i == num_1_digits - 1) {	//bounds checking
				number.number.resize(num_1_digits + 1);
				num_1_digits++;
				number.number[i + 1] = 0;
			}
			number.number[i] = (unsigned int)(new_number % number.base);
			new_number = new_number / number.base + number.number[i + 1];
		}
		else if (new_number < 0) {
			if (i == num_1_digits - 1) {	//if carry is impossible
				if (number.sign == '+') number.sign = '-';
				else number.sign = '+';
				number.number[i] = -new_number;					//check this
				break;
			}
			number.number[i] = (unsigned int)((new_number + number.base) % number.base);
			new_number = (long long)(number.number[i + 1]) - 1;
		}
		else {
			number.number[i] = (unsigned int)new_number;
			break;
		}
	}
}

void BigInt::carry(BigInt& number, long long new_number, int num_index) const { //carry ����������
	int num_1_digits = used_digits(*this);
	for (int i = num_index;; i++) {
		if (new_number >= base) {		//if change base, make <=
			if (i == num_1_digits - 1) {	//bounds checking
				number.number.resize(num_1_digits + 1);
				num_1_digits++;
				number.number[i + 1] = 0;
			}
			number.number[i] = (unsigned int)(new_number % number.base);
			new_number = new_number / number.base + number.number[i + 1];
		}
		else if (new_number < 0) {
			if (i == num_1_digits - 1) {	//if carry is impossible
				if (number.sign == '+') number.sign = '-';
				else number.sign = '+';
				number.number[i] = -new_number;					//check this
				break;
			}
			number.number[i] = (unsigned int)((new_number + number.base) % number.base);
			new_number = (long long)(number.number[i + 1]) - 1;
		}
		else {
			number.number[i] = (unsigned int)new_number;
			break;
		}
	}
}
