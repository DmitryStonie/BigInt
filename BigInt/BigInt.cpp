#include <iostream>
#include <vector>
#include <string>
#include "BigInt.h"

using namespace std;

int main() {
	BigInt n1("115792089237316195423570985008687907853269984665640564039457584007913129639936");
	BigInt n2("115792089237316195423570985008687907853269984665640564039457584007913129639935");
	BigInt n3("48563425834895345345");
	BigInt n4("-3298473482");
	BigInt n5("0");
	BigInt n6("1");
	BigInt n7("84375325489735983256294386932498238478237847887432872437843243432304782348934235");
	BigInt n8("34721554632468263492341263481632479273423423586324632646981234214");
	BigInt n9("-384567832654874362745736456324986324");
	BigInt n10("-1");

	/*string str(n1 / n2);
	string str2(n2 / n1);
	string str3(n7 / n8);
	string str4(n8 / n7);
	string str5(n1 / n3);
	string str6(n1 / n8);
	string str7(n1 / n4);
	string str8(n2 / n4);
	string str9(n1 / n6);
	string str10(n5 / n8);
	string str11(n5 / n6);
	string str12(n8 / n9);
	string str13(n2 / n9);
	string str14(n9 / n4);
	string str15(n1 / n6);
	//string str16(n1 / n5);*/
	string str17(n2 % n4);
	return 0;
}