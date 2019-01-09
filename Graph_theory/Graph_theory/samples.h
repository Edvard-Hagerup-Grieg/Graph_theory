#pragma once

#include "hash.h"
#include "omp.h"
#include <time.h>
#include <random>
#include <iostream>

using namespace std;

// [TEST SAMPLES]
void TEST_sampleCHAIN(int n, int m)
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

	int search = 1;
	while (search != 0) {
		int elem = 0;
		cout << "Enter the elemett to delete:\t";
		cin >> elem;
		cout << endl;

		hash.Delete(elem);
		hash.Print();

		cout << "Repeat?\t";
		cin >> search;
		cout << endl;
	}
}

void TEST_sampleDOUBLE(int n)
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

	int search = 1;
	while (search != 0) {
		int elem = 0;
		cout << "Enter the elemett to delete:\t";
		cin >> elem;
		cout << endl;

		hash.Delete(elem);
		hash.Print();

		cout << "Repeat?\t";
		cin >> search;
		cout << endl;
	}
}

void TEST_sampleCUCKOO(int n, int k)
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
		cout << "Enter the elemett to delete:\t";
		cin >> elem;
		cout << endl;

		hash.Delete(elem);
		hash.Print();

		cout << "Repeat?\t";
		cin >> search;
		cout << endl;
	}
}

// [TIME SAMLES]
void TIME_sampleCHAIN(int n, int m)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;
	double ITERATIONS = 1000.0;
	double result_time;
	int index = 0;

	// [RECORD]
	int* a = new int[n + ITERATIONS];
	for (int i = 0; i < n + ITERATIONS; i++)
		a[i] = i + 1;

	random_shuffle(&a[0], &a[n + (int)ITERATIONS - 1]);
	chainHash hash(m);

	for (int i = 0; i < n; i++)
		hash.Insert(a[i]);
	if (n == 10) hash.Print();

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\Graph_theory\\results\\CHAIN_n";
	path = path + to_string(n) + "_m" + to_string(m) + ".txt";

	ofstream outfile;
	outfile.open(path);
	outfile << "CHAIN HASH:\t" << endl;

	// [INSERT]
	cout << "INSERT\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		start = omp_get_wtime();
		hash.Insert(a[n + i]);
		finish = omp_get_wtime();
		hash.Delete(a[n + i]);
		result_time += (finish - start);
	}
	outfile << "INSERT:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	// [DELETE]
	cout << "DELETE\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		index = rand() % n;
		start = omp_get_wtime();
		hash.Delete(a[index]);
		finish = omp_get_wtime();
		hash.Insert(a[index]);
		result_time += (finish - start);
	}
	outfile << "DELETE:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	// [SEARCH]
	cout << "SEARCH\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		index = rand() % n;
		start = omp_get_wtime();
		hash.Search(a[index]);
		finish = omp_get_wtime();
		result_time += (finish - start);
	}
	outfile << "SEARCH:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	outfile.close();
}

void TIME_sampleDOUBLE(int n)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;
	double ITERATIONS = 1000.0;
	double result_time;
	int index = 0;

	// [RECORD]
	int m = 0;

	if (n <= 10)			m = 11;
	else if (n <= 100)		m = 101;
	else if (n <= 1000)		m = 1009;
	else if (n <= 10000)	m = 10007;
	else if (n <= 100000)	m = 100003;
	else if (n <= 1000000)	m = 1000003;

	const int key_values = n * 2 + ITERATIONS;
	int* a = new int[key_values];

	for (int i = 0; i < key_values; i++)
		a[i] = i + 1;

	random_shuffle(&a[0], &a[key_values - 1]);
	doubleHash hash(m);

	for (int i = 0; i < n; i++)
		hash.Insert(a[i]);
	if (n == 10) hash.Print();

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\Graph_theory\\results\\DOUBLE_n";
	path = path + to_string(n) + "_m" + to_string(m) + ".txt";

	ofstream outfile;
	outfile.open(path);
	outfile << "DOUBLE HASH:\t" << endl;

	// [INSERT]
	cout << "INSERT\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		start = omp_get_wtime();
		hash.Insert(a[n + i]);
		finish = omp_get_wtime();
		hash.Delete(a[n + i]);
		result_time += (finish - start);
	}
	outfile << "INSERT:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	// [DELETE]
	cout << "DELETE\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		index = rand() % n;
		start = omp_get_wtime();
		hash.Delete(a[index]);
		finish = omp_get_wtime();
		hash.Insert(a[index]);
		result_time += (finish - start);
	}
	outfile << "DELETE:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	// [SEARCH]
	cout << "SEARCH\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		index = rand() % n;
		start = omp_get_wtime();
		hash.Search(a[index]);
		finish = omp_get_wtime();
		result_time += (finish - start);
	}
	outfile << "SEARCH:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	outfile.close();
}

void TIME_sampleCUCKOO(int n, int k)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;
	double ITERATIONS = 1000.0;
	double result_time;
	int index = 0;

	// [RECORD]
	int m = n;
	int* a = new int[n + ITERATIONS];

	for (int i = 0; i < n + ITERATIONS; i++)
		a[i] = i + 1;

	random_shuffle(&a[0], &a[n + (int)ITERATIONS - 1]);
	cuckooHash hash(m, n, k);

	for (int i = 0; i < n; i++)
		hash.Insert(a[i], 0);
	if (n  == 10) hash.Print();

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\Graph_theory\\results\\CUCKOO_n";
	path = path + to_string(n) + "_m" + to_string(m) + "_k" + to_string(k) + ".txt";

	ofstream outfile;
	outfile.open(path);
	outfile << "CUCKOO HASH:\t" << endl;

	// [INSERT]
	cout << "INSERT\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		start = omp_get_wtime();
		hash.Insert(a[n + i], 0);
		finish = omp_get_wtime();
		hash.Delete(a[n + i]);
		result_time += (finish - start);
	}
	outfile << "INSERT:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	// [DELETE]
	cout << "DELETE\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		index = rand() % n;
		start = omp_get_wtime();
		hash.Delete(a[index]);
		finish = omp_get_wtime();
		hash.Insert(a[index], 0);
		result_time += (finish - start);
	}
	outfile << "DELETE:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	// [SEARCH]
	cout << "SEARCH\t";
	result_time = 0;
	for (int i = 0; i < ITERATIONS; i++)
	{
		index = rand() % n;
		start = omp_get_wtime();
		hash.Search(a[index]);
		finish = omp_get_wtime();
		result_time += (finish - start);
	}
	outfile << "SEARCH:\t" << (result_time / ITERATIONS) << endl;
	cout << "TIME:\t" << (result_time / ITERATIONS) << endl;

	outfile.close();
}