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
struct CheckInCell;
struct CheckInBoard;
struct Lecturer;
struct Time;
struct Staff;
//definition

struct CoreData{
    int numOfClasses = 0;
    Class *pHeadClass = NULL;
    int numOfYears = 0 ;
    Year *pHeadYear = NULL;    //pHead cua Year
    int numOfLecturers = 0;
    Lecturer *pHeadLecturer = NULL;
    int numOfStaffs = 0;
    Staff *pHeadStaff = NULL;
};
struct Lecturer{
    string name;
    Lecturer *next = NULL;
};
struct Staff{
    string name;
    Staff *next = NULL;
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
struct CheckInCell{
    CheckInCell *next = NULL;
    bool checked = false;
    long long startTime, endTime;
};
struct CheckInBoard{
    int numOfDays = 0;
    CheckInCell *pHeadCell = NULL, *pTailCell = NULL;

};
struct CourseManager{
    string year, semester;
    CourseManager *next = NULL, *pre = NULL;
    Course *pCourse = NULL;
    ScoreBoard scoreBoard;
    CheckInBoard checkIn;
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
struct TimeInfo{
    int date, month, year, minnute, hour;
    long long toInt(string s); 
    bool setDate(string s);
    bool setTime(string s);
    long long getTimeCode();
    void constructor(long long code);

};
void importDataBase(string pathName, CoreData &data);
void saveToDataBase(string pathName, CoreData data);
void showDataStudent(CoreData data);
void showCourse(CoreData data);
void parseString(string &s);
long long hashPass(string s);
//Class - Student
bool findStudent(long long id, CoreData data, Student *&st, Class *&ofClass);
bool removeStudent(long long id, CoreData &data);
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
void addNewCourse(string inYear, string inSemester, Course *&newCourse, CoreData &data);
void addNewCourse(Semester *curSem, Course *&newCourse);
void addStudentToCourse(Student *&curStudent, Course *&curCourse, string inYear, string inSemester);
void linkStudentToCourse(Student *&curStudent, Course *&curCourse, string inYear, string inSemester);
bool findStudentInCourse(long long stId, StudentManager *&foundStudentManager, Course *curCourse);
void removeCourse(Semester *curSem ,Course *curCourse);
bool removeCourse(string yearName, string semesterName, string courseID, CoreData &data);
void deallocateCourse(Course *curCourse);
void deallocateCourseManager(CourseManager *curCourseManager);
void deallocateStudentManager(StudentManager *curStudentManager);
void removeStudentFromCourse(long long stID, Course *curCourse);
//Time  - checkIn
int getDaysOfMonth(int month, int year);
int getDayOfWeek(int date, int month, int year); //0 == Sun
int getDayFromString(string s);  //"Sun" -> 0
int getMonthFromString(string s);
TimeInfo nextDayOf(TimeInfo curDay);
TimeInfo getFirstDay(TimeInfo startDate, int dayOfWeek);
void createCheckInBoard(string startDate, string endDate, string startHour, string endHour, int dayOfWeek, CheckInBoard &checkIn);
void addCheckInCell(CheckInBoard &checkIn, CheckInCell *tmpCell); 
TimeInfo getCurrentTime();
//Lecturer - Staff;
bool findLecturer(string nameLec, CoreData data, Lecturer *foundLecturer);
bool findStaff(string nameStaff, CoreData data, Staff *foundStaff);
#endif /* Data_hpp */
///Users/lforestor/Dev/CS/162/Project/Project/Project/Courses.csv
