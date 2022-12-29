//Register student
#include <iostream>
#include <string>
#include <fstream>
#include "adminfunction.h"
#include "Student.h"
#include <iomanip>
#include <algorithm>
using namespace std;

Settings getsettings() {
    fstream inData;
    Settings settings{};
    inData.open("settings.txt");
    if (inData) {
        string line;
        int i = 0;
        string data[2];
        while (getline(inData, line)) {
            char delimiter = ':';

            size_t pos = line.find(delimiter);
            line.erase(0, pos + 1);
            data[i] = line;
            i++;
        }
        settings.candidate_count = stoi(data[0]);
        settings.user_count = stoi(data[1]);
    }
    inData.close();
    return settings;

}

Student* getcandidate(Settings settings) {
    fstream inData;
    Student* candidate = new Student[5];
    inData.open("candidate.txt");
    if (inData) {
        string line;
        int i = 0;
        while (getline(inData, line)) {
            if (i >= settings.user_count) break;
            string data[8];
            char delimiter = '|';

            int j = 0;
            size_t pos;
            while ((pos = line.find(delimiter)) != string::npos) {
                string token = line.substr(0, pos);
                data[j] = token;
                line.erase(0, pos + 1);
                j++;
            }
            candidate[i].name = data[0];
            candidate[i].student_id = data[1];
            candidate[i].ic = data[2];
            candidate[i].year = data[3];
            candidate[i].program = data[4];
            candidate[i].vote = (data[5] == "0") ? false : true;
            candidate[i].voter = data[6];
            candidate[i].votes = stoi(data[7]);
            i++;
        }
    }
    inData.close();
    return candidate;
}

Student* getstudent(Settings settings) {
    fstream inData;
    Student* user = new Student[200];
    inData.open("students.txt");
    if (inData) {
        string line;
        int i = 0;
        while (getline(inData, line)) {
            string data[8];
            char delimiter = '|';

            int j = 0;
            size_t pos;
            while ((pos = line.find(delimiter)) != string::npos) {
                string token = line.substr(0, pos);
                data[j] = token;
                line.erase(0, pos + 1);
                j++;
            }
            user[i].name = data[0];
            user[i].student_id = data[1];
            user[i].ic = data[2];
            user[i].year = data[3];
            user[i].program = data[4];
            user[i].vote = (data[5] == "0") ? false : true;
            user[i].voter = data[6];
            user[i].votes = stoi(data[7]);
            i++;
        }
    }
    inData.close();
    return user;
}

//const int MAX_STUDENTS = 100;  // Maximum number of students that can be registered
bool putData(Settings settings) {
    fstream inData;
    inData.open("settings.txt");
    string text = "Candidate Count:" + to_string(settings.candidate_count) + "\nRegistered User Count:" + to_string(settings.user_count);
    inData << text << endl;
    return true;
}

int registerUser(Student student) {
    //case 1 =success, case 2 = user already in database
    fstream inData;
    Settings settings = getsettings();
    Student* user = getstudent(settings);

    

    for (int k = 0; k < 200; k++) {
        if (user[k].ic == student.ic || user[k].student_id == student.student_id) {
            return 2;
        }
    }
    char delimiter = '|';
    string usertext = student.name + delimiter + student.student_id + delimiter + student.ic + delimiter + student.year + delimiter + student.program + delimiter + (student.vote == true?"1":"0") + delimiter + student.voter + delimiter + to_string(student.votes) + delimiter;
    inData.open("students.txt", ios::app);
    inData << usertext << endl;
    inData.close();

    putData(settings);
    return 1;
}

// Function to register a new student
void registeringStudent() {
    Student student;
    string name;
    string ic;
    string student_id;
    string program;
    string year;
    string error_text;
    Settings settings = getsettings();
    bool registeruser = true;

    
    do {
        system("cls");
        cout << "Register User\n";

        if (settings.user_count >= 200) {
            cout << "Error: Maximum number of students already registered."<<endl;
            registeruser = false;
            break;
        }

        cin.ignore();
        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter student ID: ";
        getline(cin, student_id); 
        
        cout << "Enter MyKad Number: ";
        getline(cin, ic);

        cout << "Enter Year: ";
        getline(cin, year); 
        
        cout << "Enter Program: ";
        getline(cin, program);

        for (int i = 0; i < name.length(); i++) {
            name[i] = toupper(name[i]);
        }
        for (int i = 0; i < student_id.length(); i++) {
            student_id[i] = toupper(student_id[i]);
        }
        for (int i = 0; i < program.length(); i++) {
            program[i] = toupper(program[i]);
        }
        for (int i = 0; i < year.length(); i++) {
            year[i] = toupper(year[i]);
        }

        student.name = name;
        student.ic = ic;
        student.student_id = student_id;
        student.program = program;
        student.year = year;

        int result = registerUser(student);
        switch (result) {
        case 1:
            settings.user_count++;
            cout << "Student successfully registered!" << endl;
            cout << "Current have total " << settings.user_count << " student(s) registered! Maximum 200 students can be registered!" << endl;
            break;
        case 2:
            cout << "Student already in database!" << endl;
            break;
        default:
            cout << "Unknow error occur. Unfortunately you are admin, so please find another admin to help you!" << endl;
            break;
        }


        char reguser;
        cout << "Continue to register user?(Y/N) ";
        cin >> reguser;
        if (toupper(reguser) == 'N') {
            registeruser = false;
        }

    } while (registeruser);
}

// Function to display a list of all registered students
void displayStudents() {
    fstream inData;
    Settings settings = getsettings();
    Student* user = getstudent(settings);

    cout << "Registered students:(Only Display First 20 Character Of Student's Name)" << endl;
    for (int i = 0; i < settings.user_count; i++) {
        cout << i + 1 << ".\t" << setw(20) << left << user[i].name.substr(0, 20) << "(" << user[i].student_id << ")" << " - " << user[i].ic << " | " << user[i].year << " " << user[i].program << " | Vote = " << (user[i].vote ? "TRUE" : "FALSE") << " | Vote Count : " << user[i].voter << endl;
    }
}

bool sorting(Student i, Student j) { 
    if (i.votes > j.votes) {
        return 1;
    }
    else {
        return 0;
    }
}

//Show voting and winner
void displayResult() {
    fstream inData;
    Settings settings = getsettings();
    Student * users = getcandidate(settings);

    sort(users, users + settings.candidate_count, sorting);
    
    system("cls");
    cout << "Election Results:" << endl;

    for (int i = 0; i < settings.candidate_count; i++) {
        cout << i << " - " << users[i].name << " with total " << users[i].votes << " votes." << endl;
    }

    if (users[0].votes > users[1].votes) {
        cout << "The Winner Is >" << users[0].name << "< with total " << users[0].votes << " vote(s)" << endl << "Congratulations!" << endl;
    }
    else if (users[0].votes == users[1].votes) {
        cout << "The result is tie!" << endl;
        cout << "Another voting session will be held again by another time." << endl;
        cout << "The time will determine by administrators." << endl;
    }
}

void displayStatistics() {
    fstream inData;
    Settings settings = getsettings();
    Student* candidate = getcandidate(settings);
    Student* user = getstudent(settings);

    int female = 0, male=0, total[5] = { 0,0,0,0,0 }, femalevote[5] = { 0,0,0,0,0 }, malevote[5] = { 0,0,0,0,0 },tfemalevote,tmalevote,tvote,novote;
    double votepercentage;

    for (int i = 0; i < settings.user_count; i++) {
        string ic = user[i].ic.substr(10, 11);
        int gender = stoi(user[i].ic.substr(10, 11)) % 2;
        for (int j = 0; j < settings.candidate_count; j++) {
            if (user[i].voter == candidate[j].ic) {
                total[j]++;
                if (gender == 0) {
                    femalevote[j]++;
                }
                else {
                    malevote[j]++;
                }
            }
        }
        if (gender == 0) {
            female++;
        }
        else {
            male++;
        }
    }

    tvote = total[0] + total[1] + total[2] + total[3] + total[4];
    tfemalevote = femalevote[0] + femalevote[1] + femalevote[2] + femalevote[3] + femalevote[4];
    tmalevote = malevote[0] + malevote[1] + malevote[2] + malevote[3] + malevote[4];
    novote = settings.user_count - tvote;
    votepercentage = (double)tvote / settings.user_count;

    system("cls");
    cout << "Total Number of Voters\t\t\t:" << tvote << endl;
    cout << "Total Number of Voters did not vote\t:" << novote << endl;
    cout << "Percentage of students who votes\t:" << setprecision(2) << fixed << votepercentage << "%" << endl << endl;
    
    cout << "Total votes by each candidate: (Only Display First 20 Character of Candidate's Name)" << endl;
    for (int i = 0; i < settings.candidate_count; i++) {
        cout << setw(20) << left << candidate[i].name.substr(0, 20) << " : " << total[i] << endl;
    }

    cout << setw(20) << left << "Total Female Voters" << " : "  << tfemalevote << endl;
    cout << setw(20) << left << "Total Male Voters" << " : "  << tmalevote << endl;


}

int displayAdminlevel() {
    int choice;
    do {
        system("cls");
        cout << "Welcome to Administrator Level" << endl;
        cout << "1. Register a new student" << endl;
        cout << "2. Display all registered students" << endl;
        cout << "3. Display result" << endl;
        cout << "4. Statistics" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 1) {
            registeringStudent();
        }
        else if (choice == 2) {
            displayStudents();
        }
        else if (choice == 3) {
            displayResult();
        }
        else if (choice == 4) {
            displayStatistics();
        }else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (!(choice >= 1 && choice <= 5));
    return 0;
}