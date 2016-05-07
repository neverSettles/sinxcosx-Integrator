#pragma once
//Christopher Settles
#include <iostream>
#include <iomanip>
#include <string>
#include "TrigTerm.h"
using namespace std;

class TrigArray {
private:
	TrigTerm TrigTermArray[10];
public:

	//Constructor
	//TrigArray();

	//Useful functions
	string toString();
	void simplify();

};