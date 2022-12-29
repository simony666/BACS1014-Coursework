//admin data create and welcome screen
#include<iostream>
#include<string>
using namespace std;

struct Administrator
{
    string name;
    string username;
    string password;
};

int main()
{
    string username;
    string password;
    Administrator administrators[3];

    administrators[0].name = "Wang Siew You";
    administrators[0].username = "001";
    administrators[0].password = "0001";

    administrators[1].name = "Yong Chuy Mun";
    administrators[1].username = "002";
    administrators[1].password = "0002";

    administrators[2].name = "Eddie Chua";
    administrators[2].username = "003";
    administrators[2].password = "0003";

    cout << "Welcome, administrator! Please enter your username and password to continue.\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == administrators[0].username && password == administrators[0].password)
    {
        cout << "Access granted!\n";
    }
    else if (username == administrators[1].username && password == administrators[1].password)
    {
        cout << "Access granted!\n";
    }
    else if (username == administrators[2].username && password == administrators[2].password)
    {
        cout << "Access granted!\n";
    }
    else
    {
        cout << "Incorrect username or password. Access denied.\n";
    }
    return 0;
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
