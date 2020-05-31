
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include "Data.hpp"
using namespace std;
ifstream fin;
char ch[1000];
void importDataBase(string pathName, CoreData &data){
    //scan Academic.txt
    fin.open(pathName + "Academic.txt");
    if (!fin.is_open()){
        ofstream fout;
        fout.open(pathName+"Academic.txt");
        data.numOfYears = 0;                //neu ma ko co Academic.txt thi ko co du lieu year->=0
        fout.close();
    }else{
        fin>>data.numOfYears;
        fin.ignore(256,'\n');
        for(int i=1; i <= data.numOfYears; i++){
            Year *newYear = new Year;
            getline(fin,newYear->name);
            newYear->pHeadSemesters = NULL;
            fin>>newYear->numOfSems;
            fin.ignore(256,'\n');
            for(int j=0; j<newYear->numOfSems; j++){
                Semester *newSem = new Semester;
                newSem->pHeadCourse = NULL;
                getline(fin, newSem->name);
                fin>>newSem->numOfCourses;
                fin.ignore(256,'\n');
                for(int k=0; k<newSem->numOfCourses; k++){
                    Course *newC = new Course;
                    getline(fin, newC->id);
                    getline(fin, newC->name);
                    getline(fin, newC->lectureAccount);
                    getline(fin, newC->startDate);
                    getline(fin, newC->endDate);
                    getline(fin, newC->startHour);
                    getline(fin, newC->endHour);
                    getline(fin, newC->dayOfWeek);
                    getline(fin, newC->room);
                    addNewCourse(newSem, newC);
                }
                newSem->next = newYear->pHeadSemesters;
                newYear->pHeadSemesters = newSem;
            }
            newYear->next = data.pHeadYear;
            data.pHeadYear = newYear;
        }
    }
    fin.close();
    //scan Students.txt
    fin.open(pathName + "Students.txt");
    if (!fin.is_open()){
        ofstream fout;
        fout.open(pathName+"Students.txt");
        data.numOfClasses = 0;
        fout.close();
    }else{               
        fin>>data.numOfClasses;
        fin.ignore(256,'\n');
        for(int i=1; i <= data.numOfClasses; i++){
            Class *tmpClass = new Class;
            tmpClass->next = NULL;
            tmpClass->pHeadStudent = NULL;
            getline(fin, tmpClass->name);
            parseString(tmpClass->name);
            fin>>tmpClass->numOfStudents;     
            for(int j=1; j<=tmpClass->numOfStudents; j++){
                Student *tmpSt = new Student;
                fin>>tmpSt->id;
                fin.ignore(256,'\n');
                getline(fin, tmpSt->lastName); 
                getline(fin, tmpSt->firstName);
                getline(fin, tmpSt->gender);
                getline(fin, tmpSt->dOB); 
                fin>>tmpSt->hashPassword;
                int numOfCourse;
                fin>>numOfCourse;
                fin.ignore(256,'\n');
                //link Course of semester of year here;
                for(int k=1; k<=numOfCourse; k++){            
                    string courseId, year, semester;
                    //read info
                    getline(fin, year);
                    getline(fin, semester);
                    getline(fin, courseId);
                    //read score
                    Course *tmpCourse;
                    if (findCourse(year, semester, courseId, tmpCourse, data)){ //must true
                        linkStudentToCourse(tmpSt, tmpCourse, year, semester);
                    }
                    //read score
                    fin>>tmpSt->pHeadCourseManager->scoreBoard.midTerm
                    >>tmpSt->pHeadCourseManager->scoreBoard.finalTerm
                    >>tmpSt->pHeadCourseManager->scoreBoard.lab
                    >>tmpSt->pHeadCourseManager->scoreBoard.bonus;
                    //read check-in
                    int numOfDays;
                    fin>>numOfDays;                     // cout<<numOfDays<<" "<<tmpSt->id<<endl;
                    for(int i=0; i<numOfDays; i++){        //
                        CheckInCell *tmpCell = new CheckInCell;
                        fin>>tmpCell->checked>>tmpCell->startTime>>tmpCell->endTime; 
                        addCheckInCell(tmpSt->pHeadCourseManager->checkIn, tmpCell);
                    }
                    
                    fin.ignore(256,'\n');
                    
                }
                
                if (tmpClass->pHeadStudent==NULL){
                    tmpClass->pHeadStudent = tmpClass->pTailStudent = tmpSt;
                }else{
                    tmpClass->pTailStudent->next = tmpSt;
                    tmpClass->pTailStudent = tmpSt;
                }
            }
            tmpClass->next = data.pHeadClass;
            data.pHeadClass = tmpClass;
        }
        
    }
    fin.close();
    
    //scan Staff.txt
    fin.open(pathName + "Staff.txt");
    if (!fin.is_open()){
        ofstream fout;
        fout.open(pathName+"Staff.txt");
        data.numOfLecturers = 0;
        data.numOfStaffs = 0;
        addStaff(hashPass("123"), "admin", data);
        fout.close();
    }else{
        int numOfStaffs, numOfLecturers;
        fin>>numOfStaffs>>numOfLecturers;
        fin.ignore(256,'\n');
        for(int i = 0; i < numOfStaffs; i++){
            long long tmpHash;
            string tmpName;
            getline(fin, tmpName);
            fin>>tmpHash;
            addStaff(tmpHash, tmpName, data);
            fin.ignore(256, '\n');
        }
        for(int i = 0; i < numOfLecturers; i++){
            long long tmpHash;
            string tmpName;
            getline(fin, tmpName);
            fin>>tmpHash;
            addLecturer(tmpHash, tmpName, data);           
            fin.ignore(256, '\n');
        }
    }
    fin.close();
}
void saveToDataBase(string pathName, CoreData data){
    ofstream fout;
    //save Student info
    fout.open(pathName + "Students.txt");
    fout<<data.numOfClasses<<endl;
    Class *curClass = data.pHeadClass;
    while (data.numOfClasses--){
        fout<<curClass->name<<endl;
        parseString(curClass->name);
        fout<<curClass->numOfStudents<<endl;
        Student *curSt = curClass->pHeadStudent;
        while (curSt !=NULL ){                          // cout<<curClass->name<<" "<<curSt->id<<endl;
            fout<<curSt->id<<endl;
            fout<<curSt->lastName<<endl;
            fout<<curSt->firstName<<endl;
            fout<<curSt->gender<<endl;
            fout<<curSt->dOB<<endl;
            fout<<curSt->hashPassword<<endl;
            fout<<curSt->numOfCourse<<endl;
            
            CourseManager *curCourse = curSt->pHeadCourseManager;
            while (curCourse != NULL){
                //info
                fout<<curCourse->year<<endl<<curCourse->semester<<endl<<curCourse->pCourse->id<<endl;
                //score
                fout<<curCourse->scoreBoard.midTerm<<" "<<curCourse->scoreBoard.finalTerm<<" "<<curCourse->scoreBoard.lab<<" "<<curCourse->scoreBoard.bonus<<endl;
                //check int
                fout<<curCourse->checkIn.numOfDays<<endl;
                CheckInCell *curCell = curCourse->checkIn.pHeadCell;
                while (curCell != NULL){
                    fout<<curCell->checked<<" "<<curCell->startTime<<" "<<curCell->endTime<<endl;
                    curCell = curCell->next;
                }
                
                //...
                //
                curCourse = curCourse->next;
            }
            
            curSt = curSt->next;
        }
        curClass = curClass->next;
    }
    fout.close();
    //save Course info
    fout.open(pathName + "Academic.txt");
    fout<<data.numOfYears<<endl;
    Year *curYear = data.pHeadYear;
    while (curYear != NULL){
        fout<<curYear->name<<endl;
        fout<<curYear->numOfSems<<endl;
        Semester *curSem = curYear->pHeadSemesters;
        while (curSem != NULL){
            fout<<curSem->name<<endl;
            fout<<curSem->numOfCourses<<endl;
            Course *curCourse = curSem->pHeadCourse;
            while (curCourse != NULL){
                fout<<curCourse->id<<endl;
                fout<<curCourse->name<<endl;
                fout<<curCourse->lectureAccount<<endl;
                fout<<curCourse->startDate<<endl;
                fout<<curCourse->endDate<<endl;
                fout<<curCourse->startHour<<endl;
                fout<<curCourse->endHour<<endl;
                fout<<curCourse->dayOfWeek<<endl;
                fout<<curCourse->room<<endl;
                curCourse = curCourse->next;
            }
            curSem = curSem->next;
        }
        curYear = curYear->next;
    }
    fout.close();
    
    fout.open(pathName+"Staff.txt");
    fout<<data.numOfStaffs<<" "<<data.numOfLecturers<<endl;
    Staff *curStaff = data.pHeadStaff;
    while (curStaff != NULL){
        fout<<curStaff->userName<<endl<<curStaff->hashPassword<<endl;
        curStaff = curStaff->next;
    }
    Lecturer *curLec = data.pHeadLecturer;
    while (curLec != NULL){
        fout<<curLec->userName<<endl<<curLec->hashPassword<<endl;
        curLec = curLec->next;
    }
    fout.close();
}
bool findStudent(long long id, CoreData data, Student *&st, Class *&ofClass){
    Class *curClass = data.pHeadClass;
    while (curClass != NULL){
        //check if class is empty
        if (curClass->pHeadStudent == NULL || id < curClass->pHeadStudent->id || curClass->pTailStudent->id < id){
            curClass = curClass->next;
        }else{
            Student *curStudent = curClass->pHeadStudent;
            while (curStudent != NULL &&curStudent->id < id)
                curStudent = curStudent->next;
            if (curStudent != NULL && curStudent->id == id){
                st = curStudent;
                ofClass = curClass;
                return true;
            }
            curClass = curClass->next;
        }
    }
    return false;
}
bool findClass(string className, CoreData data, Class *&foundClass){
    Class *curClass = data.pHeadClass;
    while (curClass != NULL){
        if (curClass->name == className){
            foundClass = curClass;
            return true;
        }
        curClass = curClass->next;
    }
    return false;
}
bool removeStudent(long long id, CoreData &data){
    Class *curClass = data.pHeadClass;
    while (curClass != NULL){
        //check if class is empty
        if (curClass->pHeadStudent == NULL || id < curClass->pHeadStudent->id || curClass->pTailStudent->id < id){
            curClass = curClass->next;
        }else{
            Student *curStudent = curClass->pHeadStudent, *preStudent = NULL;
            while (curStudent != NULL &&curStudent->id < id){
                preStudent = curStudent;
                curStudent = curStudent->next;
            }
            if (curStudent != NULL && curStudent->id == id){        //found!!
                curClass->numOfStudents--;
                if (preStudent == NULL){        //remove at phead
                    preStudent = curClass->pHeadStudent;
                    curClass->pHeadStudent = curClass->pHeadStudent->next; 
                }else{
                    if (curStudent->next==NULL) curClass->pTailStudent = preStudent; //remove at ptail
                    preStudent->next = curStudent->next;
                }
                //remove in course
                CourseManager *courseManager = curStudent->pHeadCourseManager;
                while (courseManager != NULL){
                    removeStudentFromCourse(curStudent->id, courseManager->pCourse);
                    courseManager = courseManager->next;
                }
                deallocateStudent(curStudent);
                return true;
                //
            }
            curClass = curClass->next;
        }
    }
    return false;
}
bool removeStudent(long long id, CoreData &data, Student *&removedStudent){
    Class *curClass = data.pHeadClass;
    while (curClass != NULL){
        //check if class is empty
        if (curClass->pHeadStudent == NULL || id < curClass->pHeadStudent->id || curClass->pTailStudent->id < id){
            curClass = curClass->next;
        }else{
            Student *curStudent = curClass->pHeadStudent, *preStudent = NULL;
            while (curStudent != NULL &&curStudent->id < id){
                preStudent = curStudent;
                curStudent = curStudent->next;
            }
            if (curStudent != NULL && curStudent->id == id){        //found!!
                curClass->numOfStudents--;
                if (preStudent == NULL){        //remove at phead
                    preStudent = curClass->pHeadStudent;
                    curClass->pHeadStudent = curClass->pHeadStudent->next;
                }else{
                    if (curStudent->next==NULL) curClass->pTailStudent = preStudent; //remove at ptail
                    preStudent->next = curStudent->next;
                }
                //remove in course
                removedStudent = curStudent;
                return true;
                //
            }
            curClass = curClass->next;
        }
    }
    return false;
}
void deallocateStudent(Student *&st){
//    while (st->numOfCourse--){
//        //deallocate *year
//    }
//    delete st;
}
void addStudentToClass(Class *&pClass, Student *& tmpSt){
//    tmpSt->hashPassword = hashPass(to_string(tmpSt->id));
//    cout<<"Add "<<tmpSt->lastName<<" "<<tmpSt->firstName<<" to class "<<pClass->name<<" successfully!"<<endl;
    if (pClass->pHeadStudent==NULL){    //CLASS IS EMPTY
        pClass->pHeadStudent = pClass->pTailStudent = tmpSt;
        return;
    }
    if (pClass->pHeadStudent->id > tmpSt->id){  //push front
        tmpSt->next = pClass->pHeadStudent;
        pClass->pHeadStudent = tmpSt;
        return;
    }
    if (pClass->pTailStudent->id < tmpSt->id){  //push back
        pClass->pTailStudent->next = tmpSt;
        pClass->pTailStudent = tmpSt;
        return;
    }
    Student *cur = pClass->pHeadStudent;
    while (cur != NULL && cur->next !=NULL && cur->next->id < tmpSt->id){
        cur = cur->next;
    }                          
    tmpSt->next = cur->next;
    cur->next = tmpSt;
    
    
}
void createNewEmptyClass(string className, CoreData &data){
    Class *newClass = new Class;
    newClass->name = className;
    newClass->numOfStudents = 0;
    newClass->pHeadStudent = newClass->pTailStudent = NULL;
    newClass->next = data.pHeadClass;
    data.pHeadClass = newClass;
    data.numOfClasses++;
}
void addStudentToClass(string className, Student *&st, CoreData &data){
    Class *curClass = data.pHeadClass;
    while (curClass != NULL){
        if (curClass->name == className){
            curClass->numOfStudents++;
            addStudentToClass(curClass, st);
            return;
        }
        curClass = curClass->next;
    }
    //not found
    cout<<"Not found this class"<<endl;
    cout<<"1. Create a new class and add this student"<<endl;
    cout<<"2. Return"<<endl;
    int choice;
    cout<<"Your choice is: "; cin>>choice;
    switch (choice) {
        case 1:
            createNewEmptyClass(className, data);
            addStudentToClass(className, st, data);
            break;
            
        default:
            break;
    }
}

void parseString(string &s){
    while (s.length() && s[0]==' ') s.erase(0,1);
    while (s.length() && s[s.length()-1]==' ') s.erase(s.length()-1,1);
}
long long hashPass(string s){
    long long MOD = 1e9+7;
    int base = 31;
    long long res = 0;
    for(int i=0; i<s.length(); i++)
        res = (res*base + s[i])%MOD;
    return res;
}

bool findYear(string yearName, Year *&foundYear, CoreData data){
    Year *tmp = data.pHeadYear;
    while (tmp != NULL){
        if (tmp->name == yearName){
            foundYear = tmp;
            return true;
        }
        tmp = tmp->next;
    }
    //not found this year;
    //cout<<"The year "<<yearName<<" is not existing!"<<endl;
    return false;
}
bool createNewEmptyYear(string yearName, CoreData &data){
    Year *newYear;
    if (findYear(yearName, newYear, data)){
        cout<<"The year "<<yearName<<" is already existing!"<<endl;
        return 0;
    }
    data.numOfYears++;
    newYear = new Year;
    newYear->name = yearName;
    newYear->numOfSems = 0;
    newYear->pHeadSemesters = NULL;
    newYear->next = data.pHeadYear;
    data.pHeadYear = newYear;
    return 1;
}
bool findSemester(string yearName, string semesterName, Semester *&foundSemester, CoreData data){
    Year *curYear;
    if (findYear(yearName, curYear, data)){
        Semester *curSem = curYear->pHeadSemesters;
        while (curSem != NULL){
            if (curSem->name == semesterName){
                foundSemester = curSem;
                return true;
            }
            curSem = curSem->next;
        }
        //not found this semester
        //cout<<"The semester "<<semesterName<<" is not existing!"<<endl;
        return false;
    }else{
        //this year is not existing
        return false;
    }
    
}
bool createNewEmptySemester(string yearName, string semesterName, CoreData &data){
    Year *curYear;
    if (findYear(yearName, curYear, data)){
        Semester *newSemester;
        if (findSemester(yearName, semesterName, newSemester, data)){
            cout<<"The semester "<<semesterName<<" of year "<< yearName<<" is already existing!"<<endl;
            return 0;
        }
        curYear->numOfSems++;
        newSemester = new Semester;
        newSemester->name = semesterName;
        newSemester->numOfCourses = 0;
        newSemester->pHeadCourse = NULL;
        newSemester->next = curYear->pHeadSemesters;
        curYear->pHeadSemesters = newSemester;
    }
    return 1;
    
}
bool findCourse(string yearName, string semesterName, string courseID, Course *&foundCourse, CoreData data){
    Semester *curSemester;
    if (findSemester(yearName, semesterName, curSemester, data)){
        Course *curCourse;
        if (findCourse(courseID, curSemester, curCourse, data)){
            foundCourse = curCourse;
            return true;
        }
    }
    return false;
}
bool findCourse(string courseID, Semester *curSemester, Course *&foundCourse, CoreData data){
    Course *curCourse = curSemester->pHeadCourse;
    while (curCourse != NULL){
        if (curCourse->id == courseID){
            foundCourse = curCourse;
            return true;
        }
        curCourse = curCourse->next;
    } 
    //not found
//    cout<<"The Course "<<courseID<<" could not be found in this semester of this year"<<endl;
    return false;
}

void addNewCourse(string inYear, string inSemester, Course *&newCourse, CoreData &data){
    Semester *curSem;
    if (findSemester(inYear, inSemester, curSem, data)){
        curSem->numOfCourses++;
        newCourse->next = curSem->pHeadCourse;
        newCourse->pre = NULL;
        if (curSem->pHeadCourse!=NULL) curSem->pHeadCourse->pre = newCourse;
        curSem->pHeadCourse = newCourse;
        cout<<"Add course successfully"<<endl;
    }
}
void addNewCourse(Semester *curSem, Course *&newCourse){ 
    newCourse->next = curSem->pHeadCourse;
    newCourse->pre = NULL;
    if (curSem->pHeadCourse!=NULL) curSem->pHeadCourse->pre = newCourse;
    curSem->pHeadCourse = newCourse; 
}

void addStudentToCourse(Student *&curStudent, Course *&curCourse, string inYear, string inSemester){ 
    CourseManager *courseManager = new CourseManager;
    courseManager->pCourse = curCourse;
    courseManager->year = inYear;
    courseManager->semester = inSemester;
    courseManager->next = curStudent->pHeadCourseManager;
    courseManager->pre = NULL;
    if (curStudent->pHeadCourseManager!=NULL) curStudent->pHeadCourseManager->pre = courseManager;
    curStudent->pHeadCourseManager = courseManager;
    curStudent->numOfCourse++;
    
    //add CheckInBoard; 
    if (courseManager->checkIn.numOfDays == 0){
        CheckInBoard curCheckIn;
        createCheckInBoard(curCourse->startDate, curCourse->endDate, curCourse->startHour, curCourse->endHour, getDayFromString(curCourse->dayOfWeek), curCheckIn);
        courseManager->checkIn = curCheckIn;
    }
    StudentManager *studentManager = new StudentManager;
    studentManager->pStudent = curStudent;
    studentManager->next = curCourse->pHeadStudentManager;
    studentManager->pre = NULL;
    if (curCourse->pHeadStudentManager!=NULL) curCourse->pHeadStudentManager->pre = studentManager;
    curCourse->pHeadStudentManager = studentManager;
    
    studentManager->pCourseManager = courseManager;
    courseManager->pStudentManager = studentManager;
    
}
void linkStudentToCourse(Student *&curStudent, Course *&curCourse, string inYear, string inSemester){
    CourseManager *courseManager = new CourseManager;
    courseManager->pCourse = curCourse;
    courseManager->year = inYear;
    courseManager->semester = inSemester;
    courseManager->next = curStudent->pHeadCourseManager;
    courseManager->pre = NULL;
    if (curStudent->pHeadCourseManager!=NULL) curStudent->pHeadCourseManager->pre = courseManager;
    curStudent->pHeadCourseManager = courseManager;
    curStudent->numOfCourse++;
        
    StudentManager *studentManager = new StudentManager;
    studentManager->pStudent = curStudent;
    studentManager->next = curCourse->pHeadStudentManager;
    studentManager->pre = NULL;
    if (curCourse->pHeadStudentManager!=NULL) curCourse->pHeadStudentManager->pre = studentManager;
    curCourse->pHeadStudentManager = studentManager;
    
    studentManager->pCourseManager = courseManager;
    courseManager->pStudentManager = studentManager;
    
}

bool findStudentInCourse(long long stId, StudentManager *&foundStudentManager, Course *curCourse){
    StudentManager *cur = curCourse->pHeadStudentManager;
    while (cur != NULL){
        if (cur->pStudent->id == stId){
            foundStudentManager = cur;
            return true;
        }
        cur = cur->next;
    }
    return false;
}
void removeCourseManager(StudentManager *curStudentManager){
    Student *curSt = curStudentManager->pStudent;
    CourseManager *curCourseManager = curStudentManager->pCourseManager;
    curSt->numOfCourse--;
    
    //remove course from student
    if (curCourseManager->pre == NULL){
        curSt->pHeadCourseManager = curCourseManager->next;
    }else{
        curCourseManager->pre->next = curCourseManager->next;
    }
    if (curCourseManager->next != NULL) curCourseManager->next->pre = curCourseManager->pre;
    
    deallocateCourseManager(curCourseManager);
    deallocateStudentManager(curStudentManager);
}
void removeCourse(Semester *curSem ,Course *curCourse){
    curSem->numOfCourses--;
    if (curCourse->pre == NULL){
        curSem->pHeadCourse = curCourse->next;
    }else{
        curCourse->pre->next = curCourse->next;
    }
    if (curCourse->next !=NULL) curCourse->next->pre = curCourse->pre;
    StudentManager *curStudentManager = curCourse->pHeadStudentManager;
    while (curStudentManager != NULL){
        removeCourseManager(curStudentManager);
        
        StudentManager *tmp = curStudentManager->next;
        curStudentManager = tmp;
    }
}
void deallocateCourse(Course *curCourse){
    
}
void deallocateCourseManager(CourseManager *curCourseManager){
    
}
void deallocateStudentManager(StudentManager *curStudentManager){
    
}
bool removeCourse(string yearName, string semesterName, string courseID, CoreData &data){
    Course *curCourse;
    Semester *curSem;
    if (findSemester(yearName, semesterName, curSem, data)){
        if (findCourse(courseID, curSem, curCourse, data)){
            removeCourse(curSem, curCourse);
            return true;
        }
    }
    
    return 0; // could not find the course
}
bool removeStudentFromCourse(long long stID, Course *curCourse){
    StudentManager *curStudentManager;
    if (findStudentInCourse(stID, curStudentManager, curCourse)){
        removeCourseManager(curStudentManager);
        //remove Student manager 
        if (curStudentManager->pre == NULL){
            curCourse->pHeadStudentManager = curStudentManager->next;
        }else{
            curStudentManager->pre->next = curStudentManager->next;
        }
        if (curStudentManager->next != NULL) curStudentManager->next->pre = curStudentManager->pre;
        deallocateStudentManager(curStudentManager);
        return true;
    }
    return false;
}
void showDataStudent(CoreData data){
    cout<<"Number of class: "<<data.numOfClasses<<endl;
    Class *curClass = data.pHeadClass;
    while ((curClass != NULL)){
        cout<<"     Class "<<curClass->name<<" - "<<curClass->numOfStudents<<" student(s):"<<endl;
        Student *curSt = curClass->pHeadStudent; 
        while (curSt != NULL){
            cout<<"         Id: "<<curSt->id<<endl;
            cout<<"         Name: "<<curSt->firstName<<" "<<curSt->lastName<<endl;
            cout<<"         DOB: "<<curSt->dOB<<" "<<endl;
            cout<<"         NumOfCourses: "<<curSt->numOfCourse<<endl;
            CourseManager *curCourse = curSt->pHeadCourseManager;
            while (curCourse != NULL){
                cout<<"             "<<curCourse->pCourse->name<<endl;
                curCourse = curCourse->next;
            }
            curSt = curSt->next;
            cout<<endl;
        }
        curClass = curClass->next;
        cout<<endl;
    }
}
void showCourse(CoreData data){
    Year *curYear = data.pHeadYear;
    while (curYear != NULL){
        cout<<"Year: "<<curYear->name<<endl;
        Semester *curSem = curYear->pHeadSemesters;
        while (curSem != NULL){
            cout<<"     "<<curSem->name<<": "<<endl;
            Course *curCourse = curSem->pHeadCourse;
            while (curCourse != NULL){
                cout<<"         "<<curCourse->name<<endl;
                StudentManager *curSt = curCourse->pHeadStudentManager;
                while (curSt != NULL){
                    cout<<"             "<<curSt->pStudent->firstName<<" "<<curSt->pStudent->lastName<<" "<<curSt->pStudent->id<<endl;
                    curSt = curSt->next;
                }
                curCourse = curCourse->next;
            }
            curSem = curSem->next;
        }
        curYear = curYear->next;
    }
}
//Time
int getDaysOfMonth(int month, int year){
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year%4==0 && year%100!=0) || year%400==0) days[1] = 29;
    return days[month-1];
}
long long TimeInfo::toInt(string s){
    long long tmp;
    stringstream(s)>>tmp;
    return tmp;
}
bool TimeInfo::setDate(string s){
    int cntFlash = 0, tmpDate = -1, tmpMonth = -1, tmpYear = -1;
    string tmp = "";
    for(int i=0; i<s.length(); i++){
        if (s[i] == '/'){
            if (tmp != ""){
                if (tmpDate == -1){
                    tmpDate = (int)toInt(tmp);
                }else if (tmpMonth == -1){
                    tmpMonth = (int)toInt(tmp);
                }
                tmp = "";
            }
            cntFlash++;
            continue;
        }
        if ('0'<=s[i] && s[i]<='9'){
            tmp += s[i];
            continue;
        }
        return false;
    }                      
    tmpYear = (int)toInt(tmp);
    if (cntFlash==2 && 0<tmpMonth && tmpMonth<=12 && 0<tmpDate && tmpDate<=getDaysOfMonth(tmpMonth, tmpYear)){
        date = tmpDate;
        month = tmpMonth;
        year = tmpYear;
        return true;
    }else
        return false;
}
bool TimeInfo::setTime(string s){
    int cntColon = 0, tmpHour = -1, tmpMinute = -1;
    string tmp = "";
    for(int i=0; i<s.length(); i++){
        if (s[i] == ':'){
            tmpHour = (int)toInt(tmp);
            tmp = "";
            cntColon++;
            continue;
        }
        if ('0'<=s[i] && s[i]<='9'){
            tmp += s[i];
            continue;
        }
        return false;
    }
    tmpMinute = (int)toInt(tmp);
    if (cntColon==1 && 0<=tmpHour && tmpHour<24 && 0<=tmpMinute && tmpMinute<60){
        hour = tmpHour;
        minnute = tmpMinute; 
        return true;
    }
    return false;
}
//YYYYmmDDhhMMss -> long long
long long TimeInfo::getTimeCode(){
    long long tmp =(((((long long)year*100 + (long long)month)*100 + (long long)date)*100 + (long long)hour)*100 + (long long)minnute);
    return tmp;
}
void TimeInfo::constructor(long long code){
    minnute = code % 100;
    code /= 100;
    hour = code % 100;
    code /= 100;
    date = code % 100;
    code /= 100;
    month = code % 100;
    code /= 100;
    year = (int)code;
}
int getDayOfWeek(int date, int month, int year){
    int deltaMonth[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year/4 - year/100 + year/400 + deltaMonth[month-1] + date) % 7;
}
int getDayFromString(string s){
    for(int i=0; i<s.length(); i++)
        s[i] = toupper(s[i]);
    if (s == "SUN") return 0;
    if (s == "MON") return 1;
    if (s == "TUE") return 2;
    if (s == "WED") return 3;
    if (s == "THU") return 4;
    if (s == "FRI") return 5;
    if (s == "SAT") return 6;
    return -1;
} 
string getStringDayFromInt(int index){
    if (index > 6) return "";
    string day[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return day[index];
}
int getMonthFromString(string s){
    for(int i=0; i<s.length(); i++)
        s[i] = toupper(s[i]);
    if (s == "JAN") return 1;
    if (s == "FEB") return 2;
    if (s == "MAR") return 3;
    if (s == "APR") return 4;
    if (s == "MAY") return 5;
    if (s == "JUN") return 6;
    if (s == "JUL") return 7;
    if (s == "AUG") return 8;
    if (s == "SEP") return 9;
    if (s == "OCT") return 10;
    if (s == "NOV") return 11;
    if (s == "DEC") return 12;
    return -1;
}

TimeInfo nextDayOf(TimeInfo curDay){
    TimeInfo tmp = curDay;
    tmp.date++;
    if (tmp.date > getDaysOfMonth(tmp.month, tmp.year)){
        tmp.date = 1;
        tmp.month++;
        if (tmp.month > 12){
            tmp.month = 1;
            tmp.year++;
        }
    }
    return tmp;
}

TimeInfo getFirstDay(TimeInfo startDate, int dayOfWeek){
    while (getDayOfWeek(startDate.date, startDate.month, startDate.year) != dayOfWeek){
        startDate = nextDayOf(startDate);
    }
    return startDate;
}
void addCheckInCell(CheckInBoard &checkIn, CheckInCell *tmpCell){
    checkIn.numOfDays++;
    if (checkIn.pHeadCell == NULL){
        checkIn.pHeadCell = checkIn.pTailCell = tmpCell;
    }else{
        checkIn.pTailCell->next = tmpCell;
        checkIn.pTailCell = tmpCell;
    }
}
void createCheckInBoard(string startDate, string endDate, string startHour, string endHour, int dayOfWeek, CheckInBoard &checkIn){
    TimeInfo date, finalDate;
    finalDate.setDate(endDate);
    finalDate.setTime(endHour);
    date.setDate(startDate);
    date.setTime(startHour);
    date = getFirstDay(date, dayOfWeek);
//    cout<<startDate<<" "<<endDate<<" "<<startHour<<" "<<endHour<<endl;
    while (date.getTimeCode() <= finalDate.getTimeCode()){
        CheckInCell *tmpCell = new CheckInCell;
        tmpCell->startTime = date.getTimeCode();
        date.setTime(endHour);
        tmpCell->endTime = date.getTimeCode();
        date.setTime(startHour);        //rollback
        tmpCell->checked = false;
        addCheckInCell(checkIn, tmpCell); 
        for(int i=0; i<7; i++) date = nextDayOf(date);          //shift a week
    }
    
} 
TimeInfo getCurrentTime(){
    TimeInfo curTime;
    time_t my_time = time(NULL);
    string s = ctime(&my_time);
    string day, month, date, time, year;
    stringstream(s)>>day>>month>>date>>time>>year;
    curTime.setDate(date+"/"+to_string(getMonthFromString(month))+"/"+year);
    string shortTime = "";
    for(int i=0; i<5; i++) shortTime += time[i];
    curTime.setTime(shortTime); 
    return curTime;
}
void addStaff(long long hash, string userName, CoreData &data){
    data.numOfStaffs++;
    Staff *tmp = new Staff;
    tmp->userName = userName;
    tmp->hashPassword = hash;
    tmp->next = data.pHeadStaff;
    data.pHeadStaff = tmp;
}

void addLecturer(long long hash, string userName, CoreData &data){
    data.numOfLecturers++;
    Lecturer *tmp = new Lecturer;
    tmp->userName = userName;
    tmp->hashPassword = hash;
    tmp->next = data.pHeadLecturer;
    data.pHeadLecturer = tmp;
}
bool findLecturer(string nameLec, CoreData data, Lecturer *&foundLecturer){
    Lecturer *curLec = data.pHeadLecturer;
    while (curLec != NULL){
        if (curLec->userName == nameLec){
            foundLecturer = curLec;
            return true;
        }
        curLec = curLec->next;
    }
    return false;
}
bool findStaff(string nameStaff, CoreData data, Staff *&foundStaff){
    Staff *curStaff = data.pHeadStaff;
    while (curStaff != NULL){
        if (curStaff->userName == nameStaff){
            foundStaff = curStaff;
            return true;
        }
        curStaff = curStaff->next;
    }
    return false;
}
