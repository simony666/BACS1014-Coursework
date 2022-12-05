/*
* BACS1014 Assignment
* Member : Yong Choy Mun, Wang Siew You, Eddie Chua Kok Seng
*/

#include <iostream>
#include "userfunction.h"

using namespace std;

int main() {
	//Welcome Screen

	//Enter Detail ( ic,student id)
	//validation
	cout << validate("011111", "22WMR11111") << endl;
	cout << validate("011111", "22WMR11113") << endl;
	cout << validate("011113", "22WMR11113") << endl;
	return 0;
}