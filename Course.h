#ifndef Course_h
#define Course_h

#include "Data.hpp"

void menuCourse(CoreData& data);

//ACADEMIC YEARS
void displayYearInfo(Year* curYear, CoreData data);
void editYear(Year*& curYear, CoreData& data);
void deleteYear(Year*& curYear, CoreData& data);
void displayAllYears(CoreData data);
void displayYearInfo(Year* curYear, CoreData data);


//SEMESTERS
void displayAllSemesters(CoreData data);
void editSem(Semester*& curSem, CoreData& data);
void displaySemInfo(Semester* curSem, CoreData data);

//COURSES
void displayAllCourses(CoreData data);
void displayCourseInfo(Course* curCourse, CoreData data);
void importCourse(string address, CoreData& data);
void inputCourseDetail(Course*& newCourse);
void removeStdFromCourse(Course*& curCourse, CoreData& data);
void displayCoursesCurSem(Semester* curSem, CoreData data);
void displayStdInCourse(Course* curCourse, CoreData data);

//LECTURERS


#endif
