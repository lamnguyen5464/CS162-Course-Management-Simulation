#ifndef Course_h
#define Course_h 

//MENU
void menuStaffCourse(string pathName, CoreData& data);
void menuStaffScoreboard(string pathName, CoreData& data);
void menuStaffAttendance(string pathName, CoreData& data);
void menuLecturer(string pathName, CoreData& data, Lecturer* curLec);

void activity1_L1(CoreData data);
void activity2(string pathName, CoreData& data);
void activity3(string pathName, CoreData& data);
void activity4(string pathName, CoreData& data);
void activity5(string pathName, CoreData& data);
void activity6(string pathName, CoreData& data);
void activity7(string pathName, CoreData& data);
void activity8(string pathName, CoreData& data);
void activity9(string pathName, CoreData& data);
void activity10(string pathName, CoreData& data);
void activity11(string pathName, CoreData& data);
void activity12(string pathName, CoreData& data);
void activity13_L2(CoreData data);
void activity14_AT1_L3(CoreData data);
void activity15(string pathName, CoreData& data);
void activity16(CoreData data);

void activityAT2(string pathName, CoreData& data);

void activitySC1_L7(CoreData data);
void activitySC2(string pathName, CoreData& data);

void activityL4(string pathName, CoreData& data);
void activityL5(string pathName, CoreData& data);
void activityL6(string pathName, CoreData& data);

void returnMenu1Arg(void (*tmp)(CoreData), CoreData data);
void returnMenu2Arg(void (*tmp)(string, CoreData&), string pathName, CoreData& data);

//ACADEMIC YEARS
void yearMenu(Year*& curYear, CoreData data);
void displayYearInfo(Year* curYear);
void editYear(Year*& curYear, CoreData& data);
void removeYear(Year*& curYear, CoreData& data);

//SEMESTERS
void semesterMenu(Year*& curYear, Semester*& curSem, CoreData data);
void displaySemInfo(Semester* curSem);
void removeSemDirect(Year*& curYear, Semester*& curSem, CoreData& data);
void removeSemIndirect(Year*& curYear, Semester*& curSem, CoreData& data);

//COURSES
void courseMenu(Year*& curYear, Semester*& curSem, Course*& curCourse, CoreData data);
void displayCourseInfo(Course* curCourse);
void editCourse(Year* curYear, Semester* curSem, Course*& curCourse, CoreData& data);
void createNewEmptyCourse(string yearName, string semesterName, string courseID, CoreData& data);
void inputCourseDetail(string inYear, string inSemester, Course*& newCourse, CoreData& data);
void importCourse(ifstream& fin, string inYear, string inSemester, Course*& newCourse, CoreData& data);
void importCourse(string address, string yearName, string semesterName, CoreData& data);
void displayCoursesCurSem(Year* curYear, Semester* curSem);
void viewListOfStudents(Course* curCourse, CoreData data);
int countNumOfStdInCourse(Course* curCourse);

//LECTURERS
void viewLecturerList(CoreData data);
void lecturerMenu(Lecturer*& curLec, CoreData data);
void removeLecturer(Lecturer*& curLec, CoreData& data);

//SCOREBOARD
void displayScoreboard(Course* curCourse);
void editGrade(Course*& curCourse, StudentManager*& curStdMng);
void importScoreboard(string address, Course*& curCourse);
void exportScoreboard(string pathName, Course* curCourse);

void findMaxLengthOfStudentInfo(StudentManager* curStMng, int& last, int& first, int& dob);

//ATTENDANCE
void editAttendance(Course*& curCourse, StudentManager*& curStdMng);
void exportAttendance(string pathName, Course* curCourse, CoreData data);
void viewAttendanceList(Course* curCourse, CoreData data);

#endif
