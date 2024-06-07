/*
	Truong, Bao

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "Course.h"

using namespace std; 

void Course::setCourseInfo(const string& prefix, int number, int units)
{
	coursePrefix = prefix;
	courseNumber = number;
	courseUnits = units;
}

string Course::getCoursePrefix() const
{
	return coursePrefix;
}

int Course::getCourseNumber() const
{
	return courseNumber;
}

int Course::getCourseUnits() const
{
	return courseUnits;
}

bool Course::operator<(const Course& other) const
{
	return coursePrefix < other.coursePrefix;
}

