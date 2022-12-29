#pragma once
#include <string>
using namespace std;

struct Student {
	string name;
	string student_id;
	string ic;
	string year;
	string program;
	bool vote = false;
	string voter = "0";
	int votes = 0;
};

struct Settings {
	int candicate_count;
	int user_count;

};

struct Administrator
{
	string name;
	string username;
	string password;
};