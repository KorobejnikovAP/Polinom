
#include <iostream>

#include "Monom.h"
#include "Polinom.h"

using namespace std;

int main() {
	TMonom a(new double[3]{1, 2, 3}, 1);
	TMonom b(new double[3]{3, 2, 1}, 1);

	TMonom c(new double[3]{ 1, 1, 1 }, 1);
	TMonom d(new double[3]{ 2, 2, 2 }, 1);


	TPolinom P1, P2, P3;

	P1 += a;
	P1 += b;

	P2 += c;
	P2 += d;

	P3 = P2 * P1 ;
	cout << P3 << endl;
	cout << P3.calc(2, 2, 2) << endl;

	P3 = P2 + P1;
	cout << P3 << endl;
	cout << P3.calc(2, 2, 2) << endl;

	P3 = P2 - P1;
	cout << P3 << endl;
	cout << P3.calc(2, 2, 2) << endl;

}

