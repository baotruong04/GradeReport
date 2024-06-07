/*
	Truong, Bao

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "Student.h"

#include <iostream>
#include <iomanip>

using namespace std;

void Student::setStudent(const Student& otherStudent)
{
	studentID = otherStudent.studentID;
	firstName = otherStudent.firstName;
	lastName = otherStudent.lastName;
	numberOfCourses = otherStudent.numberOfCourses;
	tuitionWasPaid = otherStudent.tuitionWasPaid;
	coursesCompleted = otherStudent.coursesCompleted;
}

void Student::setStudentInfo(int id, const string& fname, const string& lname,
	bool paid, const multimap<Course, char>& cCompleted)
{
	studentID = id;
	firstName = fname;
	lastName = lname;
	numberOfCourses = static_cast<int>(cCompleted.size());
	tuitionWasPaid = paid;
	coursesCompleted = cCompleted;
}

int Student::getID() const
{
	return studentID;
}

string Student::getFirstName() const
{
	return firstName;
}

string Student::getLastName() const
{
	return lastName;
}

void Student::getName(string& fname, string& lname) const
{
	fname = firstName;
	lname = lastName;
}

int Student::getNumberOfCourses() const
{
	return numberOfCourses;
}

int Student::getUnitsCompleted() const
{
	int totalUnits = 0;

	for (const auto& pair : coursesCompleted)
	{
		totalUnits += pair.first.getCourseUnits();
	}

	return totalUnits;
}

multimap<Course, char> Student::getCoursesCompleted() const
{
	return coursesCompleted;
}

bool Student::isTuitionPaid() const
{
	return tuitionWasPaid;
}

bool Student::isCourseCompeleted(const string& prefix, 
								int courseNumber) const
{
	if (getNumberOfCourses() == 0)
	{
		return false;
	}
	else
	{
		for (const auto& pair : coursesCompleted)
		{
			if (pair.first.getCourseNumber() == courseNumber
				&& pair.first.getCoursePrefix() == prefix)
				return true;
		}
	}
	return false;
}

double Student::calculateGPA() const
{
		double gradePoints = 0.0;
		int totalUnits = 0;
		for (const auto& pair : coursesCompleted)
		{
			Course courseTaken  = pair.first;
			char grade = pair.second;

			int units = courseTaken.getCourseUnits();
			totalUnits += units;

			if (grade == 'A') gradePoints += 4.0 * units;
			else if (grade == 'B') gradePoints += 3.0 * units;
			else if (grade == 'C') gradePoints += 2.0 * units;
			else if (grade == 'D') gradePoints += 1.0 * units;
		}

		if (totalUnits > 0)
			return (gradePoints / totalUnits);
		else return 0.0;
}

double Student::billingAmount(double rate) const
{
	return static_cast<double>(numberOfCourses) * rate;
}

void Student::printStudent() const
{
	cout << studentID << " - " << lastName  << ", " << firstName << endl;
}

void Student::printStudentInfo(double rate) const
{
	cout << "Student Name: " << lastName << ", " << firstName << "\n"
		 << "Student ID: " << studentID << "\n"
		 << "Number of courses completed: " << numberOfCourses << "\n\n"
		 << left << setw(10) << "CourseNo" << setw(8) << "Units" << "Grade\n";

	for (const auto& pair : coursesCompleted)
	{
		Course courseTaken = pair.first;
		char grade = pair.second;

		cout << left << setw(10) << courseTaken.getCoursePrefix() + " "
			 + to_string(courseTaken.getCourseNumber()) << "  "
			 << setw(8) << courseTaken.getCourseUnits() << grade << "\n";

	}

	cout << "\nTotal number of credit hours: " << getUnitsCompleted() << "\n";

	if (!tuitionWasPaid)
	{
		cout << "*** Grades are being held for not paying the tuition. ***\n"
			 << "Amount Due: $" << fixed << setprecision(2) << billingAmount(rate) << "\n\n";
	}
	else
	{
		cout << "Current Term GPA: " << fixed << setprecision(2) << calculateGPA() << "\n\n";
			
	}
	cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << "\n";
}

void Student::addCourse(const Course& course, char grade)
{
		coursesCompleted.emplace(course, grade);
		numberOfCourses++;

}