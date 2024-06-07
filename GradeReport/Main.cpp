/*
	Truong, Bao

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"
#include "InputHandler.h"
#include "OutputHandler.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const string FILE_NAME = "student_data.txt";

void displayMenu();
void processChoice(const StudentList&, double);
void addCourseOption(const StudentList&, double);


int main()
{
	StudentList aList;
	double tuitionRate = 0.0;
	readStudentData(FILE_NAME, aList, tuitionRate);

	while (true)
	{
		displayMenu();
		processChoice(aList, tuitionRate);
	}

	cout << endl;
	system("Pause");
	return 0;
}

void displayMenu()
{
	cout << "\n\n*** MAIN MENU ***\n\n"
		 << "Select one of the following:\n\n"
		 << "    1: Print all students\n"
		 << "    2: Print student information\n"
		 << "    3: Search student by last name\n"
		 << "    4: Print students by course\n"
		 << "    5: Print students on hold\n"
		 << "    6: Print students to file\n"
		 << "    7: Add a course for a student\n"
		 << "    8: To exit\n\n";
}

void processChoice(const StudentList& aList, double rate)
{
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	cout << endl;

	int numberInput = 0;
	string stringInput;

	switch (choice)
	{
	case 1:
		aList.printAllStudents(rate);
		break;

	case 2:
		cout << "Please enter student's ID: ";
		cin >> numberInput;
		cout << endl;
		aList.printStudentByID(numberInput, rate);
		cout << endl;
		break;

	case 3:
		cout << "Please enter student's last name: ";
		cin >> stringInput;
		cout << endl;
		aList.printStudentByName(stringInput);
		cout << endl;
		break;

	case 4:
		cout << "Please enter the course prefix: ";
		cin >> stringInput;
		cout << "Please enter the course number: ";
		cin >> numberInput;
		cout << endl;
		aList.printStudentsByCourse(stringInput, numberInput);
		cout << endl;
		break;

	case 5:
		aList.printStudentsOnHold(rate);
		cout << endl;
		break;

	case 6:
		printAllStudentsToFile(aList, rate);
		cout << endl;
		break;

	case 7:
		addCourseOption(aList, rate);
		break;

	case 8:
		cout << "Thank you for using the OCC Gradebook. Good-bye!\n\n";
		system("Pause");
		exit(0);
		break;

	default:
		cout << "Sorry. That is not a selection.\n\n";
		break;
	}
	system("Pause");
}

void addCourseOption(const StudentList& aList, double rate)
{
	int studentID = 0;
	cout << "Enter student ID: ";
	cin >> studentID;
	cout << endl;

	Student* student = aList.findStudentByID(studentID);

	if (student == nullptr)
	{
		cerr << "Student could not be found. Please try again.\n\n";
	}
	else
	{
		string firstName;
		cout << "Enter student's first name: ";
		cin >> firstName;

		if (firstName != student->getFirstName())
		{
			cerr << "First name could not be found. Please try again.\n\n";
		}
		else
		{
			string lastName;
			cout << "Enter student's last name: ";
			cin >> lastName;

			if (lastName != student->getLastName())
			{
				cerr << "Last name could not be found. Please try again.\n\n";
			}
			else
			{
				string coursePrefix;
				cout << "Enter course prefix: ";
				cin >> coursePrefix;

				int courseNumber = 0;
				cout << "Enter course number: ";
				cin >> courseNumber;

				int courseUnit = 0;
				cout << "Enter course units: ";
				cin >> courseUnit;

				char grade = 'A';
				cout << "Enter grade: ";
				cin >> grade;
				cout << endl;

				Course aCourse;
				aCourse.setCourseInfo(coursePrefix, courseNumber, courseUnit);
				aList.addCourseForStudent(studentID, firstName, lastName, 
											aCourse, grade, rate);
				cout << endl;
			}
		}

	}
}