#include <fstream>
#include <iostream>
#include <string>
#include "Data.hpp"
#include "Course.h"
#include "class.h"
#include <iomanip>

//DISPLAYS
void displayYearInfo(Year* curYear)
{
	Year* tmpYear = curYear;
	cout << "		Name: " << tmpYear->name << endl;
	cout << "		Number of semesters: " << tmpYear->numOfSems << endl;
	cout << "		Semesters' details: " << endl;
	Semester* tmpSem = tmpYear->pHeadSemesters;
	while (tmpSem != NULL) 
	{
		cout << "			" << tmpSem->name << endl;
		tmpSem = tmpSem->next;
	}
}
void displaySemInfo(Semester* curSem)
{
	Semester* tmpSem = curSem;
	cout << "		Name: " << tmpSem->name << endl;
	cout << "		Number of courses: " << tmpSem->numOfCourses << endl;
	cout << "		Courses' details: " << endl;
	Course* tmpCourse = tmpSem->pHeadCourse;
	while (tmpCourse != NULL) {
		cout << "			" << tmpCourse->id << endl;
		tmpCourse = tmpCourse->next;
	}
}
void displayCourseInfo(Course* curCourse)
{
	cout << "						Course ID: " << curCourse->id << endl;
	cout << "						Course name: " << curCourse->name << endl;
	cout << "						Lecturer Account: " << curCourse->lectureAccount << endl;
	cout << "						Start date: " << curCourse->startDate << endl;
	cout << "						End date: " << curCourse->endDate << endl;
	cout << "						Day of week: " << curCourse->dayOfWeek << endl;
	cout << "						Start hour: " << curCourse->startHour << endl;
	cout << "						End hour: " << curCourse->endHour << endl;
	cout << "						Room: " << curCourse->room << endl;
}
void displayCoursesCurSem(Year* curYear, Semester* curSem)
{
	cout << endl << "				Courses of " << curSem->name << " of " << curYear->name << ": " << endl;
	Course* tmpCourse = curSem->pHeadCourse;
	for (int i = 1; tmpCourse != NULL; ++i)
	{
		cout << "					" << i << ". " << tmpCourse->id << endl;
		tmpCourse = tmpCourse->next;
	}
}
void viewListOfStudents(Course* curCourse, CoreData data) {
	StudentManager* tmpStMng = curCourse->pHeadStudentManager;
	if (tmpStMng == NULL) {
		cout << "	There is no student in this course." << endl;
		return;
	}
	else {
		int last = 10, first = 10, dob = 0;
		findMaxLengthOfStudentInfo(tmpStMng, last, first, dob);
		int k = (last + first + dob + 30);
		tmpStMng = curCourse->pHeadStudentManager;
		int i = 1;
		cout << endl << "        " << setw(k / 2 + 7) << right << "STUDENTS IN COURSE " << curCourse->name << endl;
		cout << "       " << "|" << "No" << " |" << setw(8) << left << "ID" << "|" << "  " << setw(last) << left << "Last name" << "  |" << "  " << setw(first) << left << "First name" << "  |" << "  " << setw(dob) << left << "DOB" << "  |" << "  " << setw(6) << left << "Gender" << "  |" << "  " << setw(6) << left << "Class" << "  |" << endl;
		while (tmpStMng != NULL) {
			Student* tmpSt;
			Class* ofClass;
			findStudent(tmpStMng->pStudent->id, data, tmpSt, ofClass);
			cout << "       " << "|" << i << ". |" << setw(8) << left << tmpStMng->pStudent->id << "|" << "  " << setw(last) << left << tmpStMng->pStudent->lastName << "  |" << "  " << setw(first) << left << tmpStMng->pStudent->firstName << "  |" << "  " << setw(dob) << left << tmpStMng->pStudent->dOB << "  |" << "  " << setw(6) << left << tmpStMng->pStudent->gender << "  |" << "  " << setw(6) << left << ofClass->name << "  |" << endl;
			tmpStMng = tmpStMng->next;
			++i;
		}
	}
	return;
}
void displayScoreboard(Course* curCourse)
{
	StudentManager* tmpStMng = curCourse->pHeadStudentManager;
	if (tmpStMng == NULL) {
		cout << "       There is no student in this course." << endl;
		return;
	}
	else {
		int last = 10, first = 10, dob = 0;
		findMaxLengthOfStudentInfo(tmpStMng->pStudent, last, first, dob);
		int k = (last + first + 70);
		tmpStMng = curCourse->pHeadStudentManager;
		int i = 1;
		cout << endl << "        " << setw(k / 2 + 7) << right << "SCOREBOARD FOR " << curCourse->id << endl;
		cout << "	Lecturer: " << curCourse->lectureAccount << setw(8) << left << "  Number of students: " << countNumOfStdInCourse(curCourse) << setw(8) << left << "  Duration: " << curCourse->startDate << " - " << curCourse->endDate << endl;
		cout << "       " << "|" << "No" << " |" << setw(8) << left << "ID" << "|" << "  " << setw(last) << left << "Last name" << "  |" << "  " << setw(first) << left << "First name" << "  |"
			<< "  " << setw(8) << left << "Midterm" << " |" << "  " << setw(8) << left << "Final" << " |" << "  " << setw(8) << left << "Lab" << " |" << "  " << setw(8) << left << "Bonus" << " |" << endl;
		while (tmpStMng != NULL) {
			cout << "       " << "|" << i << ". |" << setw(8) << left << tmpStMng->pStudent->id << "|" << "  " << setw(last) << left << tmpStMng->pStudent->lastName << "  |" << "  " << setw(first) << left << tmpStMng->pStudent->firstName << "  |";
				
			//if scores are still -1, display nothing
			if (tmpStMng->pCourseManager->scoreBoard.midTerm != -1)
				cout << "  " << setw(8) << left << fixed << setprecision(1) << tmpStMng->pCourseManager->scoreBoard.midTerm << " |";
			else
				cout << "  " << setw(8) << left << " " << " |";

			if (tmpStMng->pCourseManager->scoreBoard.finalTerm != -1)
				cout << "  " << setw(8) << left << fixed << setprecision(1) << tmpStMng->pCourseManager->scoreBoard.finalTerm << " |";
			else
				cout << "  " << setw(8) << left << " " << " |";

			if (tmpStMng->pCourseManager->scoreBoard.lab != -1)
				cout << "  " << setw(8) << left << fixed << setprecision(1) << tmpStMng->pCourseManager->scoreBoard.lab << " |";
			else
				cout << "  " << setw(8) << left << " " << " |";

			if (tmpStMng->pCourseManager->scoreBoard.bonus != -1)
				cout << "  " << setw(8) << left << fixed << setprecision(1) << tmpStMng->pCourseManager->scoreBoard.bonus << " |" << endl;
			else
				cout << "  " << setw(8) << left << " " << " |" << endl;

			tmpStMng = tmpStMng->next;
			++i;
		}
	}
	return;
}
void viewAttendanceList(Course* curCourse, CoreData data)
{
	StudentManager* tmpStMng = curCourse->pHeadStudentManager;
	if (tmpStMng == NULL) {
		cout << "	There is no student in this course." << endl;
		return;
	}
	else {
		int last = 10, first = 10, dob = 0;
		findMaxLengthOfStudentInfo(tmpStMng, last, first, dob);
		int k = (last + first + dob + 30);
		tmpStMng = curCourse->pHeadStudentManager;
		int i = 1;
		cout << endl << "        " << setw(k / 2 + 7) << right << "ATTENDANCE LIST OF " << curCourse->id << endl;
		cout << "	Lecturer: " << curCourse->lectureAccount << setw(8) << left << "  Number of students: " << countNumOfStdInCourse(curCourse) << setw(8) << left << "  Duration: " << curCourse->startDate << " - " << curCourse->endDate << setw(8) << left << "  Time: " << curCourse->startHour << " - " << curCourse->endHour << setw(8) << left << "  Day of Week: " << curCourse->dayOfWeek << endl;
		cout << "|" << "No" << " |" << setw(8) << left << "ID" << "|" << "  " << setw(last) << left << "Last name" << "  |" << "  " << setw(first) << left << "First name" << "  |" << "  " << setw(dob) << left << "DOB" << "  |" << "  " << setw(6) << left << "Class" << "  |";
		for (int i = 1; i <= tmpStMng->pCourseManager->checkIn.numOfDays; ++i)
		{
			cout << " W" << setw(2) << left << i << " |";
		}
		cout << endl;
		while (tmpStMng != NULL) {
			Student* tmpSt;
			Class* ofClass;
			findStudent(tmpStMng->pStudent->id, data, tmpSt, ofClass);
			cout << "|" << i << ". |" << setw(8) << left << tmpStMng->pStudent->id << "|" << "  " << setw(last) << left << tmpStMng->pStudent->lastName << "  |" << "  " << setw(first) << left << tmpStMng->pStudent->firstName << "  |" << "  " << setw(dob) << left << tmpStMng->pStudent->dOB << "  |" << "  " << setw(6) << left << ofClass->name << "  |";
			for (CheckInCell* tmpCheckIn = tmpStMng->pCourseManager->checkIn.pHeadCell; tmpCheckIn != NULL; tmpCheckIn = tmpCheckIn->next)
			{
				if (tmpCheckIn->checked == true)
					cout << setw(4) << left << "  x";
				else
					cout << setw(4) << left << "   ";
				cout << " |";
			}
			cout << endl;
			tmpStMng = tmpStMng->next;
			++i;
		}
	}
	return;
}
void viewLecturerList(CoreData data)
{
	cout << "Number of lecturers: " << data.numOfLecturers << endl;
	Lecturer* tmpLec = data.pHeadLecturer;
	int i = 1;
	for (tmpLec; tmpLec != NULL; tmpLec = tmpLec->next)
		cout << "	" << i++ << ". " << tmpLec->userName << endl;
}

//EDITS
void editYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "	CHOSEN YEAR INFO: " << endl;
	displayYearInfo(curYear);
	cout << endl << "EDIT NAME? (0 - NO, 1 - YES)" << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice: ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
		{
			cin.ignore();
			cout << endl << "New academic year name (INPUT 0 TO CANCEL): ";
			string tmpYearName;
			getline(cin, tmpYearName);
			if (tmpYearName != "0")
			{
				Year* tmpYear = NULL;
				while (findYear(tmpYearName, tmpYear, data))
				{
					cout << "The year " << tmpYearName << " has already existed! Try again." << endl;
					cout << endl << "New academic year name (INPUT 0 TO CANCEL): ";
					getline(cin, tmpYearName);
					if (tmpYearName == "0") return;
				}

				curYear->name = tmpYearName;
				//Edit the year of students in that academic year
				if (curYear->pHeadSemesters != NULL)
				{
					Semester* tmpSem = curYear->pHeadSemesters;
					while (tmpSem != NULL)
					{
						if (tmpSem->pHeadCourse != NULL)
						{
							Course* tmpCourse = tmpSem->pHeadCourse;
							while (tmpCourse != NULL)
							{
								if (tmpCourse->pHeadStudentManager != NULL)
								{
									StudentManager* tmpStdMng = tmpCourse->pHeadStudentManager;
									while (tmpStdMng != NULL)
									{
										tmpStdMng->pCourseManager->year = curYear->name;
										tmpStdMng = tmpStdMng->next;
									}
								}
								tmpCourse = tmpCourse->next;
							}
						}
						tmpSem = tmpSem->next;
					}
				}
				cout << "Update successfully!" << endl;
			}
			return;
		}
		default:
			showOption = false;
			break;
		}
	}
}
void editCourse(Year* curYear, Semester* curSem, Course*& curCourse, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "						CHOSEN COURSE INFO: " << endl;
	displayCourseInfo(curCourse);
	cout << endl << "						What part do you want to edit? " << endl;
	cout << "							1.Name" << endl;
	cout << "							2.Lecturer account" << endl;
	cout << "							3.Room" << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice (0 to return): ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
		{
			cin.ignore();
			cout << "New course name (INPUT 0 TO CANCEL): ";
			string tmpCourseName;
			getline(cin, tmpCourseName);
			if (tmpCourseName != "0")
			{
				curCourse->name = tmpCourseName;
				cout << "Update successfully!" << endl;
			}
			break;
		}
		case 2:
		{
			cin.ignore();
			cout << "New lecturer account (INPUT 0 TO CANCEL): ";
			string tmpLecAcc;
			getline(cin, tmpLecAcc);
			if (tmpLecAcc != "0")
			{
				curCourse->lectureAccount = tmpLecAcc;
				Lecturer* tmpLec = NULL;
				if (!findLecturer(curCourse->lectureAccount, data, tmpLec))
					addLecturer(hashPass(curCourse->lectureAccount), curCourse->lectureAccount, data);
				cout << "Update successfully!" << endl;
			}
			break;
		}
		case 3:
		{
			cin.ignore();
			cout << "New room (INPUT 0 TO CANCEL): ";
			string tmpRoom;
			getline(cin, tmpRoom);
			if (tmpRoom != "0")
			{
				curCourse->room = tmpRoom;
				cout << "Update successfully!" << endl;
			}
			break;
		}
		default:
			showOption = false;
			break;
		}
	}
}
void createNewEmptyCourse(string yearName, string semesterName, string courseID, CoreData& data) {
	Semester* curSem;
	if (findSemester(yearName, semesterName, curSem, data)) {
		Course* newCourse;
		curSem->numOfCourses++;
		newCourse = new Course;
		newCourse->id = courseID;
		inputCourseDetail(yearName, semesterName, newCourse, data);
		if (newCourse != NULL)
		{
			newCourse->next = curSem->pHeadCourse;
			curSem->pHeadCourse = newCourse;
			cout << "Create course " << newCourse->id << " of semester " << semesterName << " of year " << yearName << " successfully!" << endl;
		}
		else
			curSem->numOfCourses--;
	}
}
void removeYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "	CHOSEN YEAR INFO: " << endl;
	displayYearInfo(curYear);
	cout << endl << "DELETE? (0 - NO, 1 - YES)" << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice: ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
		{
			//Remove all semesters of current year
			Semester* tmpSem = curYear->pHeadSemesters;
			Semester* tmpSem2 = tmpSem;
			while (tmpSem != NULL)
			{
				tmpSem = tmpSem->next;
				removeSemIndirect(curYear, tmpSem2, data);
				tmpSem2 = tmpSem;
				curYear->pHeadSemesters = tmpSem2;
			}

			data.numOfYears--;
			if (curYear == data.pHeadYear)
			{
				data.pHeadYear = curYear->next;
			}
			else 
			{
				Year* tmpYear = data.pHeadYear;
				while (tmpYear->next != curYear)
				{
					tmpYear = tmpYear->next;
				}
				tmpYear->next = curYear->next;
			}

			cout << "Delete successfully!" << endl;
			return;
		}
		default:
			showOption = false;
			break;
		}
	}
}
void removeSemDirect(Year*& curYear, Semester*& curSem, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "	CHOSEN SEMESTER INFO: " << endl;
	displaySemInfo(curSem);
	cout << endl << "DELETE? (0 - NO, 1 - YES)" << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice: ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
		{
			//Remove all courses of current semesters
			Course* tmpCourse = curSem->pHeadCourse;
			while (tmpCourse != NULL)
			{
				curSem->pHeadCourse = curSem->pHeadCourse->next;
				removeCourse(curSem, tmpCourse);
				tmpCourse = curSem->pHeadCourse;
			}

			curYear->numOfSems--;
			if (curSem == curYear->pHeadSemesters)
			{
				curYear->pHeadSemesters = curSem->next;
			}
			else {
				Semester* tmpSem = curYear->pHeadSemesters;
				if (tmpSem != NULL)
				{
					while (tmpSem->next != curSem)
					{
						tmpSem = tmpSem->next;
					}
					tmpSem->next = curSem->next;
				}
			}

			cout << "Delete successfully!" << endl;
			return;
		}
		default:
			showOption = false;
			break;
		}
	}
}
void removeSemIndirect(Year*& curYear, Semester*& curSem, CoreData& data)
{
	//Remove all courses of current semesters
	Course* tmpCourse = curSem->pHeadCourse;
	while (tmpCourse != NULL)
	{
		curSem->pHeadCourse = curSem->pHeadCourse->next;
		removeCourse(curSem, tmpCourse);
		tmpCourse = curSem->pHeadCourse;
	}

	curYear->numOfSems--;
	if (curSem == curYear->pHeadSemesters)
	{
		curYear->pHeadSemesters = curSem->next;
	}
	else {
		Semester* tmpSem = curYear->pHeadSemesters;
		if (tmpSem->next != NULL)
		{
			while (tmpSem->next != curSem)
			{
				tmpSem = tmpSem->next;
			}
			tmpSem->next = curSem->next;
		}
	}
}
void editGrade(Course*& curCourse, StudentManager*& curStdMng)
{
	cout << endl << "	CHOSEN STUDENT'S INFO: " << endl;
	cout << "		STUDENT " << curStdMng->pStudent->id << " - " << curStdMng->pStudent->lastName << " " << curStdMng->pStudent->firstName << ":" << endl;
	cout << "		Midterm: " << curStdMng->pCourseManager->scoreBoard.midTerm << " | Final: " << curStdMng->pCourseManager->scoreBoard.finalTerm
		<< " | Lab: " << curStdMng->pCourseManager->scoreBoard.lab << " | Bonus: " << curStdMng->pCourseManager->scoreBoard.bonus << endl;
	cout << "			What part do you want to edit?: " << endl;
	cout << "				1.Midterm" << endl;
	cout << "				2.Final" << endl;
	cout << "				3.Lab" << endl;
	cout << "				4.Bonus" << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "				Your choice (0 to return): ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
		{
			cin.ignore();
			cout << "New midterm grade (INPUT -1 TO CANCEL): ";
			double tmpMidterm;
			cin >> tmpMidterm;
			if (tmpMidterm != -1)
			{
				curStdMng->pCourseManager->scoreBoard.midTerm = tmpMidterm;
				cout << "Update successfully!" << endl;
			}
			break;
		}
		case 2:
		{
			cin.ignore();
			cout << "New final grade (INPUT -1 TO CANCEL): ";
			double tmpFinal;
			cin >> tmpFinal;
			if (tmpFinal != -1)
			{
				curStdMng->pCourseManager->scoreBoard.finalTerm = tmpFinal;
				cout << "Update successfully!" << endl;
			}
			break;
		}
		case 3:
		{
			cin.ignore();
			cout << "New lab grade (INPUT -1 TO CANCEL): ";
			double tmpLab;
			cin >> tmpLab;
			if (tmpLab != -1)
			{
				curStdMng->pCourseManager->scoreBoard.lab = tmpLab;
				cout << "Update successfully!" << endl;
			}
			break;
		}
		case 4:
		{
			cin.ignore();
			cout << "New bonus grade (INPUT -1 TO CANCEL): ";
			double tmpBonus;
			cin >> tmpBonus;
			if (tmpBonus != -1)
			{
				curStdMng->pCourseManager->scoreBoard.bonus = tmpBonus;
				cout << "Update successfully!" << endl;
			}
			break;
		}
		default:
			showOption = false;
			break;
		}
	}
}
void editAttendance(Course*& curCourse, StudentManager*& curStdMng)
{
	cout << endl << "Input number of the week you want to edit attendance." << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "	Your choice (0 to return): ";
		cin >> yourChoice;
		if (yourChoice == 0)
			return;
		else if (yourChoice > 0 && yourChoice <= curStdMng->pCourseManager->checkIn.numOfDays)
		{
			CheckInCell* tmpCheckIn = curStdMng->pCourseManager->checkIn.pHeadCell;
			for (int i = 1; i < yourChoice; ++i)
				tmpCheckIn = tmpCheckIn->next;
			tmpCheckIn->checked = !tmpCheckIn->checked;
			cout << "Update successfully!" << endl;
		}
		else
			showOption = false;
	}
}
void removeLecturer(Lecturer*& curLec, CoreData& data)
{
	cout << endl << "DELETE LECTURER " << curLec->userName << "? (0 - NO, 1 - YES)" << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice: ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
		{
			data.numOfLecturers--;
			if (curLec == data.pHeadLecturer)
			{
				data.pHeadLecturer = curLec->next;
			}
			else 
			{
				Lecturer* tmpLec = data.pHeadLecturer;
				while (tmpLec->next != curLec)
				{
					tmpLec = tmpLec->next;
				}
				tmpLec->next = curLec->next;
			}

			cout << "Delete successfully!" << endl;
			return;
		}
		default:
			showOption = false;
			break;
		}
	}
}

//INPUT
void importCourse(ifstream& fin, string inYear, string inSemester, Course*& newCourse, CoreData& data)
{
	getline(fin, newCourse->name, ',');
	string tmpClassName;
	Class* tmpClass = NULL;
	getline(fin, tmpClassName,',');
	toUpper(tmpClassName);
	getline(fin, newCourse->lectureAccount, ',');
	getline(fin, newCourse->startDate, ',');
	getline(fin, newCourse->endDate, ',');
	getline(fin, newCourse->dayOfWeek, ',');
	getline(fin, newCourse->startHour, ',');
	getline(fin, newCourse->endHour, ',');
	getline(fin, newCourse->room, '\n');
	newCourse->id += " - " + tmpClassName;
	Course* tmpCourse = NULL;
	if (findCourse(inYear, inSemester, newCourse->id, tmpCourse, data))
	{
		cout << "The course " << newCourse->id << " of semester " << inSemester << " of year " << inYear << " is already existing!" << endl;
		delete newCourse;
		newCourse = NULL;
		return;
	}
	if (findClass(tmpClassName, data, tmpClass))
	{
		Lecturer* tmpLec = NULL;
		if (!findLecturer(newCourse->lectureAccount, data, tmpLec))
		{
			addLecturer(hashPass(newCourse->lectureAccount), newCourse->lectureAccount, data);
		}

		if (tmpClass->pHeadStudent != NULL)
		{
			Student* tmpStd = tmpClass->pHeadStudent;
			while (tmpStd != NULL)
			{
				addStudentToCourse(tmpStd, newCourse, inYear, inSemester);
				tmpStd = tmpStd->next;
			}
		}
	}
	else
	{
		cout << "Class " << tmpClassName << " for course " << newCourse->id << " does not exist! Edit this course in your .csv file and try again." << endl;
		delete newCourse;
		newCourse = NULL;
		return;
	}
}
void importCourse(string address, string yearName, string semesterName, CoreData& data)
{
	ifstream fin;
	fin.open(address);
	if (!fin.is_open()) 
	{
		cout << "Not found. Try again." << endl;
		return;
	}
	else
	{
		string headers;
		getline(fin, headers, '\n'); //ignore the headers

		while (!fin.eof())
		{
			string no;
			getline(fin, no, ','); //ignore the number
			string courseID;
			getline(fin, courseID, ',');
			if (!courseID.empty())
			{
				Semester* curSem;
				if (findSemester(yearName, semesterName, curSem, data)) {
					Course* newCourse;
					curSem->numOfCourses++;
					newCourse = new Course;
					newCourse->id = courseID;
					importCourse(fin, yearName, semesterName, newCourse, data);
					if (newCourse != NULL)
					{
						newCourse->next = curSem->pHeadCourse;
						curSem->pHeadCourse = newCourse;
						cout << "Import course " << newCourse->id << " of semester " << semesterName << " of year " << yearName << " successfully!" << endl;
					}
					else
						curSem->numOfCourses--;
				}
			}
		}
		fin.close();
	}
}
void inputCourseDetail (string inYear, string inSemester, Course* &newCourse, CoreData& data)
{
	cout << "Please input your course details (INPUT 0 ANYWHERE TO CANCEL):" << endl;
	cout << "	Course name: ";
	getline(cin, newCourse->name);
	if (newCourse->name == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	cout << "	Account of the lecturer: ";
	getline(cin, newCourse->lectureAccount);
	if (newCourse->lectureAccount == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	cout << "	Start date: ";
	getline(cin, newCourse->startDate);
	if (newCourse->startDate == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	cout << "	End date: ";
	getline(cin, newCourse->endDate);
	if (newCourse->endDate == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	cout << "	Day of the week: ";
	getline(cin, newCourse->dayOfWeek);
	if (newCourse->dayOfWeek == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	cout << "	Start hour: ";
	getline(cin, newCourse->startHour);
	if (newCourse->startHour == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	cout << "	End hour: ";
	getline(cin, newCourse->endHour);
	if (newCourse->endHour == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	cout << "	Room: ";
	getline(cin, newCourse->room);
	if (newCourse->room == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}

	string tmpClassName;
	Class* tmpClass = NULL;
	cout << "	Class: ";
	getline(cin, tmpClassName);
	if (tmpClassName == "0")
	{
		delete newCourse;
		newCourse = NULL;
		return;
	}
	toUpper(tmpClassName);
	
	bool showOption = true;
	while (!findClass(tmpClassName, data, tmpClass))
	{
			if (!showOption)
			{
				cout << "Invalid choice. Try again." << endl;
				showOption = true;
			}
			else
				cout << "	Class " << tmpClassName << " does not exist! Create class " << tmpClassName << "? (0 - RETURN, 1 - YES, 2 - INPUT AGAIN): " << endl;
			int yourChoice;
			cout << "Your choice: ";
			cin >> yourChoice;
			switch (yourChoice)
			{
			case 0:
				delete newCourse;
				newCourse = NULL;
				return;
			case 1:
				createNewEmptyClass(tmpClassName, data);
				cout << "Create class " << tmpClassName << " successfully!" << endl;
				break;
			case 2:
				cin.ignore();
				cout << "	Class: ";
				getline(cin, tmpClassName);
				if (tmpClassName == "0")
				{
					delete newCourse;
					newCourse = NULL;
					return;
				}
				toUpper(tmpClassName);
				break;
			default:
				showOption = false;
				break;
			}
	}

	newCourse->id += " - " + tmpClassName;
	Course* tmpCourse = NULL;
	if (findCourse(inYear, inSemester, newCourse->id, tmpCourse, data))
	{
		cout << "The course " << newCourse->id << " of semester " << inSemester << " of year " << inYear << " is already existing!" << endl;
		delete newCourse;
		newCourse = NULL;
		return;
	}

	Lecturer* tmpLec = NULL;
	if (!findLecturer(newCourse->lectureAccount, data, tmpLec))
	{
		addLecturer(hashPass(newCourse->lectureAccount), newCourse->lectureAccount, data);
	}

	if (tmpClass->pHeadStudent != NULL)
	{
		Student* tmpStd = tmpClass->pHeadStudent;
		while (tmpStd != NULL)
		{
			addStudentToCourse(tmpStd, newCourse, inYear, inSemester);
			tmpStd = tmpStd->next;
		}
	}
}
void importScoreboard(string address, Course* &curCourse)
{
	ifstream fin;
	fin.open(address);
	if (!fin.is_open())
	{
		cout << "Not found. Try again." << endl;
		return;
	}
	else
	{
		string headers;
		getline(fin, headers, '\n'); //ignore the headers

		while (!fin.eof())
		{
			string no;
			getline(fin, no, ','); //ignore the number
			long long stdID;
			fin >> stdID;
			if (stdID != 0)
			{
				fin.ignore(1);
				string lastname;
				getline(fin, lastname, ',');
				string firstname;
				getline(fin, firstname, ',');
				StudentManager* curStdMng = NULL;
				if (findStudentInCourse(stdID, curStdMng, curCourse))
				{
					fin >> curStdMng->pCourseManager->scoreBoard.midTerm;
					fin.ignore(1);
					fin >> curStdMng->pCourseManager->scoreBoard.finalTerm;
					fin.ignore(1);
					fin >> curStdMng->pCourseManager->scoreBoard.lab;
					fin.ignore(1);
					fin >> curStdMng->pCourseManager->scoreBoard.bonus;
					fin.ignore(1);
					cout << "Import grade for student " << stdID << " - " << curStdMng->pStudent->lastName << " " << curStdMng->pStudent->firstName << " successfully!" << endl;
				}
				else
				{
					cout << "There is no student " << stdID << " - " << lastname << " " << firstname << " in this course. Check your .csv file again." << endl;
					fin.ignore(100, '\n');
				}
				stdID = 0;
			}
		}
		fin.close();
	}
}

void exportScoreboard(string pathName, Course* curCourse)
{
	ofstream fout(pathName + curCourse->id + "- Scoreboard.csv");
	fout << "No,Student ID,Last name,First name,Midterm,Final,Lab,Bonus" << endl;
	StudentManager* curStdMng = curCourse->pHeadStudentManager;
	int i = 1;
	while (curStdMng != NULL)
	{
		fout << i++ << "," <<curStdMng->pStudent->id<<","<<curStdMng->pStudent->lastName<<","<<curStdMng->pStudent->firstName << "," << curStdMng->pCourseManager->scoreBoard.midTerm 
			<< "," << curStdMng->pCourseManager->scoreBoard.finalTerm << "," << curStdMng->pCourseManager->scoreBoard.lab << "," << curStdMng->pCourseManager->scoreBoard.bonus << endl;
		curStdMng = curStdMng->next;
	}
	fout.close();
	cout << "Export successfully!" << endl;
}
void exportAttendance(string pathName, Course* curCourse, CoreData data)
{
	StudentManager* tmpStMng = curCourse->pHeadStudentManager;
	ofstream fout(pathName + curCourse->id + "- Attendance.csv");
	fout << "No,Student ID,Last name,First name,DOB,Class";
	for (int j = 1; j <= tmpStMng->pCourseManager->checkIn.numOfDays; ++j)
	{
		fout << ",W" << j;
	}
	fout << endl;
	int i = 1;
	while (tmpStMng != NULL)
	{
		Student* tmpSt;
		Class* ofClass;
		findStudent(tmpStMng->pStudent->id, data, tmpSt, ofClass);
		fout << i++ << "," << tmpStMng->pStudent->id << "," << tmpStMng->pStudent->lastName << "," << tmpStMng->pStudent->firstName << "," << tmpStMng->pStudent->dOB
			<< "," << ofClass->name;
		for (CheckInCell* tmpCheckIn = tmpStMng->pCourseManager->checkIn.pHeadCell; tmpCheckIn != NULL; tmpCheckIn = tmpCheckIn->next)
		{
			if (tmpCheckIn->checked == true)
				fout << ",x";
			else
				fout << ", ";
		}
		fout << endl;
		tmpStMng = tmpStMng->next;
	}
	fout.close();
	cout << "Export successfully!" << endl;
}

//MENUS
void menuLecturer(string pathName, CoreData& data, Lecturer* curLec)
{
	bool showOption = true;
	while (1)
	{
		clearScreen();
		if (showOption)
		{
			cout << "__________________LECTURER__________________" << endl << endl;

			cout << "0. Return to previous menu" << endl;
			cout << endl;

			cout << "1. View academic years, semesters, courses" << endl;
			cout << "2. View list of students in a course" << endl;
			cout << "3. View attendance list of a course" << endl;
			cout << "4. Edit an attendance" << endl;
			cout << "5. Import scoreboard from a .csv file" << endl;
			cout << "6. Edit grade of a student" << endl;
			cout << "7. View a scoreboard" << endl;
			cout << endl;
		}
		else
		{
			cout << "Invalid choice! Please try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice (0-7): ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
			activity1_L1(data);
			break;
		case 2:
			activity13_L2(data);
			break;
		case 3:
			activity14_AT1_L3(data);
			break;
		case 4:
			activityL4(pathName, data);
			break;
		case 5:
			activityL5(pathName, data);
			break;
		case 6:
			activityL6(pathName, data);
			break;
		case 7:
			activitySC1_L7(data);
			break;
		default:
			showOption = false;
			break;
		}
	}
}
void menuStaffScoreboard(string pathName, CoreData& data)
{
	bool showOption = true;
	while (1)
	{
		clearScreen();
		if (showOption)
		{
			cout << "__________________ACADEMIC STAFF-SCOREBOARD__________________" << endl << endl;

			cout << "0. Return to previous menu" << endl;
			cout << endl;

			cout << "1. Search and view scoreboard of a course" << endl;
			cout << "2. Export scoreboard to a .csv file" << endl;
			cout << endl;
		}
		else
		{
			cout << "Invalid choice! Please try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice (0-2): ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
			activitySC1_L7(data);
			break;
		case 2:
			activitySC2(pathName, data);
			break;
		
		default:
			showOption = false;
			break;
		}
	}
}
void menuStaffAttendance(string pathName, CoreData& data)
{
	bool showOption = true;
	while (1)
	{
		clearScreen();
		if (showOption)
		{
			cout << "__________________ACADEMIC STAFF-ATTENDANCE__________________" << endl << endl;

			cout << "0. Return to previous menu" << endl;
			cout << endl;

			cout << "1. Search and view attendance list of a course" << endl;
			cout << "2. Export attendance list to a .csv file" << endl;
			cout << endl;
		}
		else
		{
			cout << "Invalid choice! Please try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice (0-2): ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
			activity14_AT1_L3(data);
			break;
		case 2:
			activityAT2(pathName, data);
			break;

		default:
			showOption = false;
			break;
		}
	}
}
void menuStaffCourse(string pathName, CoreData& data)
{
	bool showOption = true;
	while (1)
	{
		clearScreen();
		if (showOption) 
		{
			cout << "__________________ACADEMIC STAFF-COURSE__________________" << endl << endl;

			cout << "0. Return to previous menu" << endl;
			cout << endl;

			cout << "1. View academic years, semesters, courses" << endl;
			cout << endl;

			cout << "________ACADEMIC YEARS________" << endl;
			cout << "2. Create an academic year" << endl;
			cout << "3. Update an academic year" << endl;
			cout << "4. Delete an academic year" << endl;

			cout << endl;

			cout << "________SEMESTERS________" << endl;
			cout << "5. Create a semester for an academic year" << endl;
			cout << "6. Delete a semester for an academic year" << endl;
			cout << endl;

			cout << "________COURSES________" << endl;
			cout << "7. Import a course from a .csv file" << endl;
			cout << "8. Add a course manually" << endl;
			cout << "9. Edit an existing course" << endl;
			cout << "10. Remove a course" << endl;
			cout << "11. Remove a specific student from a course" << endl;
			cout << "12. Add a specific student to a course" << endl;
			cout << "13. View list of students of a course" << endl;
			cout << "14. View attendance list of a course" << endl;
			cout << endl;

			cout << "________LECTURERS________" << endl;
			cout << "15. Delete a lecturer" << endl;
			cout << "16. View all lecturers" << endl;
			cout << endl;
		}
		else 
		{
			cout << "Invalid choice! Please try again." << endl;
			showOption = true;
		}
	int yourChoice;
	cout << "Your choice (0-16): ";
	cin >> yourChoice;
	switch (yourChoice)
	{
	case 0:
		return;
	case 1:
		activity1_L1(data);
		break;
	case 2:
		activity2(pathName, data);
		break;
	case 3:
		activity3(pathName, data);
		break;
	case 4:
		activity4(pathName, data);
		break;
	case 5:
		activity5(pathName, data);
		break;
	case 6:
		activity6(pathName, data);
		break;
	case 7:
		activity7(pathName, data);
		break;
	case 8:
		activity8(pathName, data);
		break;
	case 9:
		activity9(pathName, data);
		break;
	case 10:
		activity10(pathName, data);
		break;
	case 11:
		activity11(pathName, data);
		break;
	case 12:
		activity12(pathName, data);
		break; 
	case 13:
		activity13_L2(data);
		break;
	case 14:
		activity14_AT1_L3(data);
		break;
	case 15:
		activity15(pathName, data);
		break;
	case 16:
		activity16(data);
		break;
	default:
		showOption = false;
		break;
	}
	}
}

void yearMenu(Year*& curYear, CoreData data)
{
	cout << "Year: " << endl;
	Year* tmpYear = data.pHeadYear;
	for (int i = 1; tmpYear != NULL; ++i)
	{
		cout << "	" << i << ". " << tmpYear->name << endl;
		tmpYear = tmpYear->next;
	}

	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "	Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "	Your choice (INPUT 0 TO GO BACK): ";
		cin >> yourChoice;

		if (yourChoice > 0 && yourChoice <= data.numOfYears)
		{
			tmpYear = data.pHeadYear;
			for (int j = 1; j < yourChoice; ++j)
			{
				tmpYear = tmpYear->next;
			}
			curYear = tmpYear;
			break;
		}
		else if (yourChoice == 0)
		{
			curYear = NULL;
			break;
		}
		else
			showOption = false;
	}
}
void semesterMenu(Year*& curYear, Semester*& curSem, CoreData data)
{
	if (curYear == NULL) yearMenu(curYear, data);
	if (curYear == NULL) return;
	cout << endl << "		Semester: " << endl;
	Semester* tmpSem = curYear->pHeadSemesters;
	for (int i = 1; tmpSem != NULL; ++i)
	{
		cout << "			" << i << ". " << tmpSem->name << endl;
		tmpSem = tmpSem->next;
	}

	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "			Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "			Your choice (INPUT 0 TO GO BACK): ";
		cin >> yourChoice;

		if (yourChoice > 0 && yourChoice <= curYear->numOfSems)
		{
			tmpSem = curYear->pHeadSemesters;
			for (int j = 1; j < yourChoice; ++j)
			{
				tmpSem = tmpSem->next;
			}
			curSem = tmpSem;
			break;
		}
		else if (yourChoice == 0)
		{
			curYear = NULL;
			curSem = NULL;
			semesterMenu(curYear, curSem, data);
			break;
		}
		else
			showOption = false;
	}
}
void courseMenu(Year*& curYear, Semester*& curSem, Course*& curCourse, CoreData data)
{
	if (curSem == NULL) semesterMenu(curYear, curSem, data);
	if (curSem == NULL) return;
	cout << endl << "				Course: " << endl;
	Course* tmpCourse = curSem->pHeadCourse;
	for (int i = 1; tmpCourse != NULL; ++i)
	{
		cout << "					" << i << ". " << tmpCourse->id << endl;
		tmpCourse = tmpCourse->next;
	}

	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "					Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "					Your choice (INPUT 0 TO GO BACK): ";
		cin >> yourChoice;

		if (yourChoice > 0 && yourChoice <= curSem->numOfCourses)
		{
			tmpCourse = curSem->pHeadCourse;
			for (int j = 1; j < yourChoice; ++j)
			{
				tmpCourse = tmpCourse->next;
			}
			curCourse = tmpCourse;
			break;
		}
		else if (yourChoice == 0)
		{
			curSem = NULL;
			curCourse = NULL;
			courseMenu(curYear, curSem, curCourse, data);
			break;
		}
		else
			showOption = false;
	}
}
void lecturerMenu(Lecturer*& curLec, CoreData data)
{
	viewLecturerList(data);
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "	Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "	Your choice (INPUT 0 TO GO BACK): ";
		cin >> yourChoice;

		if (yourChoice > 0 && yourChoice <= data.numOfLecturers)
		{
			Lecturer* tmpLec = data.pHeadLecturer;
			for (int j = 1; j < yourChoice; ++j)
			{
				tmpLec = tmpLec->next;
			}
			curLec = tmpLec;
			break;
		}
		else if (yourChoice == 0)
		{
			curLec = NULL;
			break;
		}
		else
			showOption = false;
	}
}

void activity1_L1(CoreData data)
{
	cout << endl << "_____________VIEW ACADEMIC YEARS, SEMESTERS, COURSES_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		cout << endl;
		displayCourseInfo(curCourse);
	}
	returnMenu1Arg(&activity1_L1, data);
}
void activity2(string pathName, CoreData& data)
{
	cout << endl << "_____________CREATE AN ACADEMIC YEAR_____________" << endl << endl;
	cout << "Year name you want to add (INPUT 0 TO CANCEL): ";
	string curYearName;
	cin.ignore();
	getline(cin, curYearName);
	if (curYearName != "0")
	{
		createNewEmptyYear(curYearName, data);
		cout << "Create succesfully!" << endl;
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity2, pathName, data);
}
void activity3(string pathName, CoreData& data)
{
	cout << endl << "_____________UPDATE AN ACADEMIC YEAR_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		editYear(curYear, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity3, pathName, data);
}
void activity4(string pathName, CoreData& data)
{
	cout << endl << "_____________DELETE AN ACADEMIC YEAR_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		removeYear(curYear, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity4, pathName, data);
}
void activity5(string pathName, CoreData& data)
{
	cout << endl << "_____________CREATE A SEMESTER_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	yearMenu(curYear, data);

	if (curYear != NULL)
	{
		cout << endl << "Year " << curYear->name << "'s number of semesters: " << curYear->numOfSems << endl;
		cout << "CREATE SEMESTER 'HK" << curYear->numOfSems + 1 << "'? (0 - NO, 1 - YES): ";
		int yourChoice;
		cin >> yourChoice;
		if (yourChoice == 1)
		{
			cout << endl << "Creating semester 'HK" << curYear->numOfSems + 1 << "' ..." << endl;
			string curSemester;
			curSemester = "HK" + to_string(curYear->numOfSems + 1);
			createNewEmptySemester(curYear->name, curSemester, data);
			cout << endl << "Create successfully!" << endl;
			saveToDataBase(pathName, data);
		}
	}
	returnMenu2Arg(&activity5, pathName, data);
}
void activity6(string pathName, CoreData& data)
{
	cout << endl << "_____________DELETE A SEMESTER_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);
	if (curSem != NULL)
	{
		removeSemDirect(curYear, curSem, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity6, pathName, data);
}
void activity7(string pathName, CoreData& data)
{
	cout << endl << "_____________IMPORT A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);

	if (curSem != NULL)
	{
		cout << "INPUT .CSV FILE NAME (INPUT 0 TO CANCEL): ";
		string fileName;
		cin.ignore();
		getline(cin, fileName);
		if (fileName != "0")
		{
			importCourse(pathName + fileName, curYear->name, curSem->name, data);
			saveToDataBase(pathName, data);
		}
	}
	returnMenu2Arg(&activity7, pathName, data);
}
void activity8(string pathName, CoreData& data)
{
	cout << endl << "_____________ADD A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);

	if (curSem != NULL)
	{
		cout << "Course ID you want to add (INPUT 0 TO CANCEL): ";
		string curCourseID;
		cin.ignore();
		getline(cin, curCourseID);
		if (curCourseID != "0")
		{
			createNewEmptyCourse(curYear->name, curSem->name, curCourseID, data);
			saveToDataBase(pathName, data);
		}
	}
	returnMenu2Arg(&activity8, pathName, data);
}
void activity9(string pathName, CoreData& data)
{
	cout << endl << "_____________UPDATE A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		editCourse(curYear, curSem, curCourse, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity9, pathName, data);
}
void activity10(string pathName, CoreData& data)
{
	cout << endl << "_____________REMOVE A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		removeCourse(curSem, curCourse);
		cout << "Remove successfully!" << endl;
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity10, pathName, data);
}
void activity11(string pathName, CoreData& data)
{
	cout << endl << "_____________REMOVE A STUDENT FROM A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		viewListOfStudents(curCourse, data);
		if (curCourse->pHeadStudentManager != NULL)
		{
			cout << endl << "Input ID of the student you want to remove from " << curCourse->id << " (INPUT 0 TO CANCEL): ";
			long long stdID;
			cin >> stdID;
			if (stdID != 0)
			{
				StudentManager* stdMng = NULL;
				if (removeStudentFromCourse(stdID, curCourse))
				{
					cout << "Remove successfully!" << endl;
					//saveToDataBase(pathName, data);
				}
				else
					cout << "There is no student with this ID in this course. Try again. " << endl;
			}
		}
	}
	returnMenu2Arg(&activity11, pathName, data);
}
void activity12(string pathName, CoreData& data) 
{
	cout << endl << "_____________ADD A STUDENT TO A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		cout << endl << "Input ID of the student you want to add to " << curCourse->id << " (INPUT 0 TO CANCEL): ";
		long long stdID;
		Student* std;
		Class* stdClass;
		cin >> stdID;
		if (stdID != 0)
		{
			if (findStudent(stdID, data, std, stdClass))
			{
				StudentManager* stdMng = NULL;
				if (!findStudentInCourse(stdID, stdMng, curCourse))
				{
					addStudentToCourse(std, curCourse, curYear->name, curSem->name);

					cout << "Add student " << std->id << " - " << std->lastName << " " << std->firstName << " to " << curCourse->id << " successfully!" << endl;
					saveToDataBase(pathName, data);
				}
				else
					cout << "This student has already existed in this course." << endl;
			}
			else
				cout << "There is no student with this ID. " << endl;
		}
	}
	returnMenu2Arg(&activity12, pathName, data);
}
void activity13_L2(CoreData data)
{
	cout << endl << "_____________LIST OF STUDENTS IN A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		viewListOfStudents(curCourse, data);
	}
	returnMenu1Arg(&activity13_L2, data);
}
void activity14_AT1_L3(CoreData data)
{
	cout << endl << "_____________ATTENDANCE LIST OF A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		viewAttendanceList(curCourse, data);
	}
	returnMenu1Arg(&activity14_AT1_L3, data);
}
void activity15(string pathName, CoreData& data)
{
	cout << endl << "_____________REMOVE A LECTURER_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Lecturer* curLec = NULL;
	lecturerMenu(curLec, data);
	if (curLec != NULL)
	{
		removeLecturer(curLec, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity15, pathName, data);
}
void activity16(CoreData data)
{
	cout << endl << "_____________VIEW ALL LECTURERS_____________" << endl << endl;
	viewLecturerList(data);
	returnMenu1Arg(&activity16, data);
}

void activityAT2(string pathName, CoreData& data)
{
	cout << endl << "_____________EXPORT ATTENDANCE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
		exportAttendance(pathName, curCourse, data);
	returnMenu2Arg(&activityAT2, pathName, data);
}

void activitySC1_L7(CoreData data)
{
	cout << endl << "_____________VIEW SCOREBOARD_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
		displayScoreboard(curCourse);
	returnMenu1Arg(&activitySC1_L7, data);
}
void activitySC2(string pathName, CoreData& data)
{
	cout << endl << "_____________EXPORT SCOREBOARD_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
		exportScoreboard(pathName, curCourse);
	returnMenu2Arg(&activitySC2, pathName, data);
}

void activityL4(string pathName, CoreData& data)
{
	cout << endl << "_____________EDIT AN ATTENDANCE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		viewAttendanceList(curCourse, data);
		cout << endl << "Input the ID of the student you want to edit attendance (INPUT 0 TO CANCEL): ";
		long long stdID;
		cin >> stdID;
		if (stdID != 0)
		{
			StudentManager* curStdMng = NULL;
			while (!findStudentInCourse(stdID, curStdMng, curCourse))
			{
				cout << "There is no student with this ID in " << curCourse->id << ". Try again." << endl;
				cout << "Input the ID of the student you want to edit attendance (INPUT 0 TO CANCEL): ";
				cin >> stdID;
				if (stdID == 0)
				{
					curStdMng = NULL;
					break;
				}
			}
			if (curStdMng != NULL)
			{
				editAttendance(curCourse, curStdMng);
				saveToDataBase(pathName, data);
			}
		}
	}
	returnMenu2Arg(&activityL4, pathName, data);
}
void activityL5(string pathName, CoreData& data)
{
	cout << endl << "_____________IMPORT SCOREBOARD_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		cout << "INPUT .CSV FILE NAME (INPUT 0 TO CANCEL): ";
		string fileName;
		cin.ignore();
		getline(cin, fileName);
		if (fileName != "0")
		{
			importScoreboard(pathName + fileName, curCourse);
			saveToDataBase(pathName, data);
		}
	}
	returnMenu2Arg(&activityL5, pathName, data);
}
void activityL6(string pathName, CoreData& data)
{
	cout << endl << "_____________EDIT GRADE OF A STUDENT_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		displayScoreboard(curCourse);
		cout << endl << "Input the ID of the student you want to edit grade (INPUT 0 TO CANCEL): ";
		long long stdID;
		cin >> stdID;
		if (stdID != 0)
		{
			StudentManager* curStdMng = NULL;
			while (!findStudentInCourse(stdID, curStdMng, curCourse))
			{
				cout << "There is no student with this ID in " << curCourse->id << ". Try again." << endl;
				cout << "Input the ID of the student you want to edit grade (INPUT 0 TO CANCEL): ";
				cin >> stdID;
				if (stdID == 0)
				{
					curStdMng = NULL;
					break;
				}
			}
			if (curStdMng != NULL)
			{
				editGrade(curCourse, curStdMng);
				saveToDataBase(pathName, data);
			}
		}
	}
	returnMenu2Arg(&activityL6, pathName, data);
}

void returnMenu1Arg(void (*tmp)(CoreData), CoreData data)
{
	cout << endl << "Input any number to back and save (1 to run again): ";
	int yourChoice;
	cin >> yourChoice;
	if (yourChoice != 1) return;
	tmp(data);
}
void returnMenu2Arg(void (*tmp)(string, CoreData&), string pathName, CoreData& data)
{
	cout << endl << "Input any number to back and save (1 to run again): ";
	int yourChoice;
	cin >> yourChoice;
	if (yourChoice != 1) return;
	tmp(pathName, data);
}

//add findLength ID and Class
void findMaxLengthOfStudentInfo(StudentManager* curStMng, int& last, int& first, int& dob) {
	while (curStMng != NULL) {
		if ((curStMng->pStudent->lastName).length() > last) last = (curStMng->pStudent->lastName).length();
		if ((curStMng->pStudent->firstName).length() > first) first = (curStMng->pStudent->firstName).length();
		if ((curStMng->pStudent->dOB).length() > dob) dob = (curStMng->pStudent->dOB).length();
		curStMng = curStMng->next;
	}
}
int countNumOfStdInCourse(Course* curCourse)
{
	int count = 0;
	StudentManager* curStdMng = curCourse->pHeadStudentManager;
	while (curStdMng != NULL)
	{
		curStdMng = curStdMng->next;
		count++;
	}
	return count;
}