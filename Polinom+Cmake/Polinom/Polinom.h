#pragma once
#include"Monom.h"
#include "List.h"
#include <iostream>


using namespace std;


class TPolinom : public TList<TMonomData>
{

public:
	TPolinom();
	TPolinom(TPolinom& _v);
	~TPolinom();

	bool operator==(const TPolinom& _v);

	double calc(double i, double j, double k);

	TPolinom& operator=(const TPolinom& _v);
	TPolinom& operator+=(TMonom& _v);

	TPolinom operator*(const TPolinom& _v);
	TPolinom operator+(const TPolinom& _v);
	TPolinom operator-(const TPolinom& _v);

	friend ostream& operator <<(ostream& ostr, const TPolinom& P);
	friend istream& operator >>(istream& istr, TPolinom& P);

	string GetPolinom();
};

