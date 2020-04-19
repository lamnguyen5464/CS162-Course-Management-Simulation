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
struct CtudentManager;
struct CheckIn;
struct Lecturer;
//definition

struct CoreData{
    int numOfClasses;
    Class *pHeadClass, *pTailClass;
    int numOfYears;
    Year *pHeadYear, *pTailYear;    //pHead cua Year
    int numOfLecturers;
    Lecturer *pLecturer;
};

struct Class{
    string name;
    int numOfStudents;
    Class *next;
    Student *pHeadStudent, *pTailStudent;
};
struct Student{
    long long id;
    string  lastName, firstName, dOB, gender, hashPassword;
    CourseManager *pCourseManager;
    int numOfYears;
    Year *pYear;
};
struct courseManager{
    courseManager *next;
    Course *pCourse;
    ScoreBoard *pScore;
    CheckIn *checkin;
    
};
struct Year{
    string yearName;
    int numOfSems;
    Semester *pHeadSemesters, *pTailSemester;  //pHead of semester
};
struct Semester{
    int numOfCourses;
    string semesterName;
    Course *pHeadCourse;
};
struct studentManager{
    studentManager *next;
    Student *pSt;
};
struct Course{
    string id, name, lectureAccount, startDate, endDate, dayOfWeek, room;
    studentManager *pHeadStudentManager;
};
//YYYYmmDDhhMMss -> long long
struct CheckIn{
    bool result;
    long long start, end;
};
 //1> ab

//2>

void importDataBase(string pathName, CoreData &data);

Student *find(long long id);
#endif /* Data_hpp */
