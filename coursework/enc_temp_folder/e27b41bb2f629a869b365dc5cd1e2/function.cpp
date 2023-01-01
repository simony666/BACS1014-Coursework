#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
#include "adminfunction.h"
#include <algorithm>
#include <iomanip>
using namespace std;

int main_menu() {
	int menu;
	bool done = false;

	do {
		system("cls");
		cout << "###################################" << endl
			<< "#              Level              #" << endl
			<< "###################################" << endl
			<< "1 - User Level " << endl
			<< "2 - Admin Level " << endl
			<< endl << "Please select one of the menu: ";
		cin >> menu;
		cout << menu;

		switch (menu) {
		case 1:
			return 1;
			done = true;
			break;
		case 2:
			return 2;
			done = true;
			break;
		}
	} while (!done);
	
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
}

bool opennominate() {
	Settings settings = getsettings();

	if (settings.nominate) {
		return true;
	}

	return false;
}

bool openvote() {
	Settings settings = getsettings();

	if (settings.vote) {
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

void addCandidate(Student student) {
	//case 1 =success, case 2 = user already in database
	fstream inData;
	Settings settings = getsettings();
	Student* user = getcandidate();

	for (int i = 0; i < settings.candidate_count
		
		; i++) {
		if (user[i].ic == student.ic && user[i].student_id == student.student_id) {
			//user already being nominate!
			user[i].nominater++;
			updateCandidate(user[i]);
			return;
		}
	}

	//if (settings.candidate_count >= 5) {
	//	return;
	//}

	char delimiter = '|';
	string usertext = student.name + delimiter + student.student_id + delimiter + student.ic + delimiter + student.year + delimiter + student.program + delimiter + (student.vote == true ? "1" : "0") + delimiter + student.voter + delimiter + to_string(student.votes) + delimiter + (student.nominate == true ? "1" : "0") + delimiter + to_string(student.nominater) + delimiter;
	inData.open("candidate.txt", ios::app);
	inData << usertext << endl;
	inData.close();

	settings.candidate_count +=1;
	putData(settings);
}

void nominatesystem(Student student) {
	Settings settings = getsettings();
	string error_text, nic, nstudent_id;
	
	do {
		system("cls");
		cout << "#################################" << endl
			<< "#        Nominate System        #" << endl
			<< "#################################" << endl
			<< "Welcome " << student.name << " !" << endl;

		if (student.nominate) {
			cout << "\nYou Already Nominated! Please wait for vote start!" << endl;
			return;
		}

		if (!error_text.empty()) cout << error_text << endl;
		cout << "Please enter IC :";
		cin.ignore();
		cin >> nic;
		cout << "Please enter Student ID :";
		cin.ignore();
		cin >> nstudent_id;

		int result = adminvalidate(nic, nstudent_id);
		// return 1 = all correct, 2 = IC not correct, 3 = Student Id not correct
		Student candidate;
		switch (result) {
		case 1:
			candidate = getuser(nic, nstudent_id);
			candidate.nominater++;
			addCandidate(candidate);
			student.nominate = true;
			updateStudent(student);
			cout << "\nYou had successfully nominate " << candidate.name << " in this election." << endl
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

Student getvote(Student* student) {
	Settings settings = getsettings();
	Student* user = getcandidate();
	int vote;
	char confirm;

	do {
		system("cls");
		system("cls");
		cout << "#################################" << endl;
		cout << "#          Vote System          #" << endl;
		cout << "#################################" << endl;
		cout << "Welcome " << (* student).name << " !" << endl;

		if ((*student).vote) {
			cout << "You Already Voted! Please wait for result!" << endl;
			confirm = 'y';
			break;
		}

		cout << "\nCandidate List: (Only Display First 20 Character Of Student's Name)" << endl;
		for (int i = 0; i < settings.max_candidate; i++) {
			cout << i + 1 << "."
				<< setw(20) << left << user[i].name.substr(0, 20) << "(" << user[i].student_id << ")"
				<< " - " << user[i].ic
				<< " | " << user[i].year << " " << user[i].program
				<< " | Nominated By " << user[i].nominater << " student"
				<< endl;
		}

		cout << "6. Abstain" << endl
			<< "\nPlease vote one of the candidate above by enter the number infront of each candidate" << endl
			<< "You may also select 6 to abstain."<< endl
			<< "\nYou are vote: ";
		cin.ignore();
		cin >> vote;

		system("cls");
		cout << "######################################################################" << endl
			<< "#                               Alert!                               #" << endl
			<< "#   No amendment or changing of vote is allowed after vote casted!   #" << endl
			<< "######################################################################" << endl
			<< "You are select: " << endl;
		
		if (vote == 6) {
			cout << "Abstain" << endl;
		}else{
			cout << setw(20) << left << user[vote - 1].name.substr(0, 20) << "(" << user[vote - 1].student_id << ")"
				<< " - " << user[vote - 1].ic
				<< " | " << user[vote - 1].year << " " << user[vote - 1].program << endl;
		}
		cout << "Are you sure to vote this candidate?(Y/N):";
		cin.ignore();
		cin >> confirm;
		if (toupper(confirm) != 'Y') {
			continue;
		}
		(*student).vote = true;
		if (vote == 6) {
			Student emptyuser;
			emptyuser.ic = emptyuser.name = emptyuser.program = emptyuser.year = emptyuser.student_id = "6";
			return emptyuser;
		}
		(* student).voter = user[vote - 1].ic;
		user[vote - 1].votes++;
		return user[vote-1];

	} while (toupper(confirm) != 'Y');
	
	Student emptyuser;
	emptyuser.ic = emptyuser.name = emptyuser.program = emptyuser.year = emptyuser.student_id = "";
	return emptyuser;
}

void votesystem(Student student) {
	Settings settings = getsettings();
	string error_text;
	Student candidate;

	do {
		Student voteresult = getvote(&student);
		if (voteresult.name == "") {
			break;
		}else if (voteresult.name == "6") {
			updateStudent(student);
			cout << "Successfully Abstain!" << endl;
		}
		else {
			updateCandidate(voteresult);
			updateStudent(student);
			cout << "Successfully Vote " << voteresult.name << " !" << endl;
		}

	} while (!student.vote);
}