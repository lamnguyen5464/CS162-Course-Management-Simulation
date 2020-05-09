#include <fstream>
#include <string>
#include "Data.hpp"
#include "Course.h"

const string pathName = "D:/Uni/CS162/project/Project";

void displayAllYears(CoreData data)
{
	for (int i = 1; i <= data.numOfYears; ++i)
	{
		cout << i << ". " << data.pHeadYear->name << endl;
		data.pHeadYear = data.pHeadYear->next;
	}
}

void displayAllSemesters(CoreData data)
{
	for (int i = 1; i <= data.numOfYears; ++i)
	{
		cout << (char)(i + 64) << ". " << data.pHeadYear->name << endl;
		for (int j = 1; j <= data.pHeadYear->numOfSems; ++j)
		{
			cout << j << ". " << data.pHeadYear->pHeadSemesters->name << endl;
			data.pHeadYear->pHeadSemesters = data.pHeadYear->pHeadSemesters->next;
		}
		data.pHeadYear = data.pHeadYear->next;
	}
}

void displayAllCourses(CoreData data)
{
	for (int i = 1; i <= data.numOfYears; ++i)
	{
		cout << (char)(i + 64) << ". " << data.pHeadYear->name << endl;
		for (int j = 1; j <= data.pHeadYear->numOfSems; ++j)
		{
			cout << j << ". " << data.pHeadYear->pHeadSemesters->name << endl;
			for (int k = 1; k <= data.pHeadYear->pHeadSemesters->numOfCourses; ++k)
			{
				cout << k << ". " << data.pHeadYear->pHeadSemesters->pHeadCourse->name << endl;
				data.pHeadYear->pHeadSemesters->pHeadCourse = data.pHeadYear->pHeadSemesters->pHeadCourse->next;
			}
			data.pHeadYear->pHeadSemesters = data.pHeadYear->pHeadSemesters->next;
		}
		data.pHeadYear = data.pHeadYear->next;
	}
}

void displayYearInfo(Year* curYear, CoreData data)
{
	cout << "Name: " << curYear->name << endl;
	cout << "Number of semesters: " << curYear->numOfSems << endl;
	cout << "Semesters' details: " << endl;
	while (curYear->pHeadSemesters != NULL) {
		cout << curYear->pHeadSemesters->name << endl;
		curYear->pHeadSemesters = curYear->pHeadSemesters->next;
	}
}

void displaySemInfo(Semester* curSem, CoreData data)
{
	cout << "Name: " << curSem->name << endl;
	cout << "Number of courses: " << curSem->numOfCourses << endl;
	cout << "Courses' details: " << endl;
	while (curSem->pHeadCourse != NULL) {
		cout << curSem->pHeadCourse->name << endl;
		curSem->pHeadCourse = curSem->pHeadCourse->next;
	}
}

void displayCourseInfo(Course* curCourse, CoreData data)
{
	cout << "Course ID: " << curCourse->id << endl;
	cout << "Course name: " << curCourse->name << endl;
	cout << "Lecturer Account: " << curCourse->lectureAccount << endl;
	cout << "Start date: " << curCourse->startDate << endl;
	cout << "End date: " << curCourse->endDate << endl;
	cout << "Day of week: " << curCourse->dayOfWeek << endl;
	cout << "Room: " << curCourse->room << endl;
}

void editYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before editing
	cout << "This is the information of the academic year you want to edit: ";
	displayYearInfo(curYear, data);
	//cout << "Do you want to edit? (0 - NO, 1 - YES): ";

	//Input again all the info
	cout << endl << "Please input again all the information of that academic year: ";
	cout << "Name: ";
	getline(cin, curYear->name);
	cout << "Number of semesters: ";
	int tmpNumOfSems = curYear->numOfSems;
	cin >> curYear->numOfSems;

	//If the number of semesters changes, update accordingly
	if (curYear->numOfSems > tmpNumOfSems)
	{
		for (int i = 1; i <= curYear->numOfSems - tmpNumOfSems; ++i)
		{
			cout << "New semester name: ";
			string semName;
			getline(cin, semName);
			createNewEmptySemester(curYear->name, semName, data);
			cout << endl;
		}
	}
	else if (curYear->numOfSems < tmpNumOfSems)
	{
		//delete Semester
	}

	cout << "Your updated academic year: " << endl;
	displayYearInfo(curYear, data);
}

void deleteYear(Year*& curYear, CoreData& data)
{
	//Display the info one time before deleting
	cout << "This is the information of the academic year you want to delete: ";
	displayYearInfo(curYear, data);
	//cout << "Do you want to edit? (0 - NO, 1 - YES): ";


}

void editSem(Semester*& curSem, CoreData& data)
{
	//Display the info one time before editing
	cout << "This is the information of the semester you want to edit: ";
	displaySemInfo(curSem, data);
	//cout << "Do you want to edit? (0 - NO, 1 - YES): ";

	//Input again all the info
	cout << endl << "Please input again all the information of that semester: ";
	cout << "Name: ";
	getline(cin, curSem->name);
	cout << "Number of courses: ";
	int tmpNumOfCourses = curSem->numOfCourses;
	cin >> curSem->numOfCourses;

	//If the number of semesters changes, update accordingly
	if (curSem->numOfCourses > tmpNumOfCourses)
	{
		for (int i = 1; i <= curSem->numOfCourses - tmpNumOfCourses; ++i)
		{
			Course* newCourse = new Course;
			inputCourseDetail(newCourse);
			addNewCourse(curYear, curSem->name, newCourse, data);
			cout << endl;
		}
	}
	else if (curSem->numOfCourses < tmpNumOfCourses)
	{
		//delete Semester
	}

	cout << "Your updated semester: " << endl;
	displaySemInfo(curSem, data);
}

void importCourse(string address, CoreData& data)
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

	}
}

void inputCourseDetail (Course* &newCourse)
{
	cin.ignore();
	cout << "Please input your course details:" << endl;
	cout << "Course id: ";
	getline(cin, newCourse->id);
	cout << "Course name: ";
	getline(cin, newCourse->name);
	cout << "Account of the lecturer: ";
	getline(cin, newCourse->lectureAccount);
	cout << "Start date: ";
	getline(cin, newCourse->startDate);
	cout << "End date: ";
	getline(cin, newCourse->endDate);
	cout << "Day of the week: ";
	getline(cin, newCourse->dayOfWeek);
	cout << "Start date: ";
	getline(cin, newCourse->startDate);
	cout << "Room: ";
	getline(cin, newCourse->room);
}

void editCourse(Course*& curCourse, CoreData& data)
{
	//Display the info one time before editing
	cout << "This is the information of the course you want to edit: ";
	displayCourseInfo(curCourse, data);
	//cout << "Do you want to edit? (0 - NO, 1 - YES): ";

	//Input again all the info
	inputCourseDetail(curCourse);

	cout << "Your updated course: " << endl;
	displayCourseInfo(curCourse, data);
}

void removeStdFromCourse(Course*& curCourse, CoreData& data)
{
	cout << "Please input the id of the student you want to remove from this course: ";
	long long tmpID;
	cin >> tmpID;
	Student* tmpStd;

	if (findStudentInCourse(tmpID, tmpStd, curCourse))
	{
		CourseManager* cur1 = tmpStd->pHeadCourseManager;
		CourseManager* prev1 = NULL;
		while (cur1 != NULL)
		{
			if (cur1->pCourse == curCourse)
			{
				if (prev1 != NULL)
				{
					prev1->next = cur1->next;
				}
				else //class at head
				{
					tmpStd->pHeadCourseManager = cur1->next;
				}
				break;
			}
			prev1 = cur1;
			cur1 = cur1->next;
		}

		StudentManager* cur2 = curCourse->pHeadStudentManager;
		StudentManager* prev2 = NULL;
		while (cur2 != NULL)
		{
			if (cur2->pStudent->id == tmpID)
			{
				if (prev2 != NULL)
				{
					prev2->next = cur2->next;
				}
				else //std at head
				{
					curCourse->pHeadStudentManager = cur2->next;
				}
				break;
			}
			prev2 = cur2;
			cur2 = cur2->next;
		}
	}

}

void displayCoursesCurSem(Semester* curSem, CoreData data)
{
	for (int i = 1; i <= curSem->numOfCourses; ++i)
	{
		cout << i << ". " << curSem->name << endl;
		curSem = curSem->next;
	}
}

void displayStdInCourse(Course* curCourse, CoreData data)
{
	StudentManager* cur = curCourse->pHeadStudentManager;
	int i = 1;
	while (cur != NULL)
	{
		cout << i++ << ". " << cur->pStudent->id << " - " << cur->pStudent->lastName << " " << cur->pStudent->firstName << endl;
		cur = cur->next;
	}
}

void menuCourse(CoreData& data) 
{
	cout << string(100, '\n');
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
	{
		return;
	}
	case 1:
	{
		cout << "Please input the name of the academic year you want to create: ";
		string curYearName;
		cin.ignore();
		getline(cin, curYearName);
		createNewEmptyYear(curYearName, data);
		//saveToDataBase(pathName, data);
		break;
	}
	case 2:
	{
		//Display the list of years to choose -> get name from that choice 
		string curYearName;
		Year* curYear;
		getline(cin, curYearName);
		if (findYear(curYearName, curYear, data)) 
		{
			editYear(curYear, data);
		}
		else cout << "This year does not exist. Please try again." << endl;
		break;
	}
	case 3:
	{
		string curYearName;
		Year* curYear;
		getline(cin, curYearName);
		if (findYear(curYearName, curYear, data)) 
		{
			deleteYear(curYear, data);
		}
		else cout << "This year does not exist. Please try again." << endl;
		break;
	}
	case 4:
	{
		string curYearName;
		Year* curYear;
		getline(cin, curYearName);
		if (findYear(curYearName, curYear, data))
		{
			displayYearInfo(curYear, data);
		}
		else cout << "This year does not exist. Please try again." << endl;
		break;
	}
	case 5:
	{
		/*cout << "Which year do you want to create a new semester in?" << endl;
		Year* curYear;

		//pick the year -> pick year name from that choice*/

		string curYear;
		getline(cin, curYear);

		cout << "Please input the name of the semester you want to create:";
		string curSemester;
		getline(cin, curSemester);
		createNewEmptySemester(curYear, curSemester, data);
		break;
	}
	case 6:
	{
		//Display the list of years with semesters to choose
		string curYearName;
		getline(cin, curYearName);

		string curSemName;
		getline(cin, curSemName);
		Semester* curSem;
		if (findSemester(curYearName, curSemName, curSem, data))
		{
			editSem(curSem, data);
		}
		else cout << "This semester does not exist. Please try again." << endl;
		break;
	}
	case 9:
	{
		cout << "Please input the location of the .csv file of the course you want to input: ";
		string address;
		cin.ignore();
		getline(cin, address);
		importCourse(address, data);
		break;
	}
	case 10:
	{
		/*cout << "List of semesters: " << endl;
		displayAllSemesters(data);
		int yourChoice;
		cout << "Please input the number of the semester you want to choose: ";
		cin >> yourChoice;*/
		string curYear;
		getline(cin, curYear);

		string curSem;
		getline(cin, curSem);
	
		Course* newCourse = new Course;
		inputCourseDetail(newCourse);
		addNewCourse(curYear, curSem, newCourse, data);
		break;
	}
	case 11:
	{
		/*cout << "List of courses: " << endl;
		displayAllCourses(data);
		int yourChoice;
		cout << "Please input the number of the semester you want to choose: ";
		cin >> yourChoice;*/

		string curYear;
		getline(cin, curYear);

		string curSem;
		getline(cin, curSem);

		string curCourseID;
		getline(cin, curCourseID);

		Course* curCourse;

		if (findCourse(curYear, curSem, curCourseID,curCourse, data))
		{
			editCourse(curCourse, data);
		}
		else cout << "This course does not exist. Please try again." << endl;
		break;
	}
	case 12:
	{
		/*cout << "List of courses: " << endl;
		displayAllCourses(data);
		int yourChoice;
		cout << "Please input the number of the semester you want to choose: ";
		cin >> yourChoice;

		string curYear;
		getline(cin, curYear);

		string curSem;
		getline(cin, curSem);

		string curCourseID;
		getline(cin, curCourseID);

		Course* curCourse;

		if (findCourse(curYear, curSem, curCourseID, curCourse, data))
		{
			deleteCourse(curCourse, data);
		}
		else cout << "This course does not exist. Please try again." << endl;
		break;*/
	}
	case 13:
	{
		/*cout << "List of courses: " << endl;
		displayAllCourses(data);
		int yourChoice;
		cout << "Please input the number of the semester you want to choose: ";
		cin >> yourChoice;*/

		string curYear;
		getline(cin, curYear);

		string curSem;
		getline(cin, curSem);

		string curCourseID;
		getline(cin, curCourseID);

		Course* curCourse;

		if (findCourse(curYear, curSem, curCourseID, curCourse, data))
		{
			removeStdFromCourse(curCourse, data);
		}
		else cout << "This course does not exist. Please try again." << endl;
		break;
	}
	case 14:
	{
		/*cout << "List of courses: " << endl;
		displayAllCourses(data);
		int yourChoice;
		cout << "Please input the number of the semester you want to choose: ";
		cin >> yourChoice;*/

		string curYear;
		getline(cin, curYear);

		string curSem;
		getline(cin, curSem);

		string curCourseID;
		getline(cin, curCourseID);

		Course* curCourse;

		if (findCourse(curYear, curSem, curCourseID, curCourse, data))
		{
			cout << "Please input the id of the student you want to add to this course: ";
			long long tmpID;
			cin >> tmpID;
			Student* tmpStd;
			Class* ofClass;

			if (findStudent(tmpID, data, tmpStd, ofClass))
			{
				addStudentToCourse(tmpStd, curCourse, curYear, curSem);
			}
		}
		else cout << "This course does not exist. Please try again." << endl;
		break; 
	}
	case 15:
	{
		/*cout << "List of semesters: " << endl;
		displayAllSemesters(data);
		int yourChoice;
		cout << "Please input the number of the semester you want to choose: ";
		cin >> yourChoice;*/
		
		string curYear;
		getline(cin, curYear);

		string curSemName;
		getline(cin, curSemName);
		
		Semester* curSem;
		if (findSemester(curYear, curSemName, curSem, data))
		{
			displayCoursesCurSem(curSem, data);
		}
		else
		{
			cout << "This semester does not exist" << endl;
		}
		break;
	}
	case 16:
	{
		/*cout << "List of courses: " << endl;
		displayAllCourses(data);
		int yourChoice;
		cout << "Please input the number of the semester you want to choose: ";
		cin >> yourChoice;*/

		string curYear;
		getline(cin, curYear);

		string curSem;
		getline(cin, curSem);

		string curCourseID;
		getline(cin, curCourseID);

		Course* curCourse;

		if (findCourse(curYear, curSem, curCourseID, curCourse, data))
		{
			displayStdInCourse(curCourse, data);
		}
		else cout << "This course does not exist. Please try again." << endl;
		break;
	}
	default:
	{
		showOption = false;
		break;
	}
	}
	}
}