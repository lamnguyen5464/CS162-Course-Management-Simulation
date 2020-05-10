#include <fstream>
#include <iostream>
#include <string>
#include "Data.hpp"
#include "Course.h"

//DISPLAYS
void displayYearInfo(Year* curYear)
{
	Year* tmpYear = curYear;
	cout << "Name: " << tmpYear->name << endl;
	cout << "Number of semesters: " << tmpYear->numOfSems << endl;
	cout << "Semesters' details: " << endl;
	Semester* tmpSem = tmpYear->pHeadSemesters;
	while (tmpSem != NULL) 
	{
		cout << tmpSem->name << endl;
		tmpSem = tmpSem->next;
	}
}
void displaySemInfo(Semester* curSem)
{
	Semester* tmpSem = curSem;
	cout << "Name: " << tmpSem->name << endl;
	cout << "Number of courses: " << tmpSem->numOfCourses << endl;
	cout << "Courses' details: " << endl;
	Course* tmpCourse = tmpSem->pHeadCourse;
	while (tmpCourse != NULL) {
		cout << tmpCourse->name << endl;
		tmpCourse = tmpCourse->next;
	}
}
void displayCourseInfo(Course* curCourse)
{
	cout << "Course ID: " << curCourse->id << endl;
	cout << "Course name: " << curCourse->name << endl;
	cout << "Lecturer Account: " << curCourse->lectureAccount << endl;
	cout << "Start date: " << curCourse->startDate << endl;
	cout << "End date: " << curCourse->endDate << endl;
	cout << "Day of week: " << curCourse->dayOfWeek << endl;
	cout << "Room: " << curCourse->room << endl;
}
void displayCoursesCurSem(Year* curYear, Semester* curSem)
{
	cout << endl << "Courses of " << curSem->name << " of " << curYear->name << ": " << endl;
	Course* tmpCourse = curSem->pHeadCourse;
	for (int i = 1; tmpCourse != NULL; ++i)
	{
		cout << i << ". " << tmpCourse->name << endl;
		tmpCourse = tmpCourse->next;
	}
}
void displayStdInCourse(Year* curYear, Semester* curSemester, Course* curCourse)
{
	cout << endl;
	cout << "Year: " << curYear->name << endl;
	cout << "    Semester: " << curSemester->name << endl;
	cout << "        Course: " << curCourse->name << endl;

	StudentManager* cur = curCourse->pHeadStudentManager;
	int i = 1;
	while (cur != NULL)
	{
		cout << "            " << i++ << ". " << cur->pStudent->lastName << " " << cur->pStudent->firstName << " " << cur->pStudent->id << endl;
		cur = cur->next;
	}
}

//EDITS
void editYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "This is the information of the academic year you want to edit: " << endl;
	displayYearInfo(curYear);
	cout << endl << "Do you want to edit this academic year? (0 - NO, 1 - YES)" << endl;
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
			cout << "Then you will be brought back." << endl;
			return;
		case 1:
		{
			//Input again all the info
			cout << endl << "Please input again all the information of that academic year: " << endl;
			cin.ignore();
			cout << "Name: ";
			string prevYearName = curYear->name;
			getline(cin, curYear->name);
			cout << "Number of semesters: ";
			int tmpNumOfSems = curYear->numOfSems;
			cin >> curYear->numOfSems;

			//Edit the year of students in that academic year
			if (curYear->name != prevYearName && curYear->pHeadSemesters != NULL)
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

			//If the number of semesters changes, update accordingly
			if (curYear->numOfSems > tmpNumOfSems)
			{
				cin.ignore();
				for (int i = 1; i <= curYear->numOfSems - tmpNumOfSems; ++i)
				{
					cout << "Please input the name of the semester you want to create:";
					string semesterName;
					getline(cin, semesterName);
					Semester* tmpSem = NULL;
					if (findSemester(curYear->name, semesterName, tmpSem, data))
					{
						i--;
						cout << "This semester has already existed. Please input again." << endl;
					}
					else
					{
						createNewEmptySemester(curYear->name, semesterName, data);
						curYear->numOfSems--; //redundant addition of numOfSems in createNewEmptySemester function
					}
				}
			}
			else if (curYear->numOfSems < tmpNumOfSems)
			{
				//remove semesters
				/*for (int j = curYear->numOfSems; j <= tmpNumOfSems; ++j)
				{
					Semester* curSem = NULL;
					semesterMenu(curYear, curSem, data);
					if (curSem != NULL)
					{
						removeSemDirect(curYear, curSem, data);
					}
				}*/
			}

			cout << endl << "Your updated academic year: " << endl;
			displayYearInfo(curYear);
			return;
		}
		default:
			showOption = false;
			break;
		}
	}
}
void editSem(Year*& curYear, Semester*& curSem, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "This is the information of the semester you want to edit: " << endl;
	displaySemInfo(curSem);
	cout << endl << "Do you want to edit this semester? (0 - NO, 1 - YES)" << endl;
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
			cout << "Then you will be brought back." << endl;
			return;
		case 1:
		{
			//Input again all the info
			cout << endl << "Please input again all the information of that semester: " << endl;
			cin.ignore();
			cout << "Name: ";
			string prevSemName = curSem->name;
			getline(cin, curSem->name);
			cout << "Number of courses: ";
			int tmpNumOfCourses = curSem->numOfCourses;
			cin >> curSem->numOfCourses;

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

			//If the number of courses changes, update accordingly
			if (curSem->numOfCourses > tmpNumOfCourses)
			{
				for (int i = 1; i <= curSem->numOfCourses - tmpNumOfCourses; ++i)
				{
					cin.ignore();
					for (int i = 1; i <= curSem->numOfCourses - tmpNumOfCourses; ++i)
					{
						cout << "Please input the ID of the course you want to create:";
						string courseID;
						getline(cin, courseID);
						Course* tmpCourse = NULL;
						if (findCourse(courseID, curSem, tmpCourse, data))
						{
							i--;
							cout << "This course has already existed. Please input again." << endl;
						}
						else
						{
							createNewEmptyCourse(curYear->name, curSem->name, courseID, data);
							curSem->numOfCourses--; //redundant addition of numOfCourses in createNewEmptyCourses function
						}
					}
				}
			}
			else if (curSem->numOfCourses < tmpNumOfCourses)
			{
				//remove courses
				/*for (int j = curSem->numOfCourses; j <= tmpNumOfCourses; ++j)
				{
					Course* curCourse = NULL;
					courseMenu(curYear, curSem, curCourse, data);
					if (curCourse != NULL)
					{
						removeCourse(curSem, curCourse);
					}
				}*/
			}

			cout << endl << "Your updated semester: " << endl;
			displaySemInfo(curSem);
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
	cout << endl << "This is the information of the course you want to edit: " << endl;
	displayCourseInfo(curCourse);
	cout << endl << "Do you want to edit this course? (0 - NO, 1 - YES)" << endl;
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
			cout << "Then you will be brought back." << endl;
			return;
		case 1:
		{
			//Input again all the info
			cout << endl << "Please input again all the information of that course: " << endl;
			string courseID;
			cin.ignore();
			cout << "Course ID: ";
			getline(cin, courseID);

			//Check if new ID exist
			if (findSemester(curYear->name, curSem->name, curSem, data))
			{
				Course* newCourse;
				if (findCourse(curYear->name, curSem->name, courseID, newCourse, data))
				{
					cout << "The course " << courseID << " of semester " << curSem->name << " of year " << curYear->name << " is already existing!" << endl;
					return;
				}
			}

			curCourse->id = courseID;
			inputCourseDetail(curYear->name, curSem->name, curCourse, data);
			//Check link with the class????

			cout << endl << "Your updated semester: " << endl;
			displaySemInfo(curSem);
			return;
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
		if (findCourse(yearName, semesterName, courseID, newCourse, data)) {
			cout << "The course " << courseID << " of semester " << semesterName << " of year " << yearName << " is already existing!" << endl;
			return;
		}
		curSem->numOfCourses++;
		newCourse = new Course;
		newCourse->id = courseID;
		inputCourseDetail(yearName, semesterName, newCourse, data);
		newCourse->pHeadStudentManager = NULL;
		newCourse->next = curSem->pHeadCourse;
		curSem->pHeadCourse = newCourse;
	}
	else {
		//ask to create a new year
	}
}
void removeYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before editing
	cout << endl << "This is the information of the academic year you want to delete: " << endl;
	displayYearInfo(curYear);
	cout << endl << "Do you want to delete this academic year? (0 - NO, 1 - YES)" << endl;
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
			cout << "Then you will be brought back." << endl;
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

			cout << "Deleted." << endl;
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
	cout << endl << "This is the information of the semester you want to delete: " << endl;
	displaySemInfo(curSem);
	cout << endl << "Do you want to delete this semester? (0 - NO, 1 - YES)" << endl;
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
			cout << "Then you will be brought back." << endl;
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

			cout << endl << "Updated academic year " << curYear->name << ": " << endl;
			displayYearInfo(curYear);
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

//INPUT
void importCourse(ifstream& fin, string inYear, string inSemester, Course*& newCourse, CoreData& data)
{
	getline(fin, newCourse->name, ',');
	string tmpClassName;
	Class* tmpClass = NULL;
	getline(fin, tmpClassName,',');
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
	getline(fin, newCourse->lectureAccount, ',');
	getline(fin, newCourse->startDate, ',');
	getline(fin, newCourse->endDate, ',');
	getline(fin, newCourse->dayOfWeek, ',');
	getline(fin, newCourse->startHour, ',');
	getline(fin, newCourse->startHour, ',');
	getline(fin, newCourse->room, '\n');
}
void importCourse(string address, string yearName, string semesterName, CoreData& data)
{
	ifstream fin;
	fin.open(address);
	if (!fin.is_open()) 
	{
		cout << "No such file can be found. Please try again." << endl;
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
			Semester* curSem;
			if (findSemester(yearName, semesterName, curSem, data)) {
				Course* newCourse;
				if (findCourse(yearName, semesterName, courseID, newCourse, data)) {
					cout << "The course " << courseID << " of semester " << semesterName << " of year " << yearName << " is already existing!" << endl;
					return;
				}
				curSem->numOfCourses++;
				newCourse = new Course;
				newCourse->id = courseID;
				importCourse(fin, yearName, semesterName, newCourse, data);
				newCourse->pHeadStudentManager = NULL;
				newCourse->next = curSem->pHeadCourse;
				curSem->pHeadCourse = newCourse;
			}
			else {
				//ask to create a new year
			}
		}
	}
}
void inputCourseDetail (string inYear, string inSemester, Course* &newCourse, CoreData data)
{
	cout << "Please input your course details:" << endl;
	cout << "Course name: ";
	getline(cin, newCourse->name);
	string tmpClassName;
	Class* tmpClass = NULL;
	cout << "Class: ";
	getline(cin, tmpClassName);
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
	cout << "Account of the lecturer: ";
	getline(cin, newCourse->lectureAccount);
	cout << "Start date: ";
	getline(cin, newCourse->startDate);
	cout << "End date: ";
	getline(cin, newCourse->endDate);
	cout << "Day of the week: ";
	getline(cin, newCourse->dayOfWeek);
	cout << "Start hour: ";
	getline(cin, newCourse->startHour);
	cout << "End hour: ";
	getline(cin, newCourse->startHour);
	cout << "Room: ";
	getline(cin, newCourse->room);
}

//MENUS
void menuCourse(string pathName, CoreData& data)
{
	cout << string(100, '\n'); //thay bang clear screen
	bool showOption = true;
	while (1)
	{
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
			cout << "6. Update a semester for an academic year" << endl;
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
			cout << "17. View attendance list of a course" << endl;
			cout << endl;

			cout << "________LECTURERS________" << endl;
			cout << "18. Create a new lecturer" << endl;
			cout << "19. Update a lecturer" << endl;
			cout << "20. Delete a lecturer" << endl;
			cout << "21. View all lecturers" << endl;
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
	case 6:
		activity6(pathName, data);
		break;
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
	default:
		showOption = false;
		break;
	}
	}
}
void yearMenu(Year*& curYear, CoreData data)
{
	cout << endl << "Please input 1, 2, 3, 4, ... corresponding to your selection below: " << endl;
	cout << "Year: " << endl;
	Year* tmpYear = data.pHeadYear;
	for (int i = 1; tmpYear != NULL; ++i)
	{
		cout << "    " << i << ". " << tmpYear->name << endl;
		tmpYear = tmpYear->next;
	}

	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice (INPUT 0 TO GO BACK): ";
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
	cout << endl << "        Semester: " << endl;
	Semester* tmpSem = curYear->pHeadSemesters;
	for (int i = 1; tmpSem != NULL; ++i)
	{
		cout << "            " << i << ". " << tmpSem->name << endl;
		tmpSem = tmpSem->next;
	}

	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice (INPUT 0 TO GO BACK): ";
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
	cout << endl << "                    Course: " << endl;
	Course* tmpCourse = curSem->pHeadCourse;
	for (int i = 1; tmpCourse != NULL; ++i)
	{
		cout << "                        " << i << ". " << tmpCourse->name << endl;
		tmpCourse = tmpCourse->next;
	}

	bool showOption = true;
	while (1)
	{
		if (!showOption)
		{
			cout << "Invalid choice. Try again." << endl;
			showOption = true;
		}
		int yourChoice;
		cout << "Your choice (INPUT 0 TO GO BACK): ";
		cin >> yourChoice;

		if (yourChoice > 0 && yourChoice <= curYear->numOfSems)
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
	cout << "Please input the name of the academic year you want to create: ";
	string curYearName;
	cin.ignore();
	getline(cin, curYearName);
	createNewEmptyYear(curYearName, data);
	saveToDataBase(pathName, data);

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
			activity1(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity2(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		editYear(curYear, data);
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
			activity2(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity3(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		removeYear(curYear, data);
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
			activity3(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity4(CoreData data)
{
	Year* curYear = NULL;
	yearMenu(curYear, data);
	if (curYear != NULL)
	{
		cout << endl << "Academic year " << curYear->name << " info: " << endl;
		displayYearInfo(curYear);
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
			activity4(data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity5(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	yearMenu(curYear, data);

	if (curYear != NULL)
	{
		cout << "Please input the name of the semester you want to create:";
		string curSemester;
		cin.ignore();
		getline(cin, curSemester);
		createNewEmptySemester(curYear->name, curSemester, data);
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
			activity5(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity6(string pathName, CoreData& data)
{
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
}
void activity7(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);
	if (curSem != NULL)
	{
		removeSemDirect(curYear, curSem, data);
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
			activity7(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity8(CoreData data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);

	if (curSem != NULL)
	{
		cout << endl << "Semester " << curSem->name << " of year " << curYear->name << " info: " << endl;
		displaySemInfo(curSem);
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
			activity8(data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity9(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);

	if (curSem != NULL)
	{
		cout << "Please input the location of the .csv file of the course you want to input: ";
		string address;
		cin.ignore();
		getline(cin, address);
		importCourse(address, curYear->name, curSem->name, data);
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
			activity9(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity10(string pathName, CoreData& data)
{
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
			activity10(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity11(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		editCourse(curYear, curSem, curCourse, data);
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
			activity11(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity12(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		removeCourse(curSem, curCourse);
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
			activity12(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity13(string pathName, CoreData& data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);

	if (curCourse != NULL)
	{
		cout << endl << "List of students attending in course " << curCourse->name << ": " << endl;
		displayStdInCourse(curYear, curSem, curCourse);
		cout << endl << "Please input the ID of the student you want to remove from this course: ";
		long long stdID;
		cin >> stdID;
		removeStudentFromCourse(stdID, curCourse);
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
			activity13(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity14(string pathName, CoreData& data)
{
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
			cout << endl << "Your updated list of students in course " << curCourse->name << ": " << endl;
			displayStdInCourse(curYear, curSem, curCourse);
			saveToDataBase(pathName, data);
		}
		else
			cout << "There is no student with this ID. " << endl;
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
			activity14(pathName, data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity15(CoreData data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	semesterMenu(curYear, curSem, data);
	if (curSem != NULL)
	{
		displayCoursesCurSem(curYear, curSem);
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
			activity15(data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}
void activity16(CoreData data)
{
	Year* curYear = NULL;
	Semester* curSem = NULL;
	Course* curCourse = NULL;
	courseMenu(curYear, curSem, curCourse, data);
	if (curCourse != NULL)
	{
		displayStdInCourse(curYear, curSem, curCourse);
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
			activity16(data);
			return;
		default:
			showOption = false;
			break;
		}
	}
}