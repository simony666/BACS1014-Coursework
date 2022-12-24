#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "function.h"
#include "userfunction.h"
#include "adminfunction.h"
#include "Student.h"
using namespace std;

//bool getData() {
Student getData() {
	string line;
	ifstream file;
	file.open("data.txt");
	Student user[200];

	int student_index = 0;

	if (file.is_open()) {
		while (getline(file, line)) {
			
			int pos = 0, index = 0;
			string line_data[6];

			while (pos != -1) {
				pos = (int)line.find("|");
				string cut = line.substr(0, pos);
				line_data[index] = cut;
				index++;
				line = line.substr(pos + 1);
			}

			user[student_index].name = line_data[0];
			user[student_index].student_id = line_data[1];
			user[student_index].ic = line_data[2];
			user[student_index].year = line_data[3];
			user[student_index].program = line_data[4];
			user[student_index].vote = stoi(line_data[5]) == 0 ?false:true;
			cout << user[student_index].name << ""
				<< user[student_index].student_id << ""
				<< user[student_index].ic << ""
				<< user[student_index].year << ""
				<< user[student_index].program << ""
				<< user[student_index].vote << ""
				<< endl;
		}
		file.close();
		return Student;
	}
	else {
		cout << "Unable to open file!" << endl;
	}
	return false;
}

bool putData(Student user) {
	string line;
	string delimiter = "|";
	ofstream otfile;
	otfile.open("data.txt", ios_base::app);
	if (otfile.is_open()) {
		string vote = user.vote?"1" : "0";
		line = user.name + delimiter + user.student_id + delimiter + user.ic + delimiter + user.year + delimiter + user.program + delimiter + vote + "\n";
		otfile << line;
		otfile.close();
		return true;
	}
	else {
		cout << "Unable to open file!" << endl;
	}
	return false;
}

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
	int valid;

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

			//validate acc
			int valid = adminvalidate(acc, "");
			if (valid == 2) {
				error_text = "No Such User in database";
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

			//validate pwd
			valid = adminvalidate(acc, pwd);
			if (valid == 1) {
				isLogin = true;
				return true;
			}else if (valid == 2){
				error_text = "No Such User in database";
			}else if (valid == 3) {
				error_text = "Your password is Wrong!";
			}else if (valid == 10) {
				error_text = "Your password is error!";
			}
			else {
				error_text = "Either Your Data is Wrong or Not Registered!";
			}

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

			//validate IC
			valid = uservalidate(IC, "");
			if (valid == 2) {
				error_text = "No Such User in database";
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
			valid = uservalidate(IC, std_id);
			if (valid == 1) {
				isLogin = true;
				return true;
			}
			else if (valid == 2) {
				error_text = "No Such Student in database";
			}
			else if (valid == 3) {
				error_text = "Your Student ID is Wrong!";
			}
			else if (valid == 10) {
				error_text = "Your Student id is Wrong!";
			}
			else {
				error_text = "Either Your Data is Wrong or Not Registered!";
			}
			
		}
	}

	return false;
}
