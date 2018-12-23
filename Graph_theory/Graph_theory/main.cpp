#pragma once

#include "hash.h"
#include <time.h>
#include <random>

using namespace std;

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(0)));

	const int n = 10;
	int a[n];

	doubleHash hash(n);
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100;
		hash.Insert(a[i]); 
	}
	hash.Print();
	
	cin.get();
	return 1;
}