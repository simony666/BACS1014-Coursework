#pragma once
#include "Student.h"

Settings getsettings();
Student* getcandidate();
Student* getstudent();
bool putData(Settings settings);
int adminvalidate(string ic, string student_id);
int registerUser(Student student);
void registeringStudent();
void displayStudents();
bool votesorting(Student i, Student j);
void displayResult(bool showdetail);
void displayStatistics();
void systemstate();
void resetdata();
void displayAdminlevel(Administrator admin);