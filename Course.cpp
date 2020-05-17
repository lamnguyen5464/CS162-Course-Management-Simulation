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
void displayStdInCourse(Year* curYear, Semester* curSemester, Course* curCourse)
{
	cout << endl;
	cout << "Year: " << curYear->name << endl;
	cout << "	Semester: " << curSemester->name << endl;
	cout << "		Course: " << curCourse->name << endl;

	StudentManager* cur = curCourse->pHeadStudentManager;
	int i = 1;
	while (cur != NULL)
	{
		cout << "			" << i++ << ". " << cur->pStudent->lastName << " " << cur->pStudent->firstName << " " << cur->pStudent->id << endl;
		cur = cur->next;
	}
}
void viewListOfStudents(Course* curCourse) {
	StudentManager* tmpStMng = curCourse->pHeadStudentManager;
	if (tmpStMng == NULL) {
		cout << "	There is no student in this course" << endl;
		return;
	}
	else {
		int last = 10, first = 10, dob = 0;
		findMaxLengthOfStudentInfo(tmpStMng->pStudent, last, first, dob);
		int k = (last + first + dob + 30);
		tmpStMng = curCourse->pHeadStudentManager;
		int i = 1;
		cout << endl << "        " << setw(k / 2 + 7) << right << "STUDENTS IN COURSE " << curCourse->name << endl;
		cout << "       " << "|" << "No" << " |" << setw(8) << left << "ID" << "|" << "  " << setw(last) << left << "Last name" << "  |" << "  " << setw(first) << left << "First name" << "  |" << "  " << setw(dob) << left << "DOB" << "  |" << "  " << setw(6) << left << "Gender" << "  |" << endl;
		while (tmpStMng != NULL) {
			cout << "       " << "|" << i << ". |" << setw(8) << left << tmpStMng->pStudent->id << "|" << "  " << setw(last) << left << tmpStMng->pStudent->lastName << "  |" << "  " << setw(first) << left << tmpStMng->pStudent->firstName << "  |" << "  " << setw(dob) << left << tmpStMng->pStudent->dOB << "  |" << "  " << setw(6) << left << tmpStMng->pStudent->gender << "  |" << endl;
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
		cout << "       There is no student in this course" << endl;
		return;
	}
	else {
		int last = 10, first = 10, dob = 0;
		findMaxLengthOfStudentInfo(tmpStMng->pStudent, last, first, dob);
		int k = (last + first + 70);
		tmpStMng = curCourse->pHeadStudentManager;
		int i = 1;
		cout << endl << "        " << setw(k / 2 + 7) << right << "SCOREBOARD FOR " << curCourse->name << endl;
		cout << "       " << "|" << "No" << " |" << setw(8) << left << "ID" << "|" << "  " << setw(last) << left << "Last name" << "  |" << "  " << setw(first) << left << "First name" << "  |"
			<< "  " << setw(8) << left << "Midterm" << "  |" << "  " << setw(8) << left << "Final" << "  |" << "  " << setw(8) << left << "Lab" << "  |" << "  " << setw(8) << left << "Bonus" << "  |" << endl;
		while (tmpStMng != NULL) {
			cout << "       " << "|" << i << ". |" << setw(8) << left << tmpStMng->pStudent->id << "|" << "  " << setw(last) << left << tmpStMng->pStudent->lastName << "  |" << "  " << setw(first) << left << tmpStMng->pStudent->firstName << "  |" 
				<< "  " << setw(8) << left << tmpStMng->pCourseManager->scoreBoard.midTerm << "  |" << "  " << setw(8) << left << tmpStMng->pCourseManager->scoreBoard.finalTerm << "  |" << "  " << setw(8) << left << tmpStMng->pCourseManager->scoreBoard.lab << "  |" << "  " << setw(8) << left << tmpStMng->pCourseManager->scoreBoard.bonus << "  |" << endl;
			tmpStMng = tmpStMng->next;
			++i;
		}
	}
	return;
}

//EDITS
void editYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "CHOSEN YEAR INFO: " << endl;
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
			cout << endl << "New academic year name: ";
			string tmpYearName;
			getline(cin, tmpYearName);
			Year* tmpYear = NULL;
			while (findYear(tmpYearName, tmpYear, data))
			{
				cout << "The year " << tmpYearName << " has already existed! Try again." << endl;
				cout << endl << "New academic year name: ";
				getline(cin, tmpYearName);
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
			cout << "Update successfully " << endl;
			return;
		}
		default:
			showOption = false;
			break;
		}
	}
}
/*void editSem(Year*& curYear, Semester*& curSem, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "CHOSEN SEMESTER INFO: " << endl;
	displaySemInfo(curSem);
	cout << endl << "EDIT? (0 - NO, 1 - YES)" << endl;
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
			cout << "New semester name: ";
			string prevSemName = curSem->name;
			getline(cin, curSem->name);

			//Edit the Sem of students in that semester
			if (curSem->name != prevSemName && curSem->pHeadCourse != NULL)
			{
				Course* tmpCourse = curSem->pHeadCourse;
				while (tmpCourse != NULL)
				{
					if (tmpCourse->pHeadStudentManager != NULL)
					{
						StudentManager* tmpStdMng = tmpCourse->pHeadStudentManager;
						while (tmpStdMng != NULL)
						{
							tmpStdMng->pCourseManager->semester = curSem->name;
							tmpStdMng = tmpStdMng->next;
						}
					}
					tmpCourse = tmpCourse->next;
				}
			}
			cout << endl << "UPDATED: " << endl;
			displaySemInfo(curSem);
			return;
		}
		default:
			showOption = false;
			break;
		}
	}
}*/
void editCourse(Year* curYear, Semester* curSem, Course*& curCourse, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "CHOSEN COURSE INFO: " << endl;
	displayCourseInfo(curCourse);
	cout << "What part do you want to edit? " << endl;
	cout << "1.Name" << endl;
	cout << "2.Lecturer account" << endl;
	cout << "3.Room" << endl;
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
			cin.ignore();
			cout << "New course name: ";
			getline(cin, curCourse->name);
			cout << "Update successfully " << endl;
			break;
		case 2:
			cin.ignore();
			cout << "New lecturer account: ";
			getline(cin, curCourse->lectureAccount);
			cout << "Update successfully " << endl;
			break;
		case 3:
			cin.ignore();
			cout << "New room: ";
			getline(cin, curCourse->room);
			cout << "Update successfully " << endl;
			break;
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
		/*if (findCourse(yearName, semesterName, courseID, newCourse, data)) {
			cout << "The course " << courseID << " of semester " << semesterName << " of year " << yearName << " is already existing!" << endl;
			return;
		}*/
		curSem->numOfCourses++;
		newCourse = new Course;
		newCourse->id = courseID;
		inputCourseDetail(yearName, semesterName, newCourse, data);
		//newCourse->pHeadStudentManager = NULL;
		if (newCourse != NULL)
		{
			newCourse->next = curSem->pHeadCourse;
			curSem->pHeadCourse = newCourse;
			cout << "Create course " << courseID << " of semester " << semesterName << " of year " << yearName << " successfully!" << endl;
		}
		else
		{
			curSem->numOfCourses--;
		}
	}
}
void removeYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "CHOSEN YEAR INFO: " << endl;
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
			else {
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
	cout << endl << "CHOSEN SEMESTER INFO: " << endl;
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

			cout << "Delete successfully" << endl;
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
	cout << endl << "CHOSEN STUDENT'S INFO: " << endl;
	cout << "	STUDENT " << curStdMng->pStudent->id << " - " << curStdMng->pStudent->lastName << " " << curStdMng->pStudent->firstName << endl;
	cout << "	Midterm: " << curStdMng->pCourseManager->scoreBoard.midTerm << " | Final: " << curStdMng->pCourseManager->scoreBoard.finalTerm
		<< " | Lab: " << curStdMng->pCourseManager->scoreBoard.lab << " | Bonus: " << curStdMng->pCourseManager->scoreBoard.bonus << endl;
	cout << "		What part do you want to edit? " << endl;
	cout << "			1.Midterm" << endl;
	cout << "			2.Final" << endl;
	cout << "			3.Lab" << endl;
	cout << "			4.Bonus" << endl;
	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "			Your choice (0 to return): ";
		cin >> yourChoice;
		switch (yourChoice)
		{
		case 0:
			return;
		case 1:
			cin.ignore();
			cout << "New midterm grade: ";
			cin >> curStdMng->pCourseManager->scoreBoard.midTerm;
			cout << "Update successfully " << endl;
			break;
		case 2:
			cin.ignore();
			cout << "New final grade: ";
			cin >> curStdMng->pCourseManager->scoreBoard.finalTerm;
			cout << "Update successfully " << endl;
			break;
		case 3:
			cin.ignore();
			cout << "New lab grade: ";
			cin >> curStdMng->pCourseManager->scoreBoard.lab;
			cout << "Update successfully " << endl;
			break;
		case 4:
			cin.ignore();
			cout << "New bonus grade: ";
			cin >> curStdMng->pCourseManager->scoreBoard.bonus;
			cout << "Update successfully " << endl;
			break;
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
						cout << "Import course " << courseID << " of semester " << semesterName << " of year " << yearName << " successfully!" << endl;
					}
					else
					{
						curSem->numOfCourses--;
					}
				}
			}
		}
		fin.close();
	}
}
void inputCourseDetail (string inYear, string inSemester, Course* &newCourse, CoreData data)
{
	cout << "Please input your course details:" << endl;
	cout << "	Course name: ";
	getline(cin, newCourse->name);
	cout << "	Account of the lecturer: ";
	getline(cin, newCourse->lectureAccount);
	cout << "	Start date: ";
	getline(cin, newCourse->startDate);
	cout << "	End date: ";
	getline(cin, newCourse->endDate);
	cout << "	Day of the week: ";
	getline(cin, newCourse->dayOfWeek);
	cout << "	Start hour: ";
	getline(cin, newCourse->startHour);
	cout << "	End hour: ";
	getline(cin, newCourse->endHour);
	cout << "	Room: ";
	getline(cin, newCourse->room);

	cout << newCourse->startHour << " " << newCourse->endHour << endl;

	string tmpClassName;
	Class* tmpClass = NULL;
	cout << "	Class: ";
	getline(cin, tmpClassName);
	toUpper(tmpClassName);
	

	while (!findClass(tmpClassName, data, tmpClass))
	{
		cout << "	Class " << tmpClassName << " does not exist! Try again." << endl;
		cout << "	Class: ";
		getline(cin, tmpClassName);
		toUpper(tmpClassName);
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

void exportScoreboard(Course* curCourse)
{
	ofstream fout(curCourse->id + "-Scoreboard.csv");
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
	cout << "Export successfully" << endl;
}

//MENUS
void menuCourse(string pathName, CoreData& data)
{
	bool showOption = true;
	while (1)
	{
		clearScreen();
		if (showOption) 
		{
			cout << "__________________MENU__________________" << endl << endl;

			cout << "0. Exit" << endl;
			cout << endl;

			cout << "________ACADEMIC YEARS________" << endl;
			cout << "1. Create an academic year" << endl;
			cout << "2. Update an academic year" << endl;
			cout << "3. Delete an academic year" << endl;
			cout << "4. View an academic year" << endl;
			cout << endl;

			cout << "________SEMESTERS________" << endl;
			cout << "5. Create a semester for an academic year" << endl;
			cout << "6. Update a semester for an academic year (REMOVED)" << endl;
			cout << "7. Delete a semester for an academic year" << endl;
			cout << "8. View a semester for an academic year" << endl;
			cout << endl;

			cout << "________COURSES________" << endl;
			cout << "9. Import a course from a .csv file" << endl;
			cout << "10. Add a course manually" << endl;
			cout << "11. Edit an existing course" << endl;
			cout << "12. Remove a course" << endl;
			cout << "13. Remove a specific student from a course" << endl;
			cout << "14. Add a specific student to a course" << endl;
			cout << "15. View list of courses in the current semester" << endl;
			cout << "16. View list of students of a course" << endl;
			cout << endl;

			cout << "17. View academic years, semesters, courses" << endl;
			cout << endl;

			cout << "________SCOREBOARD________" << endl;
			cout << "18. View scoreboard of a course" << endl;
			cout << "19. Import scoreboard from a .csv file" << endl;
			cout << "20. Export scoreboard to a .csv file" << endl;
			cout << "21. Edit grade of a student" << endl;
			cout << endl;
		}
		else 
		{
			cout << "Invalid choice! Please try again." << endl;
			showOption = true;
		}
	int yourChoice;
	cout << "Your choice (0-22): ";
	cin >> yourChoice;
	cout << endl;
	switch (yourChoice)
	{
	case 0:
		return;
	case 1:
		activity1(pathName, data);
		break;
	case 2:
		activity2(pathName, data);
		break;
	case 3:
		activity3(pathName, data);
		break;
	case 4:
		activity4(data);
		break;
	case 5:
		activity5(pathName, data);
		break;
	/*case 6:
		activity6(pathName, data);
		break;*/
	case 7:
		activity7(pathName, data);
		break;
	case 8:
		activity8(data);
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
		activity13(pathName, data);
		break;
	case 14:
		activity14(pathName, data);
		break; 
	case 15:
		activity15(data);
		break;
	case 16:
		activity16(data);
		break;
	case 17:
		activity17(data);
		break;
	case 18:
		activity18(data);
		break;
	case 19:
		activity19(pathName, data);
		break;
	case 20:
		activity20(data);
		break;
	case 21:
		activity21(pathName, data);
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
void activity1(string pathName, CoreData& data)
{
	cout << "_____________CREATE AN ACADEMIC YEAR_____________" << endl << endl;
	cout << "Year name: ";
	string curYearName;
	cin.ignore();
	getline(cin, curYearName);
	createNewEmptyYear(curYearName, data);
	cout << "Create succesfully!" << endl;
	saveToDataBase(pathName, data);
	returnMenu2Arg(&activity1, pathName, data);
}
void activity2(string pathName, CoreData& data)
{
	cout << "_____________UPDATE AN ACADEMIC YEAR_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		editYear(curYear, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity2, pathName, data);
}
void activity3(string pathName, CoreData& data)
{
	cout << "_____________DELETE AN ACADEMIC YEAR_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		removeYear(curYear, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity3, pathName, data);
}
void activity4(CoreData data)
{
	cout << "_____________VIEW AN ACADEMIC YEAR_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		cout << endl << "	Academic year " << curYear->name << " info: " << endl;
		displayYearInfo(curYear);
	}
	/*bool showOption = true;
	cout << "Input any key to return (1 to run again): ";
	char yourChoice;
	cin >> yourChoice;
	if (yourChoice != 1) return;
	activity4(data);*/
	/*returnMenu1Arg(4)(data);*/
	returnMenu1Arg(&activity4, data);
}
void activity5(string pathName, CoreData& data)
{
	cout << "_____________CREATE A SEMESTER_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	yearMenu(curYear, data);

	if (curYear != NULL)
	{
		cout << endl << "Year " << curYear->name << "'s number of semesters: " << curYear->numOfSems << endl;
		cout << "CREATE HK" << curYear->numOfSems + 1 << "? (0 - NO, 1 - YES) ";
		int yourChoice;
		cin >> yourChoice;
		if (yourChoice == 1)
		{
			cout << endl << "Creating semester HK" << curYear->numOfSems + 1 << " ..." << endl;
			string curSemester;
			curSemester = "HK" + to_string(curYear->numOfSems + 1);
			createNewEmptySemester(curYear->name, curSemester, data);
			cout << endl << "Create successfully!" << endl;
			saveToDataBase(pathName, data);
		}
	}
	returnMenu2Arg(&activity5, pathName, data);
}
/*void activity6(string pathName, CoreData& data)
{
	cout << "_____________UPDATE A SEMESTER_____________" << endl << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);
	if (curSem != NULL)
	{
		editSem(curYear, curSem, data);
		saveToDataBase(pathName, data);
	}

	bool showOption = true;
	while (1)
	{
		if (showOption)
		{
			cout << endl;
			cout << "0. Return" << endl;
			cout << "1. Run this function again." << endl;
		}
		else
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
			activity6(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}*/
void activity7(string pathName, CoreData& data)
{
	cout << "_____________DELETE A SEMESTER_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);
	if (curSem != NULL)
	{
		removeSemDirect(curYear, curSem, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity7, pathName, data);
}
void activity8(CoreData data)
{
	cout << "_____________VIEW A SEMESTER_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);

	if (curSem != NULL)
	{
		cout << endl << "Semester " << curSem->name << " of year " << curYear->name << " info: " << endl;
		displaySemInfo(curSem);
	}

	/*bool showOption = true;

	while (1)
	{
		if (showOption)
		{
			cout << endl;
			cout << "0. Return" << endl;
			cout << "1. Run this function again." << endl;
		}
		else
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
			activity8(data);
			return;
		default:
			showOption = false;
			break;
		}
	}*/
	returnMenu1Arg(&activity8, data);
}
void activity9(string pathName, CoreData& data)
{
	cout << "_____________IMPORT A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);

	if (curSem != NULL)
	{
		cout << "INPUT .CSV FILE NAME: ";
		string fileName;
		cin.ignore();
		getline(cin, fileName);
		importCourse(pathName + fileName, curYear->name, curSem->name, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity9, pathName, data);
}
void activity10(string pathName, CoreData& data)
{
	cout << "_____________ADD A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);

	if (curSem != NULL)
	{
		cout << "Please input the ID of the course you want to create:";
		string curCourseID;
		cin.ignore();
		getline(cin, curCourseID);
		createNewEmptyCourse(curYear->name, curSem->name, curCourseID, data);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity10, pathName, data);
}
void activity11(string pathName, CoreData& data)
{
	cout << "_____________UPDATE A COURSE_____________" << endl << endl;
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
	returnMenu2Arg(&activity11, pathName, data);
}
void activity12(string pathName, CoreData& data)
{
	cout << "_____________REMOVE A COURSE_____________" << endl << endl;
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
	returnMenu2Arg(&activity12, pathName, data);
}
void activity13(string pathName, CoreData& data)
{
	cout << "_____________REMOVE A STUDENT FROM A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		viewListOfStudents(curCourse);
		if (curCourse->pHeadStudentManager != NULL)
		{
			cout << endl << "Please input the ID of the student you want to remove from this course: ";
			long long stdID;
			cin >> stdID;
			removeStudentFromCourse(stdID, curCourse);
			cout << "Remove successfully!" << endl;
			saveToDataBase(pathName, data);
		}
	}
	returnMenu2Arg(&activity13, pathName, data);
}
void activity14(string pathName, CoreData& data)
{
	cout << "_____________ADD A STUDENT TO A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		cout << endl << "List of students attending in course " << curCourse->name << ": " << endl;
		displayStdInCourse(curYear, curSem, curCourse);
		cout << endl << "Please input the ID of the student you want to add to this course: ";
		long long stdID;
		Student* std;
		Class* stdClass;
		cin >> stdID;
		if (findStudent(stdID, data, std, stdClass))
		{
			addStudentToCourse(std, curCourse, curYear->name, curSem->name);
			cout << "Add successfully!" << endl;
			saveToDataBase(pathName, data);
		}
		else
			cout << "There is no student with this ID. " << endl;
	}
	returnMenu2Arg(&activity14, pathName, data);
}
void activity15(CoreData data)
{
	cout << "_____________LIST OF COURSES IN A SEMESTER_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);
	if (curSem != NULL)
	{
		displayCoursesCurSem(curYear, curSem);
	}
	returnMenu1Arg(&activity15, data);
}
void activity16(CoreData data)
{
	cout << "_____________LIST OF STUDENTS IN A COURSE_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		viewListOfStudents(curCourse);
	}
	returnMenu1Arg(&activity16, data);
}
void activity17(CoreData data)
{
	cout << "_____________VIEW ACADEMIC YEARS, SEMESTERS, COURSES_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
		displayCourseInfo(curCourse);
	returnMenu1Arg(&activity17, data);
}
void activity18(CoreData data)
{
	cout << "_____________VIEW SCOREBOARD_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
		displayScoreboard(curCourse);
	returnMenu1Arg(&activity18, data);
}
void activity19(string pathName, CoreData& data)
{
	cout << "_____________IMPORT SCOREBOARD_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		cout << "INPUT .CSV FILE NAME: ";
		string fileName;
		cin.ignore();
		getline(cin, fileName);
		importScoreboard(pathName + "data/" + fileName, curCourse);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity19, pathName, data);
}
void activity20(CoreData data)
{
	cout << "_____________EXPORT SCOREBOARD_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		exportScoreboard(curCourse);
	}
	returnMenu1Arg(&activity20, data);
}
void activity21(string pathName, CoreData& data)
{
	cout << "_____________EDIT GRADE OF A STUDENT_____________" << endl << endl;
	cout << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		displayScoreboard(curCourse);
		cout << endl << "Input the ID of the student you want to edit grade: ";
		long long stdID;
		cin >> stdID;
		StudentManager* curStdMng = NULL;
		while (!findStudentInCourse(stdID,curStdMng,curCourse))
		{
			cout << "There is no student with this ID in this course. Try again." << endl;
			cout << "Input the ID of the student you want to edit grade: ";
			cin >> stdID;
		}
		editGrade(curCourse, curStdMng);
		saveToDataBase(pathName, data);
	}
	returnMenu2Arg(&activity21, pathName, data);
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
