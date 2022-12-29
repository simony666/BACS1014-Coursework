//Register student
#include <iostream>
#include <string>
#include <fstream>
#include "adminfunction.h"
#include "Student.h"
#include <iomanip>
using namespace std;

//const int MAX_STUDENTS = 100;  // Maximum number of students that can be registered
bool putData(Settings settings) {
    fstream inData;
    inData.open("settings.txt");
    string text = "Candicate Count:" + to_string(settings.candicate_count) + "\nRegistered User Count:" + to_string(settings.user_count);
    inData << text << endl;
    return true;
}

int registerUser(Student student) {
    //case 1 =success, case 2 = user already in database
    fstream inData;
    Student user[200];
    Settings settings;

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
        settings.candicate_count = stoi(data[0]);
        settings.user_count = stoi(data[1])+1;
        putData(settings);
    }
    inData.close();
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
    Settings settings{};
    bool registeruser = true;

    //get data from setting file and store into settings structurt
    ifstream inData;
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
        settings.candicate_count = stoi(data[0]);
        settings.user_count = stoi(data[1]);
    }
    inData.close();
    
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
    Student user[200];
    Settings settings;

    //get data from setting file and store into settings structurt
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
        settings.candicate_count = stoi(data[0]);
        settings.user_count = stoi(data[1]);
    }
    inData.close();

    inData.open("students.txt");
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


    cout << "Registered students:(Only Display First 20 Character Of Student's Name)" << endl;
    for (int i = 0; i < settings.user_count; i++) {
        cout << i + 1 << ".\t" << setw(20) << left << user[i].name.substr(0, 20) << "(" << user[i].student_id << ")" << " - " << user[i].ic << " | " << user[i].year << " " << user[i].program << " | Vote = " << (user[i].vote ? "TRUE" : "FALSE") << " | Vote Count : " << user[i].voter << endl;
    }
}



//Show voting and winner
void displayResult() {
    cout << "Election Results:" << endl;
    
    
    
    /*cout << "Alice: " << votes.at("Alice") << " votes" << endl;
    cout << "Bob: " << votes.at("Bob") << " votes" << endl;
    cout << "Charlie: " << votes.at("Charlie") << " votes" << endl;


    if (votes.at("Alice") > votes.at("Bob") && votes.at("Alice") > votes.at("Charlie")) {
        cout << "Winner is Alice! Has won " << votes.at("Alice") << " votes." << endl;
    }

    else if (votes.at("Bob") > votes.at("Alice") && votes.at("Bob") > votes.at("Charlie")) {
        cout << "Winner is Bob! Has won " << votes.at("Bob") << " votes." << endl;
    }

    else if (votes.at("Charlie") > votes.at("Alice") && votes.at("Charlie") > votes.at("Bob")) {
        cout << "Winner is Charlie! Has won " << votes.at("Charlie") << " votes." << endl;
    }

    if (votes.at("Alice") == votes.at("Bob") && votes.at("Alice") == votes.at("Charlie")) {
        cout << "The vote was a tie." << endl;
        cout << "Another voting session will be again by another time." << endl;
        cout << "The time will determine by administrators." << endl;
    }

    else if (votes.at("Bob") == votes.at("Alice") && votes.at("Bob") == votes.at("Charlie")) {
        cout << "The vote was a tie." << endl;
        cout << "Another voting session will be again by another time." << endl;
        cout << "The time will determine by administrators." << endl;
    }

    else if (votes.at("Charlie") == votes.at("Alice") && votes.at("Charlie") == votes.at("Bob")) {
        cout << "The vote was a tie." << endl;
        cout << "Another voting session will be again by another time." << endl;
        cout << "The time will determine by administrators." << endl;
    }*/
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
            exit;
        }else if (choice == 5) {
            exit;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (!(choice >= 1 && choice <= 3));
    return 0;
}
/*

// statistics of voting result
#include <iostream>

using namespace std;

const int NUM_CANDIDATES = 3;  // Number of candidates

// Function prototype
void showVotingStats(int numVoters, int votes[][NUM_CANDIDATES]);

int main()
{
    // Test data for the function
    int numVoters = 10;
    int votes[][NUM_CANDIDATES] = {
        {1, 0, 0},  // Voter 1 votes for candidate 1
        {1, 0, 0},  // Voter 2 votes for candidate 1
        {0, 1, 0},  // Voter 3 votes for candidate 2
        {0, 0, 1},  // Voter 4 votes for candidate 3
        {0, 1, 0},  // Voter 5 votes for candidate 2
        {1, 0, 0},  // Voter 6 votes for candidate 1
        {0, 0, 1},  // Voter 7 votes for candidate 3
        {0, 0, 1},  // Voter 8 votes for candidate 3
        {0, 1, 0},  // Voter 9 votes for candidate 2
        {1, 0, 0}   // Voter 10 votes for candidate 1
    };

    showVotingStats(numVoters, votes);

    return 0;
}

// Function definition
void showVotingStats(int numVoters, int votes[][NUM_CANDIDATES])
{
    int totalVotes[NUM_CANDIDATES] = {0};  // Initialize vote totals to 0
    int numMaleVoters = 0;
    int numFemaleVoters = 0;

    // Calculate total votes for each candidate
    for (int i = 0; i < numVoters; i++)
    {
        for (int j = 0; j < NUM_CANDIDATES; j++)
        {
            totalVotes[j] += votes[i][j];
        }

        // Check the gender of the voter based on the IC number
        if (i % 2 == 0)  // Even numbered ICs are assumed to be male
        {
            numMaleVoters++;
        }
        else  // Odd numbered ICs are assumed to be female
        {
            numFemaleVoters++;
        }
    }

    // Calculate percentage of voters who voted
    float pctVoted = (float)numVoters / numVoters * 100;

    // Print the results
    cout << "Total number of voters: " << numVoters << endl;
    cout << "Total number who did not vote: " << numVoters - numVoters << endl;
    cout << "Percentage of students who voted: " << pctVoted << "%" << endl;
    cout << "Total votes for candidate 1: " << totalVotes[0] << endl;
    cout << "Total votes for candidate 2: " << totalVotes[1] << endl;
    cout << "Total votes for candidate 3: " << totalVotes[2] << endl;
    cout << "Number of male voters: " << numMaleVoters << endl;
    cout << "Number of female voters: " << numFemaleVoters << endl;
}

//Show voting and winner
#include <iostream>
#include <string>
#include <map>

using namespace std;

// Constants for the number of candidates and the number of votes
const int NUM_CANDIDATES = 3;   //Need change to total candidates!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const int NUM_VOTES = 9;      //Need change to total student register!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

// Function prototypes
void castVote(map<string, int>& votes);
void displayResults(const map<string, int>& votes);

int main() {
    // Map to store the votes for each candidate
    map<string, int> votes;

    // Initialize the votes for each candidate
    votes["Alice"] = 0;                              //Need change name!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    votes["Bob"] = 0;
    votes["Charlie"] = 0;

    // Cast the votes
    for (int i = 0; i < NUM_VOTES; i++) {
        castVote(votes);
    }

    // Display the results
    displayResults(votes);

    return 0;
}

void castVote(map<string, int>& votes) {
    cout << "Please select a candidate to vote for:" << endl;
    cout << "1. Alice" << endl;
    cout << "2. Bob" << endl;
    cout << "3. Charlie" << endl;

    int selection;
    cin >> selection;

    // Increment the vote count for the selected candidate
    switch (selection) {
    case 1:
        votes["Alice"]++;
        break;
    case 2:
        votes["Bob"]++;
        break;
    case 3:
        votes["Charlie"]++;
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
    }
}

void displayResults(const map<string, int>& votes) {
    cout << "Election Results:" << endl;
    cout << "Alice: " << votes.at("Alice") << " votes" << endl;
    cout << "Bob: " << votes.at("Bob") << " votes" << endl;
    cout << "Charlie: " << votes.at("Charlie") << " votes" << endl;


    if (votes.at("Alice") > votes.at("Bob") && votes.at("Alice") > votes.at("Charlie")) {
        cout << "Winner is Alice! Has won " << votes.at("Alice") << " votes." << endl;
    }

    else if (votes.at("Bob") > votes.at("Alice") && votes.at("Bob") > votes.at("Charlie")) {
        cout << "Winner is Bob! Has won " << votes.at("Bob") << " votes." << endl;
    }

    else if (votes.at("Charlie") > votes.at("Alice") && votes.at("Charlie") > votes.at("Bob")) {
        cout << "Winner is Charlie! Has won " << votes.at("Charlie") << " votes." << endl;
    }

    if (votes.at("Alice") == votes.at("Bob") && votes.at("Alice") == votes.at("Charlie")) {
        cout << "The vote was a tie." << endl;
        cout << "Another voting session will be again by another time." << endl;
        cout << "The time will determine by administrators." << endl;
    }

    else if (votes.at("Bob") == votes.at("Alice") && votes.at("Bob") == votes.at("Charlie")) {
        cout << "The vote was a tie." << endl;
        cout << "Another voting session will be again by another time." << endl;
        cout << "The time will determine by administrators." << endl;
    }

    else if (votes.at("Charlie") == votes.at("Alice") && votes.at("Charlie") == votes.at("Bob")) {
        cout << "The vote was a tie." << endl;
        cout << "Another voting session will be again by another time." << endl;
        cout << "The time will determine by administrators." << endl;
    }
}
*/