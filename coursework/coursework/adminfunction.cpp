Show voting and winner
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



Register student
#include <iostream>
#include <string>
using namespace std;

using namespace std;

const int MAX_STUDENTS = 100;  // Maximum number of students that can be registered

struct Student {
    string name;
    string mykad;
    string password;
    string studentid;
};

// Global array to store the registered students
Student students[MAX_STUDENTS];
int numStudents = 0;  // Number of students currently registered

// Function to register a new student
void registerStudent() {
    if (numStudents >= MAX_STUDENTS) {
        cout << "Error: Maximum number of students already registered." << endl;
        return;
    }

    cout << "Enter name: ";
    cin >> students[numStudents].name;

    cout << "Enter MyKad Number: ";
    cin >> students[numStudents].mykad;


    cout << "Enter student ID: ";
    cin >> students[numStudents].studentid;

    cout << "Enter password: ";
    cin >> students[numStudents].password;

    numStudents++;
    cout << "Student successfully registered." << endl;
}

// Function to display a list of all registered students
void displayStudents() {
    cout << "Registered students:" << endl;
    for (int i = 0; i < numStudents; i++) {
        cout << students[i].name << " (" << students[i].studentid << ")" << endl;
    }
}

int main() {
    while (true) {
        cout << "Welcome to Administrator Level" << endl;
        cout << "1. Register a new student" << endl;
        cout << "2. Display all registered students" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            registerStudent();
        }
        else if (choice == 2) {
            displayStudents();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}

