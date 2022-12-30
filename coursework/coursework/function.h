#pragma once
#include "Student.h"

int main_menu();
int validate(string ic, string student_id);
Student getuser(string ic, string student_id);
bool validdb(string ic, string student_id);
bool opennominate();
void nominatesystem(Student student);