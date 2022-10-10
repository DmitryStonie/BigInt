#include <iostream>
#include <vector>
#include <string>
#include "BigInt.h"

using namespace std;

int main() {
	BigInt n1("115792089237316195423570985008687907853269984665640564039457584007913129639936");
	BigInt n6("1");
	string str(n1 / n6);
	return 0;
}