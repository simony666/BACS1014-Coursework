#include "userfunction.h"
#include <string>
using namespace std;


//valid if user is registered user
bool validate(string ic, string student_id) {
	//define Registered Student
	// {IC,Student ID}
	string reg_user[][2] = { {"011111","22WMR11111"},{"011112","22WMR11112"} };

	//for loop validate
	for (int i = 0; i < (sizeof(reg_user) / sizeof(reg_user[0])); i++) {
		//check if IC is inside array
		if (reg_user[i][0] == ic) {
			
			// IC is inside registerred's Student
			//check if Student Id is same as ic
			if (reg_user[i][1] == student_id) {
				//IC & Student IC is inside registered's id
				return true;
			}
		}
	}
	return false;
}