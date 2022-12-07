#include "userfunction.h"
#include <string>
using namespace std;


//valid if user is registered user
int uservalidate(string ic, string student_id) {
	//define Registered Student
	// {IC,Student ID}
	//TODO : Read data from file
	string reg_user[][2] = { {"011111","22WMR11111"},{"011112","22WMR11112"} };

	//TODO : Check std_id's is valid student id

	//for loop validate
	for (int i = 0; i < (sizeof(reg_user) / sizeof(reg_user[0])); i++) {
		//check if IC is inside array
		if (reg_user[i][0] == ic) {
			//ic is inside array

			// IC is inside registerred's Student
			//check if Student Id is same as ic
			if (student_id.empty()) {
				//student_id is not set, request input
				return 10;
			}else if (student_id == reg_user[i][1]) {
				//IC & Student IC is inside registered's id
				return 1;
			}
			else {
				//student_id is not in database
				return 3;
			}
		}
		else {
			//ic is not inside array
			return 2;
		}
	}
	return 0;
}

