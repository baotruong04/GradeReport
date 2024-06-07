/*
	Truong, Bao

	Project: Grade Report
	CS A250
	Fall 2023
*/

#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "Course.h"
#include "Student.h"

class Node
{
public:
	Node() : student(), next(nullptr) {}
	Node(Student otherStudent, Node* newNext)
		: student(otherStudent), next(newNext) {}
	Node* getNext() const { return next; }
	Student getStudent() const { return student; }
	Student& getStudentFromID() { return student; } // ADDITIONAL SELECTION
	void setStudent(Student otherStudent) { student = otherStudent; }
	void setNext(Node* newNext) { next = newNext; }
	~Node() {}

private:
	Student student;
	Node* next; // Pointer that points to next node.
};


class StudentList
{
public:
	StudentList() : first(nullptr), last(nullptr), count(0) {}
	StudentList(const StudentList& otherList);
	
	void addStudent (const Student&);
	StudentList& operator= (const StudentList&);
	
	int getNoOfStudents() const;

	void printStudentByID(int, double) const;
	void printStudentByName(const std::string&) const;
	void printStudentsByCourse(const std::string&, int) const;
	void printAllStudents(double) const;

	void printStudentsToFile(std::ofstream&, double) const;
	void printStudentsOnHold(double) const;

	void clearStudentList();
	~StudentList();
	
	// ADDITIONAL SELECTION
	Student* findStudentByID(int) const;
	void addCourseForStudent(int, const std::string&,
		const std::string&, const Course&, char, double) const;


private:
	Node* first;
	Node* last;
	int count;

	void copyCallingObjIsEmpty(const StudentList&);
	void copyCallingObjLonger(const StudentList&);
	void copyObjectsSameLength(const StudentList&);
	void copyCallingObjShorter(const StudentList&);

}; 
#endif