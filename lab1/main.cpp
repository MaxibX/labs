#include <iostream>
#include"bigint.h"
#include"lib/googletest-main/googletest/include/gtest/gtest.h"

using namespace std;

TEST(test1, constr1) {
    BigInt::BigInt A;
    EXPECT_EQ(string(A), "0");
}
TEST(test2, constr2) {
    BigInt::BigInt A(369369);
    EXPECT_EQ(string(A), "369369");
}
TEST(test3, plus_constr3) {
    BigInt::BigInt A(+369369);
    EXPECT_EQ(string(A), "369369");
}
TEST(test4, minus_constr4) {
    BigInt::BigInt A(-369369);
    EXPECT_EQ(string(A), "-369369");
}
TEST(test5, minus_zero) {
    BigInt::BigInt A(-0);
    EXPECT_EQ(string(A), "0");
}
TEST(test6, str_constr1) {
    BigInt::BigInt A("369369");
    EXPECT_EQ(string(A), "369369");
}
TEST(test7, str_plus_constr2) {
    BigInt::BigInt A("+369369");
    EXPECT_EQ(string(A), "369369");
}
TEST(test8, str_minus_constr3) {
    BigInt::BigInt A("-369369");
    EXPECT_EQ(string(A), "-369369");
}
TEST(test9, str_minus_zero) {
    BigInt::BigInt A("-0");
    EXPECT_EQ(string(A), "0");
}
TEST(test10, str_len) {
    BigInt::BigInt A("1234567890123456789012345678901234567890");
    EXPECT_EQ(string(A), "1234567890123456789012345678901234567890");
}
TEST(test11, str_minus_many_zeros) {
    BigInt::BigInt A("-000000111");
    EXPECT_EQ(string(A), "-111");
}
TEST(test12, other_symbs) {
    EXPECT_THROW(BigInt::BigInt A("!-000a000@111."), invalid_argument);
}
TEST(test13, many_plus_minus) {
    EXPECT_THROW(BigInt::BigInt A("+-+-000000111"), invalid_argument);
}
TEST(test14, only_many_plus_minus) {
    EXPECT_THROW(BigInt::BigInt A("+-+-"), invalid_argument);
}
TEST(test15, copy1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B(A);
    EXPECT_EQ(string(A), string(B));
}
TEST(test16, plus_copy2) {
    BigInt::BigInt A("+37582935987");
    BigInt::BigInt B(A);
    EXPECT_EQ(string(A), string(B));
}
TEST(test17, minus_copy3) {
    BigInt::BigInt A("-37582935987");
    BigInt::BigInt B(A);
    EXPECT_EQ(string(A), string(B));
}
TEST(test18, equal) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B = A;
    EXPECT_TRUE(A == B);
}
TEST(test19, not_equal) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B(123);
    EXPECT_TRUE(A != B);
}
TEST(test20, operator_neg) {
    BigInt::BigInt A("1234567890123456789012345678901234567890");
    A = ~A;
    EXPECT_TRUE(string(A) == "-1234567890123456789012345678901234567891");
}
TEST(test21, operator_prefix_incr) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B = ++A;
    EXPECT_TRUE(B == A);
}
TEST(test22, operator_postfix_incr) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B = A++;
    EXPECT_EQ(string(A), "37582935988");
    EXPECT_EQ(string(B), "37582935987");
}
TEST(test23, operator_prefix_decr) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B = --A;
    EXPECT_TRUE(B == A);
}
TEST(test24, operator_postfix_decr) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B = A--;
    EXPECT_EQ(string(A), "37582935986");
    EXPECT_EQ(string(B), "37582935987");
}
TEST(test25, add1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-123123");
    A += B;
    EXPECT_EQ(string(A), "37582812864");
}
TEST(test26, add2) {
    BigInt::BigInt A("-123123");
    BigInt::BigInt B("37582935987");
    A += B;
    EXPECT_EQ(string(A), "37582812864");
}
TEST(test27, add3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    A += B;
    EXPECT_EQ(string(A), "75165871974");
}
TEST(test28, add4) {
    BigInt::BigInt A("-37582935987");
    BigInt::BigInt B("-37582935987");
    A += B;
    EXPECT_EQ(string(A), "-75165871974");
}
TEST(test29, add5) {
    BigInt::BigInt A(123);
    BigInt::BigInt B(456);
    A += B;
    EXPECT_EQ((int)A, 579);
}



TEST(test35, mul1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-123123");
    A *= B;
    EXPECT_EQ(string(A), "-4627323827527401");
}
TEST(test36, mul2) {
    BigInt::BigInt A("-123123");
    BigInt::BigInt B("37582935987");
    A *= B;
    EXPECT_EQ(string(A), "-4627323827527401");
}
TEST(test37, mul3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    A *= B;
    EXPECT_EQ(string(A), "1412477077402939664169");
}
TEST(test38, mul4) {
    BigInt::BigInt A("-37582935987");
    BigInt::BigInt B("-0");
    A *= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test39, mul5) {
    BigInt::BigInt A(123);
    BigInt::BigInt B(456);
    A *= B;
    EXPECT_EQ((int)A, 56088);
}
TEST(test30, sub1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-123123");
    A -= B;
    EXPECT_EQ(string(A), "37583059110");
}
TEST(test31, sub2) {
    BigInt::BigInt A("-123123");
    BigInt::BigInt B("37582935987");
    A -= B;
    EXPECT_EQ(string(A), "-37583059110");
}
TEST(test32, sub3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    A -= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test33, sub4) {
    BigInt::BigInt A("-37582935987");
    BigInt::BigInt B("-37582935987");
    A -= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, sub5) {
    BigInt::BigInt A(123);
    BigInt::BigInt B(456);
    A -= B;
    EXPECT_EQ((int)A, -333);
}
TEST(test34, div1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-37582935987");
    A /= B;
    EXPECT_EQ(string(A), "-1");
}
TEST(test34, div2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("0");
    EXPECT_THROW(A /= B, invalid_argument);
}
TEST(test34, div3) {
    BigInt::BigInt A("123123");
    BigInt::BigInt B("-37582935987");
    A /= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, div4) {
    BigInt::BigInt A("0");
    BigInt::BigInt B("-37582935987");
    A /= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, div5) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B(123123);
    A /= B;
    EXPECT_EQ(string(A), "305247");
}
TEST(test34, xor1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("123123");
    A ^= B;
    EXPECT_EQ(string(A), "37583058752");
}
TEST(test34, xor2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    A ^= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, xor3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("0");
    A ^= B;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test34, xor4) {
    BigInt::BigInt A("123123");
    BigInt::BigInt B("37582935987");
    A ^= B;
    EXPECT_EQ(string(A), "37583058752");
}
TEST(test34, xor5) {
    BigInt::BigInt A("0");
    BigInt::BigInt B("37582935987");
    A ^= B;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test34, mod1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    A %= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, mod2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-123123");
    A %= B;
    EXPECT_EQ(string(A), "9606");
}
TEST(test34, mod3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("0");
    EXPECT_THROW(A %= B, invalid_argument);
}
TEST(test34, mod4) {
    BigInt::BigInt A("0");
    BigInt::BigInt B("37582935987");
    A %= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, mod5) {
    BigInt::BigInt A("123123");
    BigInt::BigInt B("37582935987");
    A %= B;
    EXPECT_EQ(string(A), "123123");
}
TEST(test34, and1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    A &= B;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test34, and2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-123123");
    A &= B;
    EXPECT_EQ(string(A), "37582935809");
}
TEST(test34, and3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("0");
    A &= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, and4) {
    BigInt::BigInt A("0");
    BigInt::BigInt B("37582935987");
    A &= B;
    EXPECT_EQ(string(A), "0");
}
TEST(test34, and5) {
    BigInt::BigInt A("123123");
    BigInt::BigInt B("37582935987");
    A &= B;
    EXPECT_EQ(string(A), "179");
}
TEST(test34, or1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    A |= B;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test34, or2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-123123");
    A |= B;
    EXPECT_EQ(string(A), "68719353791");
}
TEST(test34, or3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("0");
    A |= B;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test34, or4) {
    BigInt::BigInt A("0");
    BigInt::BigInt B("37582935987");
    A |= B;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test34, or5) {
    BigInt::BigInt A("123123");
    BigInt::BigInt B("37582935987");
    A |= B;
    EXPECT_EQ(string(A), "37583058931");
}
TEST(test, unary_plus1) {
    BigInt::BigInt A("37582935987");
    A = +A;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test, unary_plus2) {
    BigInt::BigInt A("-0");
    A = +A;
    EXPECT_EQ(string(A), "0");
}
TEST(test, unary_plus3) {
    BigInt::BigInt A("-37582935987");
    A = +A;
    EXPECT_EQ(string(A), "-37582935987");
}
TEST(test, unary_minus1) {
    BigInt::BigInt A("37582935987");
    A = -A;
    EXPECT_EQ(string(A), "-37582935987");
}
TEST(test, unary_minus2) {
    BigInt::BigInt A("-0");
    A = -A;
    EXPECT_EQ(string(A), "0");
}
TEST(test, unary_minus3) {
    BigInt::BigInt A("-37582935987");
    A = -A;
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test, equal1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    EXPECT_TRUE(A == B);
}
TEST(test, equal2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-37582935987");
    EXPECT_FALSE(A == B);
}
TEST(test, equal3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("123123");
    EXPECT_FALSE(A == B);
}
TEST(test, inequal1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    EXPECT_FALSE(A != B);
}
TEST(test, inequal2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-37582935987");
    EXPECT_TRUE(A != B);
}
TEST(test, inequal3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("123123");
    EXPECT_TRUE(A != B);
}
TEST(test, less1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    EXPECT_FALSE(B < A);
}
TEST(test, less2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-37582935987");
    EXPECT_TRUE(B < A);
}
TEST(test, less3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("123123");
    EXPECT_TRUE(B < A);
}
TEST(test, greater1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    EXPECT_FALSE(A > B);
}
TEST(test, greater2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-37582935987");
    EXPECT_TRUE(A > B);
}
TEST(test, greater3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("123123");
    EXPECT_TRUE(A > B);
}
TEST(test, less_equal1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    EXPECT_TRUE(B <= A);
}
TEST(test, less_equal2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-37582935987");
    EXPECT_TRUE(B <= A);
}
TEST(test, less_equal3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("123123");
    EXPECT_TRUE(B <= A);
}
TEST(test, greater_equal1) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("37582935987");
    EXPECT_TRUE(A >= B);
}
TEST(test, greater_equal2) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("-37582935987");
    EXPECT_TRUE(A >= B);
}
TEST(test, greater_equal3) {
    BigInt::BigInt A("37582935987");
    BigInt::BigInt B("123123");
    EXPECT_TRUE(A >= B);
}
TEST(test, int1) {
    BigInt::BigInt A("123123");
    EXPECT_EQ((int)A, 123123);
}
TEST(test, int2) {
    BigInt::BigInt A("37582935987");
    EXPECT_EQ((int)A, 375829359);
}
TEST(test, int3) {
    BigInt::BigInt A("-37582935987");
    EXPECT_EQ((int)A, -375829359);
}
TEST(test, str1) {
    BigInt::BigInt A("123123");
    EXPECT_EQ(string(A), "123123");
}
TEST(test, str2) {
    BigInt::BigInt A("37582935987");
    EXPECT_EQ(string(A), "37582935987");
}
TEST(test, str3) {
    BigInt::BigInt A("-37582935987");
    EXPECT_EQ(string(A), "-37582935987");
}
TEST(test, size1) {
    BigInt::BigInt A(123123);
    EXPECT_EQ(A.size(), 15);
}
TEST(test, size2) {
    BigInt::BigInt A("123123");
    EXPECT_EQ(A.size(), 15);
}
TEST(test, size3) {
    BigInt::BigInt A("37582935987");
    EXPECT_EQ(A.size(), 19);
}
TEST(test, op_add) {
    BigInt::BigInt A("123123"), B("123000");
    A = A + B;
    EXPECT_EQ(string(A), "246123");
}
TEST(test, op_sub) {
    BigInt::BigInt A("123123"), B("123000");
    A = A - B;
    EXPECT_EQ(string(A), "123");
}
TEST(test, op_mul) {
    BigInt::BigInt A("123123"), B("123000");
    A = A * B;
    EXPECT_EQ(string(A), "15144129000");
}
TEST(test, op_div) {
    BigInt::BigInt A("123123"), B("123000");
    A = A / B;
    EXPECT_EQ(string(A), "1");
}
TEST(test, op_xor) {
    BigInt::BigInt A("123123"), B("123000");
    A = A ^ B;
    EXPECT_EQ(string(A), "139");
}
TEST(test, op_mod) {
    BigInt::BigInt A("123123"), B("123000");
    A = A % B;
    EXPECT_EQ(string(A), "123");
}
TEST(test, op_and) {
    BigInt::BigInt A("123123"), B("123000");
    A = A & B;
    EXPECT_EQ(string(A), "122992");
}
TEST(test, op_or) {
    BigInt::BigInt A("123123"), B("123000");
    A = A | B;
    EXPECT_EQ(string(A), "123131");
}
int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}