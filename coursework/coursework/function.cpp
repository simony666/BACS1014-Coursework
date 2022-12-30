#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
#include "adminfunction.h"
#include <algorithm>
using namespace std;

int main_menu() {
	int menu;

	cout << "###################################" << endl
		<< "#              Level              #" << endl
		<< "###################################" << endl
		<< "1 - User Level " << endl
		<< "2 - Admin Level " << endl
		<< endl << "Please select one of the menu(default: 1): ";
	cin >> menu;

	switch (menu) {
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	default:
		return 1;
	}
	return 0;
}

Student getuser(string ic, string student_id) {
	Settings settings = getsettings();
	Student* student = getstudent();
	Student emptyuser;
	emptyuser.ic = emptyuser.name = emptyuser.program = emptyuser.year = emptyuser.student_id = "";
	//int count =0;
	student_id[2] = toupper(student_id[2]);
	student_id[3] = toupper(student_id[3]);
	student_id[4] = toupper(student_id[4]);

	for (int i = 0; i < settings.user_count; i++) {
		if (student[i].ic == ic && student[i].student_id == student_id) {
			return student[i];
		}
	}

	return emptyuser;
}

bool validdb(string ic, string student_id) {
	ifstream inData;
	Settings settings = getsettings();
	Student* user = getstudent();

	for (int i = 0; i < settings.user_count; i++) {
		if (user[i].ic == ic && user[i].student_id == student_id) {
			return true;
		}
	}

	return false;
}

int validate(string ic, string student_id) {
	// return 1 = all correct, 2 = IC not correct, 3 = Student Id not correct, 4 = Not in Databses

	if (ic.length() != 12) return 2;
	if (student_id.length() != 10) return 3;

	for (int i = 0; i < ic.length(); i++) {
		if (!isdigit(ic[i])) {
			return 2;
		}
	}
	for (int i = 0; i < student_id.length(); i++) {
		if (i == 2 || i == 3 || i == 4) {
			if (!isalpha(student_id[i])) {
				return 3;
			}
		}
		else {
			if (!isdigit(student_id[i])) {
				return 3;
			}
		}
	}
	student_id[2] = toupper(student_id[2]);
	student_id[3] = toupper(student_id[3]);
	student_id[4] = toupper(student_id[4]);
	if (validdb(ic,student_id)) {
		return 1;
	}
	else {
		return 4;
	}
	
	return 0;
};

bool opennominate() {
	string setting[3];
	ifstream inData;
	Settings settings = getsettings();

	if (settings.candidate_count < 5) {
		return true;
	}

	return false;
}

bool nominatesorting(Student i, Student j) {
	if (i.nominater > j.nominater) {
		return 1;
	}
	else {
		return 0;
	}
}

bool updateCandidate(Student student) {
	Settings settings = getsettings();
	Student* user = getcandidate();

	fstream inData;
	char delimiter = '|';
	inData.open("candidate.txt", ios::out);
	inData << "";
	inData.close();
	inData.open("candidate.txt", ios::app);
	sort(user, user + settings.candidate_count, nominatesorting);

	for (int i = 0; i < settings.candidate_count; i++) {
		string usertext;
		if (student.ic == user[i].ic) {
			usertext = student.name + delimiter + student.student_id + delimiter + student.ic + delimiter + student.year + delimiter + student.program + delimiter + (student.vote == true ? "1" : "0") + delimiter + student.voter + delimiter + to_string(student.votes) + delimiter + (student.nominate == true ? "1" : "0") + delimiter + to_string(student.nominater) + delimiter;
		}
		else {
			usertext = user[i].name + delimiter + user[i].student_id + delimiter + user[i].ic + delimiter + user[i].year + delimiter + user[i].program + delimiter + (user[i].vote == true ? "1" : "0") + delimiter + user[i].voter + delimiter + to_string(user[i].votes) + delimiter + (user[i].nominate == true ? "1" : "0") + delimiter + to_string(user[i].nominater) + delimiter;
		}
		inData << usertext << endl;
	}
	inData.close();

	return true;
}
bool updateStudent(Student student) {
	Settings settings = getsettings();
	Student* user = getstudent();

	fstream inData;
	char delimiter = '|';
	inData.open("students.txt", ios::out);
	inData << "";
	inData.close();
	inData.open("students.txt", ios::app);
	for (int i = 0; i < settings.user_count; i++) {
		string usertext;
		if (student.ic == user[i].ic) {
			usertext = student.name + delimiter + student.student_id + delimiter + student.ic + delimiter + student.year + delimiter + student.program + delimiter + (student.vote == true ? "1" : "0") + delimiter + student.voter + delimiter + to_string(student.votes) + delimiter + (student.nominate == true ? "1" : "0") + delimiter + to_string(student.nominater) + delimiter;
		}
		else {
			usertext = user[i].name + delimiter + user[i].student_id + delimiter + user[i].ic + delimiter + user[i].year + delimiter + user[i].program + delimiter + (user[i].vote == true ? "1" : "0") + delimiter + user[i].voter + delimiter + to_string(user[i].votes) + delimiter + (user[i].nominate == true ? "1" : "0") + delimiter + to_string(user[i].nominater) + delimiter;
		}
		inData << usertext << endl;
	}
	inData.close();

	return true;
}

int addCandidate(Student student) {
	//case 1 =success, case 2 = user already in database
	fstream inData;
	Settings settings = getsettings();
	Student* user = getcandidate();



	for (int i = 0; i < 200; i++) {
		if (user[i].ic == student.ic || user[i].student_id == student.student_id) {
			//user already being nominate!
			user[i].nominater++;
			updateCandidate(user[i]);
			return 1;
		}
	}
	char delimiter = '|';
	string usertext = student.name + delimiter + student.student_id + delimiter + student.ic + delimiter + student.year + delimiter + student.program + delimiter + (student.vote == true ? "1" : "0") + delimiter + student.voter + delimiter + to_string(student.votes) + delimiter + (student.nominate == true ? "1" : "0") + delimiter + to_string(student.nominater) + delimiter;
	inData.open("candidate.txt", ios::app);
	inData << usertext << endl;
	inData.close();

	settings.candidate_count = settings.candidate_count + 1;
	putData(settings);
	return 1;
}

void nominatesystem(Student student) {
	Settings settings = getsettings();
	string error_text, nic, nstudent_id;
	
	do {
		system("cls");
		cout << "nominate System" << endl;
		
		if (settings.candidate_count >= 5) {
			cout << "Some error occur! Please wait for vote start!" << endl;
			return;
		}
		if (student.nominate) {
			cout << "You Already Nominated! Please wait for vote start!" << endl;
			return;
		}

		if (!error_text.empty()) cout << error_text << endl;
		cout << "Please enter IC :";
		cin >> nic;
		cout << "Please enter Student ID :";
		cin >> nstudent_id;

		int result = adminvalidate(nic, nstudent_id);
		// return 1 = all correct, 2 = IC not correct, 3 = Student Id not correct
		Student candidate;
		switch (result) {
		case 1:
			candidate = getuser(nic, nstudent_id);
			addCandidate(candidate);
			student.nominate = true;
			updateStudent(student);
			cout << "You had successfully nominate " << candidate.name << " in this election." << endl
				<< "Please wait for voting period start to support your candidate!" << endl;
			break;
		case 2:
			error_text = "IC is incorrect! Please check before enter!";
			break;
		case 3:
			error_text = "Student ID is incorrect! Please check before enter!";
			break;
		}
	} while (!student.nominate);
}