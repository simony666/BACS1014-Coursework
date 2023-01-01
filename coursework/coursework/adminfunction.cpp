//Register student
#include <iostream>
#include <string>
#include <fstream>
#include "adminfunction.h"
#include "Student.h"
#include <iomanip>
#include <algorithm>
#include "function.h"
using namespace std;

Settings getsettings() {
    fstream inData;
    Settings settings{};
    inData.open("settings.txt");
    if (inData) {
        string line;
        int i = 0;
        string data[5];
        while (getline(inData, line)) {
            char delimiter = ':';

            size_t pos = line.find(delimiter);
            line.erase(0, pos + 1);
            data[i] = line;
            i++;
        }
        settings.max_candidate = stoi(data[0]);
        settings.candidate_count = stoi(data[1]);
        settings.user_count = stoi(data[2]);
        settings.nominate = (data[3]=="0")?false:true;
        settings.vote = (data[4]=="0")?false:true;
    }
    inData.close();
    return settings;

}

Student* getcandidate() {
    Settings settings = getsettings();
    fstream inData;
    Student* candidate = new Student[settings.candidate_count];
    inData.open("candidate.txt");
    if (inData) {
        string line;
        int i = 0;
        while (getline(inData, line)) {
            if (i >= settings.user_count) break;
            string data[10];
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
            candidate[i].nominate = (data[8] == "0") ? false : true;
            candidate[i].nominater = stoi(data[9]);
            i++;
        }
    }
    inData.close();
    return candidate;
}

Student* getstudent() {
    Settings settings = getsettings();
    fstream inData;
    Student* user = new Student[200];
    inData.open("students.txt");
    if (inData) {
        string line;
        int i = 0;
        while (getline(inData, line)) {
            string data[10];
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
            user[i].nominate = (data[8] == "0") ? false : true;
            user[i].nominater = stoi(data[9]);
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
    string text = "Max candidate:" + to_string(settings.max_candidate) 
        + "\nCandidate Count:" + to_string(settings.candidate_count)
        + "\nRegistered User Count:" + to_string(settings.user_count)
        + "\nNominate:" + (settings.nominate == true ? "1" : "0")
        + "\nVote:" + (settings.vote == true ? "1" : "0");
    inData << text << endl;
    return true;
}

int adminvalidate(string ic, string student_id) {
    // return 1 = all correct, 2 = IC not correct, 3 = Student Id not correct

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

    return 1;
}

int registerUser(Student student) {
    //case 1 =success, case 2 = user already in database
    fstream inData;
    Settings settings = getsettings();
    Student* user = getstudent();

    int result = adminvalidate(student.ic, student.student_id);
    // return 1 = all correct, 2 = IC not correct, 3 = Student Id not correct
    switch (result) {
    case 1:
        break;
    case 2:
        return 2;
    case 3:
        return 3;
    }
    

    for (int i = 0; i < 200; i++) {
        if (user[i].ic == student.ic || user[i].student_id == student.student_id) {
            return 4;
        }
    }
    char delimiter = '|';
    string usertext = student.name + delimiter + student.student_id + delimiter + student.ic + delimiter + student.year + delimiter + student.program + delimiter + (student.vote == true ? "1" : "0") + delimiter + student.voter + delimiter + to_string(student.votes) + delimiter + (student.nominate == true ? "1" : "0") + delimiter + to_string(student.nominater) + delimiter;
    inData.open("students.txt", ios::app);
    inData << usertext << endl;
    inData.close();

    settings.user_count = settings.user_count + 1;
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
        
        cout << "Enter IC Number: ";
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
        //TODO : valid user input

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
        case 3:
            cout << "Student's IC is Incorrect!" << endl;
            break;
        case 4:
            cout << "Student's Student ID is Incorrect!" << endl;
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
    Student* user = getstudent();

    cout << "Registered students:(Only Display First 20 Character Of Student's Name)" << endl;
    for (int i = 0; i < settings.user_count; i++) {
        cout << i + 1 << ".\t" 
            << setw(20) << left << user[i].name.substr(0, 20) << "(" << user[i].student_id << ")" 
            << " - " << user[i].ic 
            << " | " << user[i].year << " " << user[i].program 
            << " | Vote = " << (user[i].vote ? "TRUE" : "FALSE") 
            << " | Vote Count : " << user[i].voter 
            << endl;
    }
}

bool votesorting(Student i, Student j) { 
    if (i.votes > j.votes) {
        return 1;
    }
    else {
        return 0;
    }
}

//Show voting and winner
void displayResult(bool showdetail) {
    Settings settings = getsettings();
    Student * users = getcandidate();

    sort(users, users + settings.candidate_count, votesorting);
    
    system("cls");
    cout << "##################################" << endl;
    cout << "#        Election Results        #" << endl;
    cout << "##################################" << endl;

    if (showdetail) {
        cout << "Votes obtain by each candidate:" << endl;
        for (int i = 0; i < settings.max_candidate; i++) {
            cout << i+1 << " - " << users[i].name << " with total " << users[i].votes << " votes." << endl;
        }
    }

    if (users[0].votes > users[1].votes) {
        cout << "\nThe Winner Is >" << users[0].name << "< with total " << users[0].votes << " vote(s)" << endl << "Congratulations!" << endl;
    }
    else if (users[0].votes == users[1].votes) {
        cout << "\nThe result is tie! Fisrt user will be choose!" << endl
            << "The Winner Is >" << users[0].name << "< with total " << users[0].votes << " vote(s)" << endl 
            << "Congratulations!" << endl;
    }
}

void displayStatistics() {
    Settings settings = getsettings();
    Student* candidate = getcandidate();
    Student* user = getstudent();

    int female = 0, male=0, total[6] = { 0 }, femalevote[6] = { 0 }, malevote[6] = { 0 },tfemalevote,tmalevote,tvote,novote;
    double votepercentage;

    for (int i = 0; i < settings.user_count; i++) {
        string ic = user[i].ic.substr(10, 11);
        int gender = stoi(user[i].ic.substr(10, 11)) % 2;
        if (user[i].vote) {
            if (user[i].voter == "0") {
                total[5]++;
                if (gender == 0) {
                    femalevote[5]++;
                }
                else {
                    malevote[5]++;
                }
            }
            else {
                for (int j = 0; j < settings.max_candidate; j++) {
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
            }
        }
        if (gender == 0) {
            female++;
        }
        else {
            male++;
        }
    }

    tvote = total[0] + total[1] + total[2] + total[3] + total[4] + total[5];
    tfemalevote = femalevote[0] + femalevote[1] + femalevote[2] + femalevote[3] + femalevote[4] + femalevote[5];
    tmalevote = malevote[0] + malevote[1] + malevote[2] + malevote[3] + malevote[4] + malevote[5];
    novote = settings.user_count - tvote;
    votepercentage = (double)tvote / settings.user_count;

    system("cls");
    cout << "Total Number of Voters\t\t\t:" << tvote << endl
        << "Total Number of Voters did not vote\t:" << novote << endl
        << "Total Number of Voters abstain\t\t:" << total[5] << endl
        << "Percentage of students who votes\t:" << setprecision(2) << fixed << votepercentage*100 << "%" << endl << endl;
    
    cout << "Total votes by each candidate: (Only Display First 20 Character of Candidate's Name)" << endl;
    for (int i = 0; i < settings.candidate_count; i++) {
        cout << setw(20) << left << candidate[i].name.substr(0, 20) << " : " << total[i] << endl;
    }
    cout << setw(20) << left << "Abstain" << " : " << total[5] << endl;

    cout << endl << setw(20) << left << "Total Female Voters" << " : "  << tfemalevote << endl
        << setw(20) << left << "Total Male Voters" << " : "  << tmalevote << endl;


}
void systemstate() {
    Settings settings = getsettings();
    char confirm;

    do {
        system("cls");
        cout << "################################" << endl
            << "#         System State         #" << endl
            << "################################" << endl;

        cout << "Current State:" << endl
            << "Nominating: " << (settings.nominate ? "Open" : "Close") << endl
            << "Voting: " << (settings.vote ? "Open" : "Close") << endl
            << endl;
        cout << "Do you want to switch Nominating State to <" << (settings.nominate ? "Close" : "Open") << "> ?" << endl
            << "Are you want to swith?(Y/N): ";
        cin >> confirm;
        if (toupper(confirm) == 'Y') {
            settings.nominate = settings.nominate ? false : true;
            putData(settings);
            cout << "State Change!" << endl;
        }
        else if (toupper(confirm) == 'N') {
            cout << "State Remain!" << endl;
        }
        else {
            continue;
        }
        cout << "\nDo you want to switch Voting State to <" << (settings.vote ? "Close" : "Open") << "> ?" << endl
            << "Are you want to swith?(Y/N): ";
        cin >> confirm;
        if (toupper(confirm) == 'Y') {
            settings.vote = settings.vote ? false : true;
            putData(settings);
            cout << "State Change!" << endl;
        }
        else if (toupper(confirm) == 'N') {
            cout << "State Remain!" << endl;
        }
    } while (!(toupper(confirm) == 'N'|| toupper(confirm) == 'Y'));
    cout << "\nCurrent Satate:" << endl
        << "Nominating: " << (settings.nominate ? "Open" : "Close") << endl
        << "Voting: " << (settings.vote ? "Open" : "Close") << endl;
}

void resetdata() {
    Settings settings = getsettings();
    char confirm, selection,doubleconfirm;

    system("cls");
    cout << "##################################" << endl
        << "#           Reset Data           #" << endl
        << "##################################" << endl
        << "Alert! Please make sure are you really want to do so before continue!" << endl
        << "This will erase all data can cannot be redone!" << endl
        << "Are you sure to continue?(Y/N)" << endl;

    cin >> confirm;

    if (toupper(confirm) != 'Y') {
        return;
    }
    system("cls");
    cout << "##################################" << endl
        << "#           Reset Data           #" << endl
        << "##################################" << endl
        << "Please select one from below:" << endl
        << "1. Reset All Data (This will DELETE all data include all registered Student!)" << endl
        << "2. Reset Data (This will remove all candidate data and reset student's data)" << endl
        << "3. Reset Vote (This only reset each student's data without removing candidate)" << endl
        << "4. Cancel" << endl
        << "Your selection: ";
    cin >> selection;

    switch (selection)
    {
    case '1':
        system("cls");
        cout << "##################################" << endl
            << "#           Reset Data           #" << endl
            << "##################################" << endl
            << "Are you sure to Reset All Data? This action cannot be undone!" << endl
            << "Below data will be change one confirmed:" << endl
            << "All Student Data Deleted" << endl
            << "All Candidate Data Deleted" << endl
            << "\nAre you sure want to continue?(Y/N)" << endl;
        cin >> doubleconfirm;

        if (toupper(doubleconfirm) == 'Y') {
            fstream inData;
            inData.open("candidate.txt", ios::out);
            inData << "";
            inData.close();
            inData.open("student.txt", ios::out);
            inData << "";
            inData.close();
            settings.candidate_count = 0;
            settings.user_count = 0;
            settings.nominate = true;
            settings.vote = false;
            putData(settings);
            cout << "Successfully Reset All Data!" << endl;
        }
        else {
            cout << "Action Cancelled" << endl;
            return;
        }
        //reset all data
        break;
    case '2':
        system("cls");
        cout << "##################################" << endl
            << "#           Reset Data           #" << endl
            << "##################################" << endl
            << "Are you sure to Reset Data? This action cannot be undone!" << endl
            << "Below data will be change one confirmed:" << endl
            << "All Candidate Data Deleted" << endl
            << "All Student Data Reset to Default Condition" << endl
            << "\nAre you sure want to continue?(Y/N)" << endl;
        cin >> doubleconfirm;

        if (toupper(doubleconfirm) == 'Y') {
            Student* user = getstudent();
            fstream inData;
            char delimiter = '|';
            
            //Delete Candidate Data
            inData.open("candidate.txt", ios::out);
            inData << "";
            inData.close();
            
            //Reset Student Data
            inData.open("students.txt", ios::out);
            inData << "";
            inData.close();
            inData.open("students.txt", ios::app);
            for (int i = 0; i < settings.user_count; i++) {
                string usertext;
                usertext = user[i].name + delimiter + user[i].student_id + delimiter + user[i].ic + delimiter + user[i].year + delimiter + user[i].program + delimiter + "0" + delimiter + "0" + delimiter + "0" + delimiter + "0" + delimiter + "0" + delimiter;
                inData << usertext << endl;
            }
            inData.close();

            settings.candidate_count = 0;
            putData(settings);
            cout << "Successfully Reset Data!" << endl;
        }
        else {
            cout << "Action Cancelled" << endl;
            return;
        }
        break;
    case '3':
        system("cls");
        cout << "##################################" << endl
            << "#           Reset Data           #" << endl
            << "##################################" << endl
            << "Are you sure to Reset Vote? This action cannot be undone!" << endl
            << "Below data will be change one confirmed:" << endl
            << "All Candidate Data Reset to Default Condition" << endl
            << "All Student Data Reset to Default Condition" << endl
            << "\nAre you sure want to continue?(Y/N)" << endl;
        cin >> doubleconfirm;

        if (toupper(doubleconfirm) == 'Y') {
            Student* candidate = getcandidate();
            Student* user = getstudent();
            fstream inData;
            char delimiter = '|';

            //Reset Candidate Data
            inData.open("candidate.txt", ios::out);
            inData << "";
            inData.close();
            inData.open("candidate.txt", ios::app);
            for (int i = 0; i < settings.candidate_count; i++) {
                string usertext;
                usertext = candidate[i].name + delimiter + candidate[i].student_id + delimiter + candidate[i].ic + delimiter + candidate[i].year + delimiter + candidate[i].program + delimiter + "0" + delimiter + "0" + delimiter + "0" + delimiter + "0" + delimiter + to_string(candidate[i].nominater) + delimiter;
                inData << usertext << endl;
            }
            inData.close();

            //Reset Student Data
            inData.open("students.txt", ios::out);
            inData << "";
            inData.close();
            inData.open("students.txt", ios::app);
            for (int i = 0; i < settings.user_count; i++) {
                string usertext;
                usertext = user[i].name + delimiter + user[i].student_id + delimiter + user[i].ic + delimiter + user[i].year + delimiter + user[i].program + delimiter + "0" + delimiter + "0" + delimiter + "0" + delimiter + (user[i].nominate == true ? "1" : "0") + delimiter + "0" + delimiter;
                inData << usertext << endl;
            }
            inData.close();
            settings.nominate = true;
            settings.vote = true;
            putData(settings);
            cout << "Successfully Reset Vote!" << endl;
        }
        else {
            cout << "Action Cancelled" << endl;
            return;
        }
        break;
    default:
        break;
    }
}

void displayAdminlevel(Administrator admin) {
    int choice;
    do {
        system("cls");
        cout << "#################################" << endl
            << "#      Administrator Level      #" << endl
            << "#################################" << endl
            << "Welcome " << admin.name << " !" << endl
            << endl
            << "Please Select Your Action!" << endl
            << "1. Register a new student" << endl
            << "2. Display all registered students" << endl
            << "3. Display result" << endl
            << "4. Statistics" << endl
            << "5. System State" << endl
            << "6. Reset Data" << endl
            << "7. Quit" << endl
            << "Enter your choice: ";

        cin.ignore();
        cin >> choice;

        if (choice == 1) {
            registeringStudent();
        }
        else if (choice == 2) {
            displayStudents();
        }
        else if (choice == 3) {
            displayResult(true);
        }
        else if (choice == 4) {
            displayStatistics();
        }else if (choice == 5) {
            systemstate();
        }
        else if (choice == 6) {
            resetdata();
        }
        else if (choice == 7) {
            break;
        }

        else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (!(choice >= 1 && choice <= 7));
}