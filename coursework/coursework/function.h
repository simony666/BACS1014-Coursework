#pragma once
#include "Student.h"

int main_menu();
Student getuser(string ic, string student_id);
bool validdb(string ic, string student_id);
int validate(string ic, string student_id);
bool opennominate();
bool openvote();
bool nominatesorting(Student i, Student j);
bool updateCandidate(Student student);
bool updateStudent(Student student);
void addCandidate(Student student);
void nominatesystem(Student student);
Student getvote(Student* student);
void votesystem(Student student);