//Christopher Settles
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <iterator>
using namespace std;

class TrigTerm {
private:
	double outcoef;
	int incoef;
	int sinexp;
	int cosexp;
	int xexp;
//	static list<TrigTerm> trig_list; //needs to be in thbe cpp file

public:
	//Getter functions and setter functions were not needed and never used, so I deleted them. 

	//Constructor
	TrigTerm(double =0, double =0, int =0, int =1, int = 0);
	void TrigTerm::initialize();

	void Integrate();
	void evenIntegrate();
	void oddIntegrate();

	//Useful functions
	string toString();

	list<TrigTerm>& getList();
	void TrigTerm::combineLikeTerms();

};

