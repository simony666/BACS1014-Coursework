#include "adminfunction.h"
#include <string>
using namespace std;

int adminvalidate(string acc, string pwd) {

	string reg_user[][2] = { {"001","123"},{"002","1234"} };
	
	for (int i = 0; i < (sizeof(reg_user) / sizeof(reg_user[0])); i++) {
		//check if Acc is inside array
		if (reg_user[i][0] == acc) {
			// acc is inside Admin Array
			
			//check password
			if (pwd.empty()) {
				//Account is inside Array, request user's password
				return 10;
			}else if (pwd == reg_user[i][1]) {
				//acc and pwd is inside array
				return 1;
			}
			else {
				//pwd is wrong!
				return 3;
			}
		}
		else {
			//account is wrong
			return 2;
		}
	}
	return 0;
}