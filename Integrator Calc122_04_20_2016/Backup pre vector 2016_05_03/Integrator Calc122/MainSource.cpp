//Christopher Settles

//To do list:
/*
Collect terms function that takes the array and collects all like terms. 
Like terms are ones where the incoef, sinexp, cosexp, and xexp are the same between all terms.

We want fractions for the inner coef and outercoef
Fraction class needs a fraction plus fraction function, add fractions to ints. fractions times int and fraction divided by ints. 
*/
#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <string>
#include "MainSource.h"
#include "crsmath.h"
#include "TrigTerm.h"
using namespace std;
void printIntegral(TrigTerm &, string);
int main()
{ 
	/* These are a bunch of test cases
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			TrigTerm Jimmy(1.0, 1.0, i, j);
			printIntegral(Jimmy, "The integral of " + Jimmy.toString() + " : \n");
		}
	}
	*/
	int sinexp, cosexp;
	cout << "Enter the sin exp and cos exp" << endl;
	cout << "Sin^:";
	cin >> sinexp;
	cout << "Cos^:";
	cin >> cosexp;


	TrigTerm Jimmy(1.0, 1.0, sinexp,cosexp);
	printIntegral(Jimmy, "The integral of " + Jimmy.toString() + " : \n");
	return 0;
}
void printIntegral(TrigTerm &printee, string text) {
	cout << text;
	printee.initialize();
	printee.Integrate();
	printee.combineLikeTerms();

	list<TrigTerm>::iterator iter;
	list<TrigTerm> trig_list = printee.getList();
	for (iter = trig_list.begin(); iter != trig_list.end(); iter++) {
		cout << iter->toString() <<" + \n" ;
	}
	cout << "c" <<endl <<endl;

}
