#include "Polinom.h"
#include <../gtest/gtest.h>


TEST(TPolinom, can_create_polinom)
{
	ASSERT_NO_THROW(TPolinom());
}

TEST(TPolinom, correctly_operator_eq) {


	TMonom a1(new double[3]{ 5, 2, 5 }, 3);
	TMonom a2(new double[3]{ 4, 3, 3 },-5);
	TMonom a3(new double[3]{ 3, 5, 1 }, 7);

	TMonom b1(new double[3]{ 3, 2, 6 }, 4);
	TMonom b2(new double[3]{ 2, 1, 8 },-6);

	TPolinom A, B, C, D;

	A += a1;
	A += a2;
	A += a3;

	B += b1;
	B += b2;

	C += a1;
	C += a2;
	C += a3;
	C += b1;
	C += b2;
	D = A + B;

	ASSERT_TRUE(D == C);
}

TEST(TPolinom, can_assignment_plus)
{
	TPolinom P;
	TMonom a(new double[3]{ 1,1,1 }, -1);
	ASSERT_NO_THROW(P += a);
}


TEST(TPolinom, can_multiply)
{
	TPolinom P, P1, P2;
	TMonom a(new double[3]{ 1,1,1 }, -1);
	TMonom b(new double[3]{ 2,2,2 }, 1);
	P1 += a;
	P1 += b;
	TMonom c(new double[3]{ 3,2,1 }, 1);
	TMonom d(new double[3]{ 1,2,3 }, -1);
	P2 += c;
	P2 += d;
	P = P1 * P2;
	string res = P.GetPolinom();
	string expP = "1543-1432-13451234";
	EXPECT_EQ(expP, res);
}

TEST(TPolinom, can_plus)
{
	TPolinom P, P1, P2;
	TMonom a(new double[3]{ 1,1,1 }, -1);
	TMonom b(new double[3]{ 2,2,2 }, 1);
	P1 += a;
	P1 += b;
	TMonom c(new double[3]{ 3,2,1 }, 1);
	TMonom d(new double[3]{ 1,2,3 }, -1);
	P2 += c;
	P2 += d;
	P = P1 + P2;
	string res = P.GetPolinom();
	string expP = "13211222-1123-1111";
	EXPECT_EQ(expP, res);
}

TEST(TPolinom, can_sub)
{

	TPolinom P, P1, P2;
	TMonom a(new double[3]{ 1,1,1 }, -1);
	TMonom b(new double[3]{ 2,2,2 }, 1);
	P1 += a;
	P1 += b;
	TMonom c(new double[3]{ 3,2,1 }, 1);
	TMonom d(new double[3]{ 1,2,3 }, -1);
	P2 += c;
	P2 += d;
	P = P1 - P2;
	string res = P.GetPolinom();
	string expP = "-132112221123-1111";
	EXPECT_EQ(expP, res);
}