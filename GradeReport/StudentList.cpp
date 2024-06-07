/*
	Truong, Bao

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"
 
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void StudentList::addStudent(const Student& otherStudent)
{
	if (first == nullptr)
	{
		first = new Node(otherStudent, nullptr);
		last = first;
	}
	else
	{
		last->setNext(new Node(otherStudent, nullptr));
		last = last->getNext();
	}
	++count;
}

int StudentList::getNoOfStudents() const
{
	return count;
}

void StudentList::printStudentByID(int id, double rate) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr)
	{
		Student currentStudent = current->getStudent();
		if (currentStudent.getID() == id)
		{
			found = true;
			currentStudent.printStudentInfo(rate);
		}
		current = current->getNext();
	}

	if (!found)
		cerr << "No students with ID " << id << " found in the list.\n";
}

void StudentList::printStudentByName(const string& lname) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr)
	{
		Student currentStudent = current->getStudent();
		if (currentStudent.getLastName() == lname)
		{
			found = true;
			currentStudent.printStudent();
		}
		current = current->getNext();
	}
	if (!found)
		cerr << "No students with last name " << lname << " is on the list.\n";
}

void StudentList::printStudentsByCourse(const string& prefix, int number) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr)
	{
		Student currentStudent = current->getStudent();
		for (const auto& pair : currentStudent.getCoursesCompleted())
		{
			const Course& courseTaken = pair.first;
			if (courseTaken.getCoursePrefix() == prefix 
				&& courseTaken.getCourseNumber() == number)
			{
				found = true;
				currentStudent.printStudent();
			}
		}

		current = current->getNext();
	}
	if (!found)
		cerr << "No students enrolled in " << prefix << " " << number << endl;
}

void StudentList::printAllStudents(double rate) const
{
	Node* current = first;

	while (current!= nullptr)
	{
		Student currentStudent = current->getStudent();
		currentStudent.printStudentInfo(rate);
		current = current->getNext();
	}
}


void StudentList::printStudentsToFile(ofstream& out, double rate) const
{
	Node* current = first;

	while (current != nullptr)
	{
		Student currentStudent = current->getStudent();

		out << "Student Name: " << currentStudent.getLastName() << ", "
			<< currentStudent.getFirstName() << "\n"
			<< "Student ID: " << currentStudent.getID() << "\n"
			<< "Number of courses completed: "
			<< currentStudent.getNumberOfCourses() << "\n\n"
			<< left << setw(10) << "CourseNo" << setw(8) << "Units" << "Grade\n";

		for (const auto& pair : currentStudent.getCoursesCompleted())
		{
			const Course& courseTaken = pair.first;
			char grade = pair.second;

			out << left << setw(10) << courseTaken.getCoursePrefix() + " "
				+ to_string(courseTaken.getCourseNumber()) << "  "
				<< setw(8) << courseTaken.getCourseUnits() << grade << "\n";

		}

		out << "\nTotal number of credit hours: " 
			<< currentStudent.getUnitsCompleted() << "\n";

		if (!currentStudent.isTuitionPaid())
		{
			out << "*** Grades are being held for not paying the tuition. ***\n"
				<< "Amount Due: $" << fixed << setprecision(2)
				<< currentStudent.billingAmount(rate) << endl;
		}
		else
		{
			out << "Current Term GPA: " << fixed << setprecision(2)
				<< currentStudent.calculateGPA() << "\n\n";
		}

		out << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << "\n";
		current = current->getNext();
	}
}

void StudentList::printStudentsOnHold(double rate) const
{
	Node* current = first;
	bool isHold = false;

	while (current != nullptr)
	{
		Student currentStudent = current->getStudent();
		if (!currentStudent.isTuitionPaid())
		{
			isHold = true;
			currentStudent.printStudent();
			cout << setw(8) << "    Amount Due: $" 
				 << fixed << setprecision(2)
				 << currentStudent.billingAmount(rate) << "\n";
		}
		current = current->getNext();
	}
	if (!isHold)
	{
		cout << "There are no students on hold.\n";
	}
}

void StudentList::clearStudentList()
{
	Node* temp = first;
	while (first != nullptr)
	{
		first = first->getNext();
		delete temp;
		temp = first;
	}
	last = nullptr;
	count = 0;
}

StudentList::~StudentList()
{
	if (first != nullptr)
	{
		clearStudentList();
	}
}


Student* StudentList::findStudentByID(int studentID) const
{
	Node* currentStudent = first;
	while (currentStudent != nullptr) 
	{
		if (currentStudent->getStudent().getID() == studentID) 
		{
			return &(currentStudent->getStudentFromID());
		}
		currentStudent = currentStudent->getNext();
	}
	return nullptr; 
}

void StudentList::addCourseForStudent(int studentID, 
				const string& firstName, const string& lastName, 
				const Course& course, char grade, double rate) const 
{
	Student* student = findStudentByID(studentID);
	student->addCourse(course, grade);

	cout << "The course has been added successfully.\n";
	student->printStudentInfo(rate);

}
