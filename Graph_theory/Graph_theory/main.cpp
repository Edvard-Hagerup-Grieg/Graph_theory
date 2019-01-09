#pragma once

#include <stdlib.h>
#include "samples.h"

using namespace std;
void main(int argc, char* argv[])
{
	//	TEST_sampleCHAIN(10, 5);
	//	TEST_sampleDOUBLE(10);
	//	TEST_sampleCUCKOO(10, 2);

	if (argv[1][0] == '0')
		TIME_sampleCHAIN(atoi(argv[2]), atoi(argv[3]));
	else if (argv[1][0] == '1')
		TIME_sampleDOUBLE(atoi(argv[2]));
	else if (argv[1][0] == '2')
		TIME_sampleCUCKOO(atoi(argv[2]), atoi(argv[1]));
	else
	{ 
		cout << "Invalid argument." << endl;
		cin.get();
	}
}