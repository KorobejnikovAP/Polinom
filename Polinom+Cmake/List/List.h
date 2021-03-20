#pragma once
#include <iostream>

using namespace std;

template <class T>
class TListElem {
protected:
	T data;
	TListElem* next;
	TListElem* prev;
public:
	TListElem(T data);
	~TListElem();

	T GetData();
	TListElem* GetNext();
	TListElem* GetPrev();

	void SetData(T _data);
	void SetNext(TListElem* _next);
	void SetPrev(TListElem* _prev);

	virtual TListElem<T>* Clone();

	template <class T1>
	friend ostream& operator<<(ostream& out, const TListElem<T1>& A);

	template <class T1>
	friend istream& operator>>(istream& in, TListElem<T1>& A);
};


template <class T>
class TList
{
protected:
	TListElem<T>* root;
	TListElem<T>* end;
	int count;
public:
	TList();
	TList(TList<T>& _v);
	virtual ~TList();

	virtual TList<T>& operator=(TList<T>& _v);

	void InsFirst(T d);
	void InsLast(T d);
	void Ins(TListElem<T>* e, T d);

	int GetCount();
	TListElem<T>* GetFirst();
	TListElem<T>* GetLast();

	void DelFirst();
	void DelLast();
	void Del(TListElem<T>* e);

	template <class T1>
	friend ostream& operator<<(ostream& out, const TList<T1>& A);

	template <class T1>
	friend istream& operator>>(istream& in, TList<T1>& A);
};


template <class T1>
inline ostream& operator<<(ostream& out, const TListElem<T1>& A) {
	out << A.data;
	return out;
}

template<class T1>
inline istream& operator>>(istream& in, TListElem<T1>& A)
{
	in >> A.data;
	return in;
}

template<class T1>
inline ostream& operator<<(ostream& out, const TList<T1>& A)
{
	TListElem<T1>* i = A.root;

	while (i != 0) {
		out << *i << endl;
		i = i->GetNext();
	}

	return out;
}

template<class T1>
inline istream& operator>>(istream& in, TList<T1>& A)
{
	int count;
	in >> count;

	for (int i = 0; i < count; ++i) {
		T1 d;
		in >> d;
		A.InsLast();
	}

	return in;
}

template<class T>
inline TListElem<T>::TListElem(T _data)
{
	data = _data;
	next = 0;
	prev = 0;
}

template<class T>
inline TListElem<T>::~TListElem()
{
	next = 0;
	prev = 0;
}

template<class T>
inline T TListElem<T>::GetData()
{
	return data;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetNext()
{
	return next;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetPrev()
{
	return prev;
}

template<class T>
inline void TListElem<T>::SetData(T _data)
{
	data = _data;
}

template<class T>
inline void TListElem<T>::SetNext(TListElem* _next)
{
	next = _next;
}

template<class T>
inline void TListElem<T>::SetPrev(TListElem* _prev)
{
	prev = _prev;
}

template<class T>
inline TListElem<T>* TListElem<T>::Clone()
{
	TListElem<T>* res = new TListElem<T>(*this);
	return res;
}

template<class T>
inline TList<T>::TList()
{
	root = 0;
	end = 0;
	count = 0;
}

template<class T>
TList<T>::TList(TList<T>& _v)
{
	count = _v.count;

	TListElem<T>* i = _v.root;
	TListElem<T>* j = this->root;
	TListElem<T>* p = 0;

	root = 0;
	end = 0;

	while (i != 0) {
		j = i->Clone();
		j->SetNext(0);

		if (p != 0) {
			p->SetNext(j);
			j->SetPrev(p);
		}

	    p = j;

		if (root == 0)
			root = j;

		end = j;

		i = i->GetNext();
	}
}

template<class T>
TList<T>::~TList()
{
	if (this->root != NULL) {
		TListElem<T>* i = this->root;
		TListElem<T>* p = 0;
		while (i != 0) {
			p = i;
			i = i->GetNext();
			delete p;
		}
		this->root = 0;
		this->end = 0;
		count = 0;
	}
}

template<class T>
TList<T>& TList<T>::operator=(TList<T>& _v)
{
	if (this == &_v)
		return *this;

	if (this->root != 0) {
		TListElem<T>* i = this->root;
		TListElem<T>* p = 0;
		while (i != 0) {
			p = i;
			i = i->GetNext();
			delete p;
		}
		this->root = 0;
		this->end = 0;
		count = 0;
	}

	count = _v.count;

	TListElem<T>* i = _v.root;
	TListElem<T>* j = this->root;
	TListElem<T>* p = 0;

	while (i != 0) {
		j = i->Clone();
		j->SetNext(0);

		if (p != 0) {
			p->SetNext(j);
			j->SetPrev(p);
		}

		p = j;

		if (root == 0)
			root = j;

		end = j;

		i = i->GetNext();
	}
	return *this;
}

template<class T>
inline void TList<T>::InsFirst(T d)
{
	TListElem<T>* tmp = d.Clone();
	tmp->SetNext(root);
	root = tmp;
	if (end == 0)
		end = tmp;
	count++;
}

template<class T>
inline void TList<T>::InsLast(T d)
{
	if (end == 0)
		end = d.Clone();
	else {
		TListElem<T>* tmp = d.Clone();
		tmp->SetNext(end);
		end = tmp;
	}
	if (root == 0)
		root = end;
	count++;
}

template<class T>
inline void TList<T>::Ins(TListElem<T>* e, T d)
{
	TListElem<T> tmp = d.Clone();
	tmp->SetNext(e->GetNext());
	tmp->GetPrev(e);
	e->GetNext()->SetPrev(tmp);
	e->SetNext(tmp);
	count++;
}

template<class T>
inline int TList<T>::GetCount()
{
	return count;
}

template<class T>
inline TListElem<T>* TList<T>::GetFirst()
{
	return root;
}

template<class T>
inline TListElem<T>* TList<T>::GetLast()
{
	return end;
}

template<class T>
inline void TList<T>::DelFirst()
{
	TListElem<T>* i = root;
	root = root->GetNext();
	count--;
	delete i;
}

template<class T>
inline void TList<T>::DelLast()
{
	TListElem<T>* i = end;
	end = end->GetPrev();
	count--;
	delete i;
}

template<class T>
inline void TList<T>::Del(TListElem<T>* e)
{
	e->GetPrev()->SetNext(e->GetNext());
	e->GetNext()->SetPrev(e->GetPrev());
	count--;
	delete e;
}
