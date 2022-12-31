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
void displayCandidate();
bool sorting(Student i, Student j);
void displayResult();
void displayStatistics();
void displayAdminlevel();