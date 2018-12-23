#pragma once

#include <random>
#include <iostream>
#include <string>
#include <list> 
#include <time.h>

using namespace std;

// [HASH-FUNCTION]
class hashFunction {
private:
	const int p = 1021;
	int a;
	int b;
	int m;
public:
	hashFunction() { a = 0, b = 0, m = 0; };
	hashFunction(const int m) {
		this -> m = m;
		a = rand() % p;
		b = 1 + rand() % (p - 1);
	}

	hashFunction(const int m, int a, int b) {
		this->m = m;
		this->a = a;
		this->b = b;
	}

	int geta() { return a; };
	int getb() { return b; };
	int getm() { return m; };
	int getp() { return p; };

	int operator()(int key) { return ((a * key + b) % p) % m; }
	void operator=(hashFunction h) { a = h.geta(), b = h.getb(), m = h.getm(); }
};

class doubleHashFunction {
private:
	hashFunction h1;
	hashFunction h2;
	int m;  //простое
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


// [CHAIN]
class chainHash {
private:
	int m;
	hashFunction h;
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

// [GRAPH]
class graphHash {}; 


//[CHAIN]
chainHash::chainHash(const int m)
{
	this -> m = m;
	hashFunction func(m);
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

//[DOUBLE]
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



