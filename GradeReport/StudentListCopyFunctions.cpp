/*
	Truong, Bao

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"

#include <iostream>

using namespace std;

StudentList::StudentList(const StudentList& otherList)
{
	first = nullptr;
	last = nullptr;
	count = 0;

	Node* currentStudentOther = otherList.first;

	while (currentStudentOther != nullptr)
	{
		addStudent(currentStudentOther->getStudent());
		currentStudentOther = currentStudentOther->getNext();
	}
	count = otherList.count;

}

void StudentList::copyCallingObjIsEmpty(const StudentList& otherList)
{
	Node* currentStudentOther = otherList.first;

	while (currentStudentOther != nullptr)
	{
		addStudent(currentStudentOther->getStudent());
		currentStudentOther = currentStudentOther->getNext();
	}
}

void StudentList::copyObjectsSameLength(const StudentList& otherList)
{
	Node* currentStudent = first;
	Node* currentStudentOther = otherList.first;

	while (currentStudent != nullptr && currentStudentOther != nullptr)
	{
		currentStudent->setStudent(currentStudentOther->getStudent());
		currentStudent = currentStudent->getNext();
		currentStudentOther = currentStudentOther->getNext();
	}
}

void StudentList::copyCallingObjLonger(const StudentList& otherList)
{
	Node* currentStudent = first;
	Node* currentStudentOther = otherList.first;
	bool check = false;

	while (currentStudentOther != nullptr && !check)
	{
		if (currentStudentOther->getNext() == nullptr)
		{
			last = currentStudent;
			check = true;
		}
		currentStudent->setStudent(currentStudentOther->getStudent());
		currentStudent = currentStudent->getNext();
		currentStudentOther = currentStudentOther->getNext();
	}

	while (currentStudent != nullptr)
	{
		Node* trailCurrent = currentStudent;
		currentStudent = currentStudent->getNext();

		delete trailCurrent;
		trailCurrent = nullptr;

		count--;
	}

	last->setNext(nullptr);

}

void StudentList::copyCallingObjShorter(const StudentList& otherList)
{
	Node* currentStudent = first;
	Node* currentStudentOther = otherList.first;

	while (currentStudent != nullptr)
	{
		currentStudent->setStudent(currentStudentOther->getStudent());
		currentStudentOther = currentStudentOther->getNext();
		currentStudent = currentStudent->getNext();
		
	}

	while (currentStudentOther != nullptr)
	{
		addStudent(currentStudentOther->getStudent());
		currentStudentOther = currentStudentOther->getNext();
	}

}

StudentList& StudentList::operator= (const StudentList& otherList)
{
	if (&otherList == this)
	{
		cerr << "Attempted assignment to itself.\n";
	}
	else if (otherList.count == 0)
	{
		clearStudentList();
	}
	else if (count == 0)
	{
		copyCallingObjIsEmpty(otherList);
	}
	else if (count > otherList.count)
	{
		copyCallingObjLonger(otherList);
	}
	else if (count == otherList.count)
	{
		copyObjectsSameLength(otherList);
	}
	else
	{
		copyCallingObjShorter(otherList);
	}
	return *this;
}


