#include <iostream>
#include <vector>
#include <string>
#include "BigInt.h"

using namespace std;

int main() {
	BigInt n5("-79228162514264337593543950335");
	BigInt n6("79228162514264337593543950335");
	string a3 = (string)(n5 + n6);
	return 0;
}