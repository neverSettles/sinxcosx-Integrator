//Christopher Settles
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "crsmath.h"
using namespace std;

long long fact(int number)
{
	long long rv = 1;

	if (number == 0)
		return 1;

	for (int i = number; i > 0; i--)
	{
		rv *= i;
	}
	return rv;
}

long long nCr(int exp, int place)
{
	if (place > exp)
		return 0;
	long long rv = fact(exp) / (fact(place)*fact(exp - place));
	return rv;
}