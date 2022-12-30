#pragma once
#include "Student.h"

Settings getsettings();
Student* getcandidate(Settings settings);
Student* getstudent(Settings settings);
bool putData(Settings settings);
int registerUser(Student student);
void registeringStudent();
void displayStudents();
bool sorting(Student i, Student j);
void displayResult();
void displayStatistics();
int displayAdminlevel();