#include <vector>
#include <string>
#include <stdexcept>
#include "BigInt.h"

using namespace std;

BigInt::BigInt() {
	number.resize(default_size);
	number[0] = 0;
	sign = '+';
}

BigInt::BigInt(int a) {
	number.resize(default_size);
	if (a < 0) {
		sign = '-';
		long long tmp = a;
		tmp = llabs(tmp);
		number[0] = (unsigned int)(tmp % base);
	}
	else {
		sign = '+';
		number[0] = (unsigned int)a;
	}
}

BigInt::BigInt(std::string str_num) {
	if (is_number(str_num) == 0) {								// check for not a number
		throw std::invalid_argument("Invalid syntax.");				// exception doesn't handle
		return;
	}
	string tmp = str_num;											//error when empty string
	int last_index = str_num.length() - 1, first_index = 0;
	for (int i = 0; i <= last_index; i++) tmp[i] -= 48;				//from chars to numbers
	sign = set_sign(str_num[0]);
	number.resize(0);
	if (str_num[0] == '-' || str_num[0] == '+') {					//if first + or -
		first_index = 1;
	}
	char carry = 0, to_divide = 0;
	int bit_to_write = 0;
	for (int i = first_index; i <= last_index; bit_to_write++, to_divide = 0, carry = 0) {
		for (int j = i; j <= last_index; j++) {
			to_divide = carry * 10 + tmp[j];
			carry = to_divide % 2;
			tmp[j] = to_divide / 2;
		}
		if (bit_to_write % 32 == 0) number.resize(number.size() + 1);
		number[bit_to_write / 32] = number[bit_to_write / 32] + (((unsigned int)carry) << (bit_to_write));
		if (tmp[i] == 0) i++;
	}
}

BigInt::BigInt(const BigInt& num_2) {
	sign = num_2.sign;
	number = num_2.number;
}

BigInt::~BigInt() {

}