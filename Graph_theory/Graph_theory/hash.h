#pragma once

#include <random>
#include <iostream>
#include <string>
#include <list> 
#include <time.h>
#include <math.h>

using namespace std;

// [HASH-FUNCTIONS]
class hashFunction {
private:
	int a;
	int b;
	int m;
public:
	hashFunction() { a = 0, b = 0, m = 0; };
	hashFunction(const int m, int a, int b) {
		this->m = m;
		this->a = a;
		this->b = b;
	}

	int geta() { return a; };
	int getb() { return b; };
	int getm() { return m; };

	int operator()(int key) { return (a * key + b) % m; }
	void operator=(hashFunction h) { a = h.geta(), b = h.getb(), m = h.getm(); }
};

class chainHashFunction {
private:
	int p = 1021;
	int a;
	int b;
	int m;
public:
	chainHashFunction() { a = 0, b = 0, m = 0; };
	chainHashFunction(const int m) {
		if		(m <= 10)		p = 11;
		else if (m <= 100)		p = 101;
		else if (m <= 1000)		p = 1009;
		else if (m <= 10000)	p = 10007;
		else if (m <= 100000)	p = 100003;
		else if (m <= 1000000)	p = 1000003;
		else cout << "n must be less then 1 000 001" << endl;
		this -> m = m;
		a = rand() % p;
		b = 1 + rand() % (p - 1);
	}
	chainHashFunction(const int m, int a, int b) {
		this->m = m;
		this->a = a;
		this->b = b;
	}

	int geta() { return a; };
	int getb() { return b; };
	int getm() { return m; };
	int getp() { return p; };

	int operator()(int key) { return ((a * key + b) % p) % m; }
	void operator=(chainHashFunction h) { a = h.geta(), b = h.getb(), m = h.getm(); }
};

class doubleHashFunction {
private:
	hashFunction h1;
	hashFunction h2;
	int m;  //ïðîñòîå
public:
	doubleHashFunction() { m = 0; };
	doubleHashFunction(const int m) {
		hashFunction func1(m, 1, 0);
		hashFunction func2(m - 1, 1, 0);
		h1 = func1;
		h2 = func2;
		this->m = m;
	}

	int getm() { return m; };

	int operator()(int key, int iter) { return (h1(key) + iter * (1 + h2(key))) % m; }
	void operator=(doubleHashFunction h) { m = h.getm(); h1 = h.h1; h2 = h.h2; }
};

class kIndependentHashFunction {
private:
	int p = 1021;
	int* a;
	int k;
	int m;
public:
	kIndependentHashFunction() { };
	kIndependentHashFunction(const int m, int k) {
		if (m <= 10)			p = 11;
		else if (m <= 100)		p = 101;
		else if (m <= 1000)		p = 1009;
		else if (m <= 10000)	p = 10007;
		else if (m <= 100000)	p = 100003;
		else if (m <= 1000000)	p = 1000003;
		else cout << "n must be less then 1 000 001" << endl;
		this->m = m;
		this->k = k;
		a = new int[k];

		for(int i = 0; i < k; i++)
			a[i] = rand() % p;
	}

	int* geta() { return a; };
	int getk() { return k; };
	int getm() { return m; };
	int getp() { return p; };

	int operator()(int key) 
	{ 
		int poly = 0;
		for (int i = 0; i < k; i++)
			poly += a[i] * pow(key, k - i - 1);
		return (poly % p) % m; 
	}
	void operator=(kIndependentHashFunction h) { a = h.geta(), k = h.getk(), m = h.getm(); }
};


// [TABLE]
class tableHash {
private:
	int m;
	int* table;
	chainHashFunction h;
public:
	tableHash() {};
	tableHash(const int m);

	void Insert(int x);
	void Delete(int key);
	void Print();
	bool Search(int key);
};

// [CHAIN]
class chainHash {
private:
	int m;
	chainHashFunction h;
	list<int> *table;
public:
	chainHash(const int m);

	void Insert(int x);
	void Delete(int key);
	void Print();
	bool Search(int key);
};

// [DOUBLE]
class doubleHash {
private:
	int m;
	int* table;
	doubleHashFunction h;
public: 
	doubleHash(const int m);

	void Insert(int x);
	void Delete(int key);
	void Print();
	bool Search(int key);
};

// [ÑUCKOO]
class cuckooHash
{
private:
	int m;
	int limit;
	int depth = 0;
	int* table1;
	int* table2;
	kIndependentHashFunction h1;
	kIndependentHashFunction h2;
public:
	cuckooHash(const int m, int n, int k);

	void Insert(int x, int num_table);
	void Delete(int key, int num_table);
	void Print();
	void Rehash();
	bool Search(int key);
};


// [TABLE]
tableHash::tableHash(const int m)
{
	this->m = m;
	chainHashFunction func(m);
	h = func;

	for (int i = 0; i < m; i++)
		table[i] = NULL;
}

void tableHash::Insert(int key)
{
	int index = h(key);
	table[index] = key;
}

void tableHash::Delete(int key)
{
	int index = h(key);
	table[index] = NULL;
}

void tableHash::Print()
{
	cout << "TABLE HASH:" << endl;

	for (int i = 0; i < m; i++) 
		cout << table[i] << "\t";

	cout << endl;
}

bool tableHash::Search(int key) {
	int index = h(key);

	if (table[index] == key)
			return true;

	return false;
}

// [CHAIN]
chainHash::chainHash(const int m)
{
	this -> m = m;
	chainHashFunction func(m);
	h = func;
	table = new list<int>[m];
}

void chainHash::Insert(int key)
{
	int index = h(key);
	table[index].push_back(key);
}

void chainHash::Delete(int key)
{
	int index = h(key);

	typename list <int>::iterator i;
	for (i = table[index].begin(); i != table[index].end(); i++) {
		if (*i == key)
			break;
	}

	if (i != table[index].end())
		table[index].erase(i);
}

void chainHash::Print()
{
	cout << "CHAIN METOD:" << endl;

	for (int i = 0; i < m; i++) {
		cout << i;
		for (auto x : table[i])
			cout << " --> " << x;
		cout << endl;
	}
}

bool chainHash::Search(int key) {
	int index = h(key);

	typename list <int>::iterator i;
	for (i = table[index].begin(); i != table[index].end(); i++) {
		if (*i == key)
			return true;
	}
	
	return false;
}

// [DOUBLE]
doubleHash::doubleHash(const int m)
{
	this->m = m;
	doubleHashFunction func(m);
	h = func;
	table = new int[m];

	for (int i = 0; i < m; i++)
		table[i] = NULL;
}

void doubleHash::Insert(int key)
{	
	int iter = 0;
	int index = h(key, iter);
	while (iter != m) 
	{
		if (table[index] == NULL)
		{
			table[index] = key;
			return;
		}
		iter++;
		index = h(key, iter);
	}

	cout << "Error: The table is full. Key: " << key << endl;
}

void doubleHash::Delete(int key)
{
	int iter = 0;
	int index = h(key, iter);
	while (iter != m)
	{
		if (table[index] == key)
		{
			table[index] = NULL;
			return;
		}
		iter++;
		index = h(key, iter);
	}

	cout << "Error: The key is not found." << endl;
}

void doubleHash::Print() 
{
	cout << "DOUBLE HASHING" << endl;
	cout << "KEY: \t HASH-VALUE:" << endl;

	for (int i = 0; i < m; i++) {
		cout << table[i] << "\t" << h(table[i], 0);
		cout << endl;
	}
}

bool doubleHash::Search(int key) 
{
	int iter = 0;
	int index = h(key, iter);
	while (iter != m)
	{
		if (table[index] == key)
			return true;
		iter++;
		index = h(key, iter);
	}

	return false;
}

// [ÑUCKOO]
cuckooHash::cuckooHash(const int m, int n, int k)
{
	limit = log(n);
	this->m = m;
	kIndependentHashFunction func1(m, k);
	kIndependentHashFunction func2(m, k);
	h1 = func1;
	h2 = func2;
	table1 = new int[m];
	table2 = new int[m];

	for (int i = 0; i < m; i++)
	{
		table1[i] = NULL;
		table2[i] = NULL;
	}
}

void cuckooHash::Insert(int key, int num_table)
{
	if (depth > limit)
	{
		depth = 0;
		Rehash();
	}

	int tmp = 0;
	int index1 = h1(key);
	int index2 = h2(key);

	if (num_table == 0)
	{
		if (table1[index1] == NULL) 
		{
			depth = 0;
			table1[index1] = key;
		}
		else
		{ 
			depth++;
			tmp = table1[index1];
			table1[index1] = key;
			Insert(tmp, 1);
		}
	}
	else
	{
		if (table2[index2] == NULL)
		{ 
			depth = 0;
			table2[index2] = key;
		}
		else
		{
			depth++;
			tmp = table2[index2];
			table2[index2] = key;
			Insert(tmp, 0);
		}
	}
}

void cuckooHash::Delete(int key, int num_table)
{
	int index1 = h1(key);
	int index2 = h2(key);

	if (table1[index1] == key)
		table1[index1] == NULL;
	else if (table2[index2] == key)
		table2[index2] == NULL;
	else
		cout << "Error: The key is not found." << endl;
}

void cuckooHash::Print()
{
	cout << "CUCKOO HASHING" << endl;

	for (int i = 0; i < m; i++) 
	{
		if(table1[i] == NULL)
			cout << "_\t";
		else
			cout << table1[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < m; i++)
	{
		if (table2[i] == NULL)
			cout << "_\t";
		else
			cout << table2[i] << "\t";
	}
	cout << endl;
}

void cuckooHash::Rehash()
{
	kIndependentHashFunction func1(h1.getm(), h1.getk());
	kIndependentHashFunction func2(h2.getm(), h2.getk());
	h1 = func1;
	h2 = func2;

	int* _table1 = new int[m];
	int* _table2 = new int[m];

	for (int i = 0; i < m; i++)
	{
		_table1[i] = table1[i];
		_table2[i] = table2[i];

		table1[i] = NULL;
		table2[i] = NULL;
	}

	for (int i = 0; i < m; i++)
	{
		if (_table1[i] != NULL) Insert(_table1[i], 0);
		if (_table2[i] != NULL) Insert(_table2[i], 0);
	}
}

bool cuckooHash::Search(int key)
{
	int index1 = h1(key);
	int index2 = h2(key);

	if (table1[index1] == key)
		return true;
	else if (table2[index2] == key)
		return true;
	else
		return false;
}