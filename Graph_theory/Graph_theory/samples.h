#pragma once

#include "hash.h"
#include <time.h>
#include <random>
#include <iostream>

using namespace std;

void sampleCHAIN(int n, int m) 
{
	srand(static_cast<unsigned int>(time(0)));

	int* a = new int[n];

	for (int i = 0; i < n; i++)
		a[i] = i + 1;

	random_shuffle(&a[0], &a[n - 1]);
	chainHash hash(m);

	for (int i = 0; i < n; i++)
		hash.Insert(a[i]);

	hash.Print();
	cin.get();
}

void sampleDOUBLE(int n)
{
	srand(static_cast<unsigned int>(time(0)));

	int m = 0;

	if (n <= 10)			m = 11;
	else if (n <= 100)		m = 101;
	else if (n <= 1000)		m = 1009;
	else if (n <= 10000)	m = 10007;
	else if (n <= 100000)	m = 100003;
	else if (n <= 1000000)	m = 1000003;

	const int key_values = n * 3;
	int* a = new int[key_values];

	for (int i = 0; i < key_values; i++)
		a[i] = i + 1;

	random_shuffle(&a[0], &a[key_values - 1]);
	doubleHash hash(m);

	for (int i = 0; i < n; i++)
		hash.Insert(a[i]);

	hash.Print();
	cin.get();
}

void sampleCUCKOO(int n, int k)
{
	srand(static_cast<unsigned int>(time(0)));

	int m = n;
	int* a = new int[n];

	for (int i = 0; i < n; i++)
		a[i] = i + 1;

	random_shuffle(&a[0], &a[n - 1]);
	cuckooHash hash(m, n, k);

	for (int i = 0; i < n; i++)
		hash.Insert(a[i], 0);

	hash.Print();
	cin.get();

	int search = 1;
	while (search != 0) {
		int elem = 0;
		cin >> elem;
		if (hash.Search(elem)) cout << "The element is found." << endl;
		else cout << "The element is not found." << endl;
		cout << "Repeat?\t";
		cin >> search;
		cout << endl;
	}
}
