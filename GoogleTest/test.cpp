#include "pch.h"
#include "../BigInt/BigInt.h"

TEST(TestCaseName, TestName) {
	BigInt a("94390543298432");
	EXPECT_EQ((string)a, "23423434");
	EXPECT_TRUE(true);
}