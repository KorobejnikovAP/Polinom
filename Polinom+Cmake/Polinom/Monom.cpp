#include "Monom.h"

	

TMonom::TMonom(TMonomData _data):TListElem<TMonomData>(_data)
{
}

TMonom::TMonom(double* _data, double _K) : TListElem<TMonomData>(0)
{
	if (_data != NULL)
		data.Deg = _data[0] * p * p + _data[1] * p + _data[2];
	else
		data.Deg = 0;
	data.K = _K;
}

TMonom::TMonom(const TMonom& _v) : TListElem<TMonomData>(_v)
{
	prev = 0;
	next = 0;
}

TMonom::~TMonom()
{
}

bool TMonom::operator==(const TMonom& _v)
{
	if (data.Deg > 0)
		return data.Deg == _v.data.Deg;
	else {
		return data.K == _v.data.K;
	}
}

bool TMonom::operator!=(const TMonom& _v)
{
	return !this->operator==(_v);
}

TMonomData& TMonom::operator*(int)
{
	return data;
}

TMonomData& TMonom::operator*()
{
	return data;
}

double TMonom::GetK()
{
	return data.K;
}

void TMonom::SetK(double _K)
{
	data.K = _K;
}

TMonom* TMonom::Clone()
{
	TMonom* res = new TMonom(*this);
	return res;
}

TMonom* TMonom::GetNext()
{
	return static_cast<TMonom*>(next);
}

TMonom& TMonom::operator=(const TMonom& _v)
{
	if (this == &_v)
		return *this;

	next = 0;
	prev = 0;

	data.K = _v.data.K;
	data.Deg = _v.data.Deg;

	return *this;
}



TMonom TMonom::operator*(const TMonom& _v)
{
	int* s1 = this->GetArrDeg();
	int* s2 = _v.GetArrDeg();
	TMonom tmp;
	tmp.data.K = data.K * _v.data.K;
	tmp.data.Deg = (s1[0] + s2[0]) * p * p + (s1[1] + s2[1]) * p + (s1[2] + s2[2]);

	return tmp;
}

TMonom* TMonom::operator+(const TMonom& _v)
{
	TMonom* tmp = 0;

	if (*this == _v) {
		tmp = new TMonom(*this);
		tmp->data.K = this->data.K + _v.data.K;
	}
	else {
		tmp = new TMonom[2];
		if (*this > _v) {
			tmp[0] = *this;
			tmp[1] = _v;
		}
		else {
			tmp[0] = _v;
			tmp[1] = *this;
		}
	}

	return tmp;
}

TMonom* TMonom::operator-(const TMonom& _v)
{
	TMonom* tmp = 0;

	if (*this == _v) {
		tmp = new TMonom(*this);
		tmp->data.K = this->data.K - _v.data.K;
	}
	else {
		tmp = new TMonom[2];
		if (*this > _v) {
			tmp[0] = *this;
			tmp[1] = _v;
		}
		else {
			tmp[0] = _v;
			tmp[1] = *this;
		}
	}

	return tmp;
}

bool TMonom::operator>(const TMonom& _v)
{

	if (data.Deg > 0) {
		return data.Deg > _v.data.Deg;
	}
	else {
		return data.K > _v.data.K;
	}
}

bool TMonom::operator<(const TMonom& _v)
{
	if (data.Deg > 0) {
		return data.Deg < _v.data.Deg;
	}
	else {
		return data.K < _v.data.K;
	}
}

ostream& operator<<(ostream& out, const TMonom& A)
{
	out << A.data.K << "*";
	int* arrDeg = A.GetArrDeg();
	out << "x^" << arrDeg[0];
	out << "y^" << arrDeg[1];
	out << "z^" << arrDeg[2];
	out << " ";
	return out;
}

istream& operator>>(istream& in, TMonom& A)
{
	int s = 0;
	int tmp;
	in >> A.data.K;
	in >> tmp;
	s += tmp * p * p;
	in >> tmp;
	s += tmp * p;
	in >> tmp;
	s += tmp;
	A.data.Deg = s;

	return in;
}


TMonomData::TMonomData(const TMonomData& _v)
{
	Deg = _v.Deg;
	K = _v.K;
}

TMonomData::TMonomData(double* _data, double _K)
{
	K = _K;
	if (_data != NULL)
		Deg = _data[0] * p * p + _data[1] * p + _data[2];
	else
		Deg = 0;
}


int* TMonom::GetArrDeg() const
{
	int* res = new int[3];
	res[0] = data.Deg / (p * p);
	res[1] = (data.Deg % (p * p)) / p;
	res[2] = data.Deg % p;

	return res;
}

string TMonom::GetMonom()
{
	int* arrDeg = this->GetArrDeg();
	string res = "";
	if (data.K < 0)
	{
		res += "-";
		res += data.K * (-1) + '0';
	}
	else
		res += data.K + '0';
	for (int i = 0; i < 3; i++)
		res += arrDeg[i] + '0';
	return res;
}