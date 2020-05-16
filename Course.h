#ifndef Course_h
#define Course_h

#include "Data.hpp"

//MENU
void menuCourse(string pathName, CoreData& data);
void activity1(string pathName, CoreData& data);
void activity2(string pathName, CoreData& data);
void activity3(string pathName, CoreData& data);
void activity4(CoreData data);
void activity5(string pathName, CoreData& data);
void activity6(string pathName, CoreData& data);
void activity7(string pathName, CoreData& data);
void activity8(CoreData data);
void activity9(string pathName, CoreData& data);
void activity10(string pathName, CoreData& data);
void activity11(string pathName, CoreData& data);
void activity12(string pathName, CoreData& data);
void activity13(string pathName, CoreData& data);
void activity14(string pathName, CoreData& data);
void activity15(CoreData data);
void activity16(CoreData data);

void (*returnMenu1Arg(int actNum))(CoreData);
void exit(CoreData data);
void (*returnMenu2Arg(int actNum))(string, CoreData&);
void exit2(string tmp, CoreData& data);

//ACADEMIC YEARS
void yearMenu(Year*& curYear, CoreData data);
void displayYearInfo(Year* curYear);
void editYear(Year*& curYear, CoreData& data);
void removeYear(Year*& curYear, CoreData& data);

//SEMESTERS
void semesterMenu(Year*& curYear, Semester*& curSem, CoreData data);
void displaySemInfo(Semester* curSem);
void editSem(Year*& curYear, Semester*& curSem, CoreData& data);
void removeSemDirect(Year*& curYear, Semester*& curSem, CoreData& data);
void removeSemIndirect(Year*& curYear, Semester*& curSem, CoreData& data);

//COURSES
void courseMenu(Year*& curYear, Semester*& curSem, Course*& curCourse, CoreData data);
void displayCourseInfo(Course* curCourse);
void editCourse(Year* curYear, Semester* curSem, Course*& curCourse, CoreData& data);
void createNewEmptyCourse(string yearName, string semesterName, string courseID, CoreData& data);
void inputCourseDetail(string inYear, string inSemester, Course*& newCourse, CoreData data);
void importCourse(ifstream& fin, string inYear, string inSemester, Course*& newCourse, CoreData& data);
void importCourse(string address, string yearName, string semesterName, CoreData& data);
void displayCoursesCurSem(Year* curYear, Semester* curSem);
void displayStdInCourse(Year* curYear, Semester* curSemester, Course* curCourse);

//LECTURERS


#endif