#pragma once
#include <fstream>
#include "List.h"
using namespace std;

const int p = 20;

class TMonomData {
public:
	int Deg; // свертка степеней 
	double K; // коэфицент 

	TMonomData(double* _data = 0, double _K = 0);
	TMonomData(const TMonomData& _v);
	~TMonomData() = default;
};

struct TMonom : public TListElem<TMonomData>
{
	
public:
	TMonom(TMonomData _data);
	TMonom(double* _data = 0, double _K = 0);
	TMonom(const TMonom& _v);
	~TMonom();

	bool operator== (const TMonom& _v);
	bool operator!= (const TMonom& _v);

	TMonomData& operator*(int);
	TMonomData& operator*();

	double GetK();
	void SetK(double _K);

	virtual TMonom* Clone();
	virtual TMonom* GetNext();

	int* GetArrDeg() const;
	string GetMonom();

	TMonom& operator=(const TMonom& _v);

	TMonom operator*(const TMonom& _v);

	TMonom* operator+(const TMonom& _v);
	TMonom* operator-(const TMonom& _v);

	bool operator>(const TMonom& _v);
	bool operator<(const TMonom& _v);

	friend ostream& operator<<(ostream& out, const TMonom& A);
	friend istream& operator>>(istream& in, TMonom& A);
};

