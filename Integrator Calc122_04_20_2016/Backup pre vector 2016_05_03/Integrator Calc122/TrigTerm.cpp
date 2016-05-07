//Christopher Settles
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <sstream>
#include <list>
#include <iterator>
#include <cmath>
#include "TrigTerm.h"
#include "crsmath.h"
using namespace std;

static list<TrigTerm> trig_list; //did not work when placed in the .h file


TrigTerm::TrigTerm(double _outcoef, double _incoef, int _sinexp, int _cosexp, int _xexp) {
	outcoef = _outcoef;
	incoef = _incoef;
	sinexp = _sinexp;
	cosexp = _cosexp;
	xexp = _xexp;
}

void TrigTerm::initialize()
{
	trig_list.clear();
}

string TrigTerm::toString() 
{
	string rv = "";
	ostringstream os;
	os << fixed << setprecision(3) << showpoint;
	if (outcoef == 0) {
		os << 0;
		return os.str();
	}
		
	os << outcoef << "*";
	if (xexp > 0)
		os << "x^" << xexp;
	if (sinexp > 0)
		os << "sin^" << sinexp << "(" << incoef << "x) ";
	if (cosexp > 0)
		os << "cos^" << cosexp << "(" << incoef <<  "x)";
	rv = os.str();
	return rv;
/*	char output[40];
	sprintf_s(output, "%.3f*sin^%i(%.3fx) * cos^%i(%.3fx)", outcoef,sinexp,incoef, cosexp ,  incoef);

	string rv = output;
	string rv = to_string(outcoef) + "*sin^" + to_string(sinexp) +
		"(" + to_string(incoef) + "x) * cos^" + to_string(cosexp) +
		"(" + to_string(incoef) + "x)";*/
}

list<TrigTerm>& TrigTerm::getList()
{
	return trig_list;
}

void TrigTerm::Integrate()
{
	if (sinexp % 2 == 1 || cosexp % 2 == 1)
		oddIntegrate();
	else if (cosexp % 2 == 0 && cosexp % 2 == 0)
		evenIntegrate();
	else
		cout << "Something went horribly wrong here.." << endl;
}

void TrigTerm::evenIntegrate()
{
	//For if it's 1.
	if (sinexp == 0 && cosexp == 0) {

		trig_list.push_back(TrigTerm(outcoef, 1, 0, 0, 1));
		return;
	}


	int newsinexp = sinexp / 2;
	int newcosexp = cosexp / 2; //Both exponents are even so dividing by two will be fine.
	int numofnewterms = newsinexp + newcosexp + 1; // Because 1 is a term where the cos exp is 0. and it goes untill all the terms are gotten.

	//When integrating sin^6cos^8, the sins are changed to ( (1-cos2x)/2 ) and the cosines are changed to ( (1+cos2x)/2 ) so you can take the 2's out 
	//and divide the outcoef by 2 ^(sinexp + cosexp) because that is the number of two's you take out.
	outcoef /= pow(2, newsinexp + newcosexp);

	//You then have (1-cos2x)^((1/2)*sinexp) which is (newsinexp) and (1+cos2x)^((1/2)*cosexp) which is newcosexp 

	//The outside coefficient 
	for (int i = 0; i < numofnewterms; i++) {
		int newoutcoef = 0;
		for (int j = 0; j <= i; j++) {
			
			//
			newoutcoef += pow((-1), j) * nCr(newsinexp, j) * nCr(newcosexp, i - j); // The terms
		}
		TrigTerm Jimmy(newoutcoef * outcoef, 2 * incoef, 0 , i);
		//newsinexp should be 0


		Jimmy.Integrate();
	}

}

void TrigTerm::oddIntegrate()
{

	bool sin_is_odd = true;

	if (sinexp % 2 == 1)
		sin_is_odd = true;
	else if (cosexp % 2 == 1)
		sin_is_odd = false;
	else
		cout << "There were issues... oddIntegrate called w/o odd exponents.\n";


	//Dividing an odd number by 2 rounds down to an integer.
	//allocate the array
	// int** arr = new int*[row]; Syntax stolen from http://stackoverflow.com/questions/9219712/c-array-expresssion-must-have-a-constant-value
	//TrigTerm *myArray = new TrigTerm[];

	if (sin_is_odd)
	{
		int originalcosexp = cosexp;
		int originalsinexp = sinexp;
		int numberofnewterms = (sinexp + 1) / 2;


		//for (int i = 0, j = 1; i < 2; i++, j *= -1)

		for (int i = 0, j = 1; i < numberofnewterms ; i++, j *=-1)
		{
			int newcosexp = originalcosexp + 2 * i + 1; //i*2 because turned sines into cosines 2 at a time. 
			
			trig_list.push_back(TrigTerm(
				(-1) / incoef * j * outcoef / (newcosexp) *  nCr(numberofnewterms - 1, i) , //-1/ inside coeficcient because u = cos(nx) so du = -sin nx * n dx so du*-1/n = sin nx dx
				incoef,
				0 * sinexp,
				newcosexp));
		}

		//Create new cos terms here where the new terms are (1-cos^2(x))
		//multiply all these starting with the (1-cos^2(x)) terms first
		//maybe because there is some cool trick to foiling a certain number 
		//of terms that can make this easy. 
		//Going to need expression with multiple trig functions. 
	}

	if (!sin_is_odd)//If cos is odd
	{
		int originalcosexp = cosexp;
		int originalsinexp = sinexp;
		int numberofnewterms = (cosexp + 1) / 2;


		//for (int i = 0, j = 1; i < 2; i++, j *= -1)

		for (int i = 0, j = 1; i < numberofnewterms; i++, j *= -1)
		{
			int newsinexp = originalsinexp + 2 * i + 1; //i*2 because turned sines into cosines 2 at a time. 

			trig_list.push_back(TrigTerm(
				(1) / incoef * j * outcoef / (newsinexp)*  nCr(numberofnewterms - 1, i), //-1/ inside coeficcient because u = cos(nx) so du = -sin nx * n dx so du*-1/n = sin nx dx
				incoef,
				newsinexp,
				0 * cosexp));
		}

	}

	//trig_list.push_back(TrigTerm(outcoef, incoef, sinexp, cosexp));

}

void TrigTerm::combineLikeTerms()
{
/*	for (int i = 0; i < trig_list.size(); i++)
	{
		Trig_Term = trig_list(i)
	}
	list<TrigTerm>::iterator iter, iterinner;

	for (iter = trig_list.begin(); iter != trig_list.end(); iter++) {
		
		list<TrigTerm>::iterator iternext = iter; 
		iternext++;

		for (iterinner = iternext; iter != trig_list.end(); ){
			
			if (
				iter->incoef == iterinner->incoef &&
				iter->sinexp == iterinner->sinexp &&
				iter->cosexp == iterinner->cosexp)
			{
				iter->incoef += iterinner->incoef;
				//i= items.erase(i);
				iterinner = trig_list.erase(iterinner);
			}
			else
				iterinner++;
		}
	}*/
}
