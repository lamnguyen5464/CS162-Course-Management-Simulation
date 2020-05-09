//
//  Data.hpp
//  Project
//
//  Created by Lam Nguyen on 4/18/20.
//  Copyright © 2020 Lam Nguyen. All rights reserved.
//

#ifndef Data_hpp
#define Data_hpp

#include <cstdio>
#include <iostream>
using namespace std;
struct Class;
struct CoreData;
struct Student;
struct Course;
struct ScoreBoard;
struct Year;
struct Semester;
struct CourseManager;
struct StudentManager;
struct CheckIn;
struct Lecturer;
//definition

struct CoreData{
    int numOfClasses = 0;
    Class *pHeadClass = NULL;
    int numOfYears = 0 ;
    Year *pHeadYear = NULL;    //pHead cua Year
    int numOfLecturers = 0;
    Lecturer *pHeadLecturer = NULL;
};

struct Class{
    string name;
    int numOfStudents = NULL;
    Class *next = NULL;
    Student *pHeadStudent = NULL, *pTailStudent = NULL;
};
struct Student{
    Student *next = NULL;
    long long id, hashPassword;
    string  lastName, firstName, dOB, gender;
    int numOfCourse = 0;
    CourseManager *pHeadCourseManager = NULL;
};
struct ScoreBoard{
    double midTerm = -1, finalTerm = -1, lab = -1, bonus = -1;
};
struct CourseManager{
    string year, semester;
    CourseManager *next = NULL, *pre = NULL;
    Course *pCourse = NULL;
    ScoreBoard scoreBoard;
    CheckIn *checkin = NULL;
    StudentManager *pStudentManager;
    
};
struct StudentManager{
    StudentManager *next=NULL, *pre=NULL;
    CourseManager *pCourseManager;
    Student *pStudent;
};
struct Year{
    string name;
    int numOfSems = 0;
    Year *next = NULL;
    Semester *pHeadSemesters = NULL;  //pHead of semester
};
struct Semester{
    int numOfCourses = 0;
    string name;
    Semester *next = NULL;
    Course *pHeadCourse = NULL;
}; 
struct Course{
    Course *next = NULL, *pre = NULL; 
    string id, name, lectureAccount, startDate, endDate, dayOfWeek, room, startHour, endHour; //hh:mm
    StudentManager *pHeadStudentManager = NULL;
};
//YYYYmmDDhhMMss -> long long
struct CheckIn{
    bool result;
    long long start, end;
};
void importDataBase(string pathName, CoreData &data);
void saveToDataBase(string pathName, CoreData data);
void showDataStudent(CoreData data);
void parseString(string &s);
long long hashPass(string s);
//Class - Student
bool findStudent(long long id, CoreData data, Student *&st, Class *&ofClass);
void removeStudent(long long id, CoreData &data);
bool findClass(string className, CoreData data, Class *&foundClass);
void deallocateStudent(Student *&st);
void createNewEmptyClass(string className, CoreData &data);
void addStudentToClass(Class *&pClass, Student *& tmpSt);
void addStudentToClass(string className, Student *&st, CoreData &data);
//Year - Semester - Course
bool findYear(string yearName, Year *&foundYear, CoreData data);
void createNewEmptyYear(string yearName, CoreData &data);
bool findSemester(string yearName, string semesterName, Semester *&foundSemester, CoreData data);
void createNewEmptySemester(string yearName, string semesterName, CoreData &data);
bool findCourse(string yearName, string semesterName, string courseID, Course *&foundCourse, CoreData data);
bool findCourse(string courseID, Semester *curSemester, Course *&foundCourse, CoreData data);
void removeCourse(string yearName, string semesterName, string courseID, Course *&foundCourse, CoreData &data);
void addNewCourse(string inYear, string inSemester, Course *&newCourse, CoreData &data);
void addNewCourse(Semester *curSem, Course *&newCourse);
void addStudentToCourse(Student *&curStudent, Course *&curCourse, string inYear, string inSemester);
bool findStudentInCourse(long long stId, StudentManager *&foundStudentManager, Course *curCourse);
void removeCourse(Course *curCourse);
void deallocateCourse(Course *curCourse);
void deallocateCourseManager(CourseManager *curCourseManager);
void deallocateStudentManager(StudentManager *curStudentManager);
bool removeCourse(string yearName, string semesterName, string courseID, CoreData &data);
void removeStudentFromCourse(long long stID, Course *curCourse);
#endif /* Data_hpp */
