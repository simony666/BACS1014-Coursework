#include <iostream>
#include <stdlib.h>
#include <string>
#include "function.h"
#include "userfunction.h"
using namespace std;

void displayUser() {
	cout << "##############################################" << endl
		<< "#                 User Level                 #" << endl
		<< "##############################################" << endl
		<< "** Switch to Admin Level, Please enter <-1> **" << endl << endl;
}

void displayAdmin() {	
	cout << "##############################################" << endl
		<< "#                Admin Level                 #" << endl
		<< "##############################################" << endl
		<< "** Switch to User Level, Please enter <-1> **" << endl << endl;
}

bool login() {
	bool isAdmin = false, isLogin = false;
	string IC = "", std_id="", acc="", pwd="", error_text = "";

	while (!isLogin) {
		system("cls");
		if (isAdmin) {
			//user is admin, display admin
			displayAdmin();

			//display error text is applicable
			if (error_text != "") {
				cout << error_text << endl;
				error_text = "";
			}

			//READ acc
			cout << "Please enter your Account: ";
			cin >> acc;

			//Check if user switch to user level
			if (acc == "-1") {
				//user switch to user level
				acc,pwd = "";
				cout << "Switch to User" << endl;
				isAdmin = false;
				continue;
			}

			//READ pwd
			cout << "Please enter your Password: ";
			cin >> pwd;

			//Check if user switch to user level
			if (pwd == "-1") {
				//user switch to user level
				acc,pwd = "";
				cout << "Switch to User" << endl;
				isAdmin = false;
				continue;
			}

			//TODO : validate for admin

		}
		else {
			//user is not admin, display user
			displayUser();

			//display error if applicable
			if (error_text != "") {
				cout << error_text << endl;
				error_text = "";
			}

			//READ IC
			cout << "Please enter your IC: ";
			cin >> IC;

			//Check if user switch to admin level
			if (IC == "-1") {
				IC, std_id = "";
				cout << "Switch to Admin" << endl;
				isAdmin = true;
				continue;
			}

			//READ std_id
			cout << "Please enter your Student ID: ";
			cin >> std_id;

			//Check if user switch to admin level
			if (std_id == "-1") {
				//user switch to user level
				IC, std_id = "";
				cout << "Switch to User" << endl;
				isAdmin = true;
				continue;
			}

			//validate data
			if (validate(IC, std_id)) {
				isLogin = true;
				return true;
			}
			else {
				error_text = "Either Your Data is Wrong or Not Registered!";
			}
			
		}
	}

	return false;
}