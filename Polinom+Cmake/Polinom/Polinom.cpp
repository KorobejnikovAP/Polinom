#include "Polinom.h"
#include <math.h>

TPolinom::TPolinom() : TList<TMonomData>()
{
}

TPolinom::TPolinom(TPolinom& _v) : TList<TMonomData>(_v)
{
}

TPolinom::~TPolinom()
{
}

bool TPolinom::operator==(const TPolinom& _v)
{
	if (this->count != _v.count)
		return false;
	TMonom* tmp = static_cast<TMonom*>(this->root);
	TMonom* tmp1 = static_cast<TMonom*>(_v.root);
	while(tmp != 0)
	{
		if (*tmp != *tmp1 || tmp->GetK() != tmp1->GetK())
			return false;
		tmp = tmp->GetNext();
		tmp1 = tmp1->GetNext();
	}
	return true;
}

double TPolinom::calc(double x, double y, double z)
{
	double res = 0;
	TMonom* tmp = static_cast<TMonom*>(this->root);
	int* s;
	while (tmp != 0) {
		s = tmp->GetArrDeg();
		res += tmp->GetK() * exp(s[0] * log(x))
			               * exp(s[1] * log(y))
			               * exp(s[2] * log(z));
		tmp = tmp->GetNext();
	}
	return res;
}



TPolinom& TPolinom::operator=(const TPolinom& _v)
{
	if (this == &_v) {
		return *this;
	}

	if (this->root != 0)
	{
		TMonom* i = static_cast<TMonom*>(this->root);
		TMonom* p = 0;
		while (i != 0)
		{
			p = i;
			i = i->GetNext();
			delete p;
		}
		root = 0;
		end = 0;
		count = 0;
	}
	
	TMonom* i = static_cast<TMonom*>(_v.root);
	while (i != 0)
	{
		*this += *i;
		i = i->GetNext();
	}

	return *this;
}

TPolinom& TPolinom::operator+=(TMonom& _v)
{
	if (this->root == 0) {
		this->root = _v.Clone();
		this->end = this->root;
		this->count++;
	}
	else {
		TMonom* tmp = static_cast<TMonom*>(this->root);
		while (tmp != 0) {
			if (*tmp == _v) {
				tmp->SetK(tmp->GetK() + _v.GetK());
				return *this;
			}
			else {
				TMonom* _v2 = _v.Clone();
				if (*tmp < _v) {
					_v2->SetPrev(tmp->GetPrev());
					_v2->SetNext(tmp);

					if (tmp->GetPrev() != 0)
						tmp->GetPrev()->SetNext(_v2);
					else
						this->root = _v2;

					tmp->SetPrev(_v2);
					this->count++;
					return *this;
				}
				else
					if (tmp->GetNext() == 0) {
						_v2->SetPrev(tmp);
						tmp->SetNext(_v2);
						this->end = _v2;
						this->count++;
						return *this;
					}
					else
						tmp = tmp->GetNext();
			}
		}
	}
	return *this;
}

TPolinom TPolinom::operator*(const TPolinom& _v)
{
	TPolinom res;
	TMonom* tmp1 = static_cast<TMonom*>(root);
	if (this->root == 0 && _v.root == 0)
		throw - 1;
	while (tmp1 != 0) {
		TMonom* tmp2 = static_cast<TMonom*>(_v.root);
		while (tmp2 != 0) {
			TMonom tmp3;
			tmp3 = *tmp2 * *tmp1;
			res += tmp3;
			tmp2 = tmp2->GetNext();
		}
		tmp1 = tmp1->GetNext();
	}
	return res;
}

TPolinom TPolinom::operator+(const TPolinom& _v)
{
	if (this->root == 0 && _v.root == 0)
		throw - 1;

	TPolinom res;
	TMonom* tmp1 = static_cast<TMonom*>(root);
	TMonom* tmp2 = static_cast<TMonom*>(_v.root);
	TMonom* r = 0;
	
	while (tmp1 != 0 && tmp2 != 0) {
		TMonom tmp3;
		if (*tmp1 == *tmp2) {
		    tmp3 = (*tmp1 + *tmp2)[0];
			tmp1 = tmp1->GetNext();
			tmp2 = tmp2->GetNext();
		}
		else {
			if (*tmp1 > * tmp2) {
				tmp3 = *tmp1;
				tmp1 = tmp1->GetNext();
			}
			else {
				tmp3 = *tmp2;
				tmp2 = tmp2->GetNext();
			}
		}

		if (r == 0) {
			res += tmp3;
			r = static_cast<TMonom*>(res.root);
		}
		else {
			r->SetNext(tmp3.Clone());
			r->GetNext()->SetPrev(r);
			r = r->GetNext();
		}
	}
		
	if (tmp1 != 0)
		while (tmp1 != 0)
		{
			r->SetNext(tmp1->Clone());
			r->GetNext()->SetPrev(r);
			r = r->GetNext();
			tmp1 = tmp1->GetNext();
		}
	else if (tmp2 != 0)
		while (tmp2 != 0)
		{
			r->SetNext(tmp2->Clone());
			r->GetNext()->SetPrev(r);
			r = r->GetNext();
			tmp2 = tmp2->GetNext();
		}
		
	return res;
}

TPolinom TPolinom::operator-(const TPolinom& _v)
{
	if (_v.root == 0 || this->root == 0)
		throw - 1;

	TPolinom res;
	TMonom* tmp1 = static_cast<TMonom*>(root);
	TMonom* tmp2 = static_cast<TMonom*>(_v.root);
	TMonom* r = 0;

	while (tmp1 != 0 && tmp2 != 0) {
		TMonom tmp3;
		if (*tmp1 == *tmp2) {
			tmp3 = (*tmp1 - *tmp2)[0];
			tmp1 = tmp1->GetNext();
			tmp2 = tmp2->GetNext();
		}
		else {
			if (*tmp1 < *tmp2) {
				TMonom* t = static_cast<TMonom*>(tmp2->Clone());
				t->SetK(t->GetK() * (-1));
				tmp3 = *t;
				tmp2 = tmp2->GetNext();
			}
			else {
				tmp3 = *tmp1;
				tmp1 = tmp1->GetNext();
			}
		}
		if (r == 0) {
			res += tmp3;
			r = static_cast<TMonom*>(res.root);
		}
		else {
			r->SetNext(tmp3.Clone());
			r->GetNext()->SetPrev(r);
			r = r->GetNext();
		}
	}

	if (tmp1 != 0)
		while (tmp1 != 0) {
			r->SetNext(tmp1->Clone());
			r->GetNext()->SetPrev(r);
			r = r->GetNext();
			tmp1 = tmp1->GetNext();
		}
	else if (tmp2 != 0)
		while (tmp2 != 0)
		{
			TMonom* tt = static_cast<TMonom*>(tmp2->Clone());
			tt->SetK(tt->GetK() * (-1));
			r->SetNext(tt);
			r->GetNext()->SetPrev(r);
			r = r->GetNext();
			tmp2 = tmp2->GetNext();
		}
	return res;
}


ostream& operator<<(ostream& ostr, const TPolinom& P)
{
	if (P.count == 0)
		return ostr;

	TMonom* i = static_cast<TMonom*>(P.root);
	ostr << *i;
	i = i->GetNext();

	while (i != 0)
	{
		if (i->GetK() > 0)
			ostr << "+";
		ostr << *i;
		i = i->GetNext();
	}
	return ostr;
}

istream& operator>>(istream& istr, TPolinom& P)
{
	int count;
	istr >> count;
	TPolinom res;
	for (int i = 0; i < count; i++)
	{
		TMonom tmp;
		istr >> tmp;
		res += tmp;
	}
	P = res;
	return istr;
}

string TPolinom::GetPolinom()
{
	string res = "";
	TMonom* i = static_cast<TMonom*>(root);
	while (i != 0)
	{
		res += i->GetMonom();
		i = i->GetNext();
	}
	return res;
}