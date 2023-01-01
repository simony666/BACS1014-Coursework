/*
* BACS1014 Assignment
* Member : Yong Choy Mun, Wang Siew You, Eddie Chua Kok Seng
*/

#include <iostream>
#include "Student.h"
#include "function.h"
#include "adminfunction.h"

using namespace std;
void user() {
	bool isLogin = false;
	string ic, student_id;
	string error_text;
	Student user;

	do {
		system("cls");
		cout << "##################################" << endl;
		cout << "#           USER LEVEL           #" << endl;
		cout << "##################################" << endl;
		if (!error_text.empty()) cout << error_text << endl;

		cout << "Please enter IC: ";
		cin.ignore();
		cin >> ic;
		cout << "Please enter Student Id: ";
		cin.ignore();
		cin >> student_id;

		int result = validate(ic, student_id);
		switch (result) {
		case 1:
			isLogin = true;
			user = getuser(ic,student_id);
			break;
		case 2:
			error_text = "IC is incorrect! Please make sure only enter numberic ic without -";
			break;
		case 3:
			error_text = "Student ID is incorrect! Please make sure enter a correct format!";
			break;
		case 4:
			error_text = "No Data In Database! Please contact admin if you think this is an error!";
			break;
		default:
			error_text = "Unknown error occur! Please contact admin for futeru help.";
			break;
		}
	} while (!isLogin);

	cout << "Login SUCCESS!!!" << endl;

	if (opennominate()) {
		//open for nominate
		nominatesystem(user);

	}
	else if(openvote()) {
		//vote
		votesystem(user);

	}
	else {
		displayResult(false);
	}

}
void admin() {
	bool isAdminLogin = false;
	string username;
	string password;
	Administrator administrators[3];
	Administrator admin;
	string error_text;

	administrators[0].name = "Wang Siew You";
	administrators[0].username = "001";
	administrators[0].password = "0001";

	administrators[1].name = "Yong Choy Mun";
	administrators[1].username = "002";
	administrators[1].password = "0002";

	administrators[2].name = "Eddie Chua";
	administrators[2].username = "003";
	administrators[2].password = "0003";




	do {
		system("cls");
		cout << "#################################" << endl
			<< "#      Administrator Level      #" << endl
			<< "#################################" << endl
			<< "Please enter your username and password to continue.\n";
		if (!error_text.empty()) cout << error_text << endl;

		cout << "Username: ";
		cin.ignore();
		cin >> username;
		cout << "Password: ";
		cin.ignore();
		cin >> password;

		for (int i = 0; i < 3; i++) {
			if (username == administrators[i].username && password == administrators[i].password)
			{
				isAdminLogin = true;
				admin = administrators[i];
				break;
			}
		}
		error_text = "Incorrect username or password. Access denied.";
	} while (!isAdminLogin);
	
	displayAdminlevel(admin);
}

int main() {

	//continue loop until close the window
	do
	{
		int menu = main_menu();
		system("cls");
		if (menu == 1) {
			user();
		}
		else if (menu == 2) {
			admin();
		}
		cout << '\n' << "Press enter to continue.....";
		cin.ignore();
	} while (cin.get() == '\n');
	return 0;
}