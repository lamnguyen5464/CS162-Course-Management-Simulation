#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Data.hpp"
#include "class.h"
using namespace std;

void clearScreen(){
    system("cls");
}

void upper(string &name){
    for (int i = 0;i < name.length();i++)
        if (name[i] >= 'a' && name[i] <='z')
        name[i] = name[i] - 32;
}
void staffClassMenu (string pathname,CoreData &data){
    bool showOption = true;
    while (1){
        if (showOption){
            cout << "__________________STAFF-CLASS__________________" << endl;
            cout << "1.Import students of a class from the csv file." << endl;
            cout << "2.Manually add a student to a class." << endl;
            cout << "3.Edit an existing student" << endl;
            cout << "4.Remove a student" << endl;
            cout << "5.Change a student from class A to class B." << endl;
            cout << "6.View list of classes and list of students in a class." << endl;
            cout << "0.Return to previous menu." << endl;
        }
        else{
            cout << "Invalid choice!Try again!"<< endl;
            showOption = true;
        }
        int yourChoice;
        cout << ">Your choice: ";
        cin >> yourChoice;
        switch (yourChoice){
            case 0:
                return;
            case 1:
                activity1(pathname,data);
                break;
            case 2:
                activity2(pathname,data);
                break;
            case 3:
                activity3(pathname,data);
                break;
            case 4:
                activity4(pathname,data);
                break;
            case 5:
                 activity5(pathname,data);
                 break;
            case 6:{
                activity6(pathname,data);
                break;
            }
            default:
                showOption = false;
                break;
        }
    }
}

void inputStudentFromFile(Student *tmpSt,Class *&tmpClass,ifstream &fin,CoreData &data){
    string headers;
    string no;
    getline(fin,headers,'\n'); //ignore headers
    while(!fin.eof()){
        getline(fin, no, ','); //ignore no
        tmpSt = new Student;
        fin.ignore(1);
        fin >> tmpSt->id;
        fin.ignore(1);
        getline(fin,tmpSt->lastName,',');
        getline(fin,tmpSt->firstName,',');
        getline(fin,tmpSt->gender,',');
        getline(fin,tmpSt->dOB,'\n');
        tmpSt->hashPassword = hashPass(to_string(tmpSt->id));
        addStudentToClass(tmpClass->name,tmpSt,data);
    }
}

void importStudentFromCsvFile (CoreData &data){
    ifstream fin;
    string linkOfFile;
    cout << "Csv file: ";
    cin.ignore();
    getline(cin, linkOfFile);
    fin.open(linkOfFile);
    if (!fin.is_open()){
        cout << "can not open file"<<endl;
    }
    else{
        string classname = linkOfFile;

       // t chua biet xu li ten lop sao
        createNewEmptyClass(classname,data);
        Class *tmpClass = NULL;
        if (!findClass(classname,data,tmpClass)) return;
        Student *tmpSt = NULL ;
        inputStudentFromFile(tmpSt,tmpClass,fin,data);
        fin.close();
    }
}

void creatClassToImport(CoreData &data){
    bool k = true;
    string classname;
    while(1){
        if (!k) cout << "Invalid choice. Try again.";
        int choice;
        cout << "Do you want to create a new class(0.No)&(1.Yes): ";
        cin >> choice;
        switch(choice){
            case 1:{
                cout << "Class's name: ";
                cin.ignore();
                getline(cin,classname);
                createNewEmptyClass(classname,data);
                return;
            }
            case 0:
                return;
            default:
                k = false;
                break;
        }
    }
}

void edit(Student *&tmpSt,int choice,bool &checkChoice){
    switch(choice){
        case 1:{
            cout << "   New last name: ";
            string tmpLast;
            cin.ignore();
            getline(cin,tmpLast);
            tmpSt ->lastName = tmpLast;
            cout << "   Edit successfully!"<<endl;
            break;
        }
        case 2:{
            cout << "   New first name: ";
            string tmpFirst;
            cin.ignore();
            getline(cin,tmpFirst);
            tmpSt ->firstName = tmpFirst;
            cout << "   Edit successfully!"<<endl;
            break;
        }
        case 3:{
            cout << "   New doB: ";
            string tmpdob;
            cin.ignore();
            getline(cin,tmpdob);
            tmpSt ->dOB = tmpdob;
            cout << "   Edit successfully!"<<endl;
            break;
        }
        case 4:{
            cout << "    New gender: "<<endl;
            inputGender(tmpSt->gender);
            cout << "    Edit successfully!"<<endl;
            break;
        }
        default:
            checkChoice = false;
            break;
    }
}
bool editAnExistingStudent(CoreData &data){
    bool checkChoice = true;
    long long ID;
    cout << "Please input id of the student you want to edit: ";
    cin >> ID;
    Student *tmpSt=NULL;
    Class *tmpClass=NULL;
    int choice;
    if (findStudent(ID,data,tmpSt,tmpClass)){
        cout << "What part do you want to edit? "<<endl;
        cout << "1.ID: " << tmpSt->id << endl;
        cout << "2.Last name: " << tmpSt->lastName<< endl;
        cout << "3.First name: " << tmpSt->firstName << endl;
        cout << "4.DoB: " << tmpSt->dOB << endl;
        cout << "5.Gender: " << tmpSt->id << endl;
        cout << "Your choice (0 to return): ";
        cin >> choice;
        if (choice == 0) return false;
        edit(tmpSt,choice,checkChoice);
    }
    else{
        cout << "Can not find student"<<endl;
        cout << "1.Input another student."<<endl;
        cout << "2.Return" << endl;
        cout << ">Your choice: ";
        cin >> choice;
        switch(choice){
            case 2:
                return false;
            default:
                break;
        }
    }
    if (checkChoice == false) cout << "Invalid choice. Try again."<<endl;
    return true;
}

bool editByMenu (CoreData &data){
    Student *curSt = NULL;
    Class *curClass = NULL;
    bool checkChoice = true;
    int choice;
    if (!menuStudent(curClass,curSt,data)) return false;
    cout << endl;
    cout << "What part do you want to edit? "<<endl;
    cout << "1.Last name: " << curSt->lastName<< endl;
    cout << "2.First name: " << curSt->firstName << endl;
    cout << "3.DoB: " << curSt->dOB << endl;
    cout << "4.Gender: " << curSt->id << endl;
    cout << ">Your choice (0 to return): ";
    cin >> choice;
    if (choice == 0) return false;
    edit(curSt,choice,checkChoice);
    if (checkChoice == false) cout << "Invalid choice. Try again."<<endl;
    return true;
}

void menuClass(Class *&curClass,CoreData data){
    bool checkChoice = true;
    while(1){
        if (checkChoice == false) cout << "Invalid choice. Try again. "<<endl;
        if (data.numOfClasses == 0) {
            cout << "There is no class"<<endl;
            return;
        }
        curClass = data.pHeadClass;
        int a = 1,choice;
        cout << "Choose class: "<<endl;
        while (curClass != NULL){
            cout<<"        "<< a <<". " << "Class " << curClass ->name << ": " << curClass ->numOfStudents << " students." <<endl;
            curClass = curClass ->next;
            a++;
        }
        cout <<"        " << "Choose class: (0 to return): ";
        cin >> choice;
        if (choice == 0) return;
        else if (choice <= data.numOfClasses){
            curClass = data.pHeadClass;
            int i = 1;
            while (i < choice){
                curClass = curClass -> next;
                ++i;
            }
            return;
        }
        else checkChoice = false;
    }
}

bool viewListOfStudents(Class *curClass,CoreData data){
    menuClass(curClass,data);
    if (curClass == NULL) return false;
    Student *tmpSt = curClass ->pHeadStudent;
    if (tmpSt == NULL){
        cout << "       There is no student in this class"<<endl;
        return true;
    }
    else{
        int last = 10,first = 10,dob = 0;
        findMaxLength(tmpSt,last,first,dob);
        int k =(last+first+dob+30);
        tmpSt = curClass ->pHeadStudent;
        int i = 1;
        cout <<"        "<<setw(k/2+7)<< right << "CLASS " << curClass->name<<endl;
        cout << "       "<<"|"<<"No"<<" |" <<setw(8) <<left <<"ID"<<"|"<<"  "<<setw(last)<<left<<"Last name"<<"  |"<<"  "<<setw(first)<<left<<"First name"<<"  |"<<"  "<<setw(dob)<<left<<"DOB"<<"  |"<<"  "<<setw(6)<<left<<"Gender"<<"  |"<<endl;
        while(tmpSt != NULL){
            cout <<"       "<< "|"<<i<<". |" <<setw(8) <<left <<tmpSt->id<<"|"<<"  "<<setw(last)<<left<<tmpSt->lastName<<"  |"<<"  "<<setw(first)<<left<<tmpSt->firstName<<"  |"<<"  "<<setw(dob)<<left<<tmpSt->dOB<<"  |"<<"  "<<setw(6)<<left<<tmpSt->gender<<"  |"<<endl;
            tmpSt = tmpSt -> next;
            ++i;
        }
    }
    return true;
}

void findMaxLength(Student *curSt,int &last,int &first,int &dob){
    while(curSt != NULL){
        if ((curSt ->lastName).length() > last) last = (curSt ->lastName).length();
        if ((curSt ->firstName).length() > first) first = (curSt ->firstName).length();
        if ((curSt ->dOB).length() > dob) dob = (curSt ->dOB).length();
        curSt = curSt ->next;
    }
}
bool menuStudent(Class *&curClass,Student *&tmpSt,CoreData data){
    bool option = true;
    while(1){
        if (!option){
            cout << "Invalid choice. Try again."<<endl;
            option = true;
        }
        menuClass(curClass,data);
        if (curClass == NULL) return false;
        tmpSt = curClass ->pHeadStudent;
        if (tmpSt == NULL){
            cout << "There is no student in this class"<<endl;
            return false;
        }
        else{
            int last = 10,first = 10,dob = 0;
            findMaxLength(tmpSt,last,first,dob);
            int k =(last+first+dob+30);
            tmpSt = curClass ->pHeadStudent;
            int i = 1,choice;
            cout <<"        "<<setw(k/2+7)<< right << "CLASS " << curClass->name<<endl;
            cout << "       "<<"|"<<"No"<<" |" <<setw(8) <<left <<"ID"<<"|"<<"  "<<setw(last)<<left<<"Last name"<<"  |"<<"  "<<setw(first)<<left<<"First name"<<"  |"<<"  "<<setw(dob)<<left<<"DOB"<<"  |"<<"  "<<setw(6)<<left<<"Gender"<<"  |"<<endl;
            while(tmpSt != NULL){
                cout <<"       "<< "|"<<i<<". |" <<setw(8) <<left <<tmpSt->id<<"|"<<"  "<<setw(last)<<left<<tmpSt->lastName<<"  |"<<"  "<<setw(first)<<left<<tmpSt->firstName<<"  |"<<"  "<<setw(dob)<<left<<tmpSt->dOB<<"  |"<<"  "<<setw(6)<<left<<tmpSt->gender<<"  |"<<endl;
                tmpSt = tmpSt -> next;
                ++i;
            }
            cout << endl;
            cout << ">Choose student: (0 to return): ";
            cin >> choice;
            if (choice == 0) return menuStudent(curClass,tmpSt,data);
            else if (choice <= curClass ->numOfStudents){
                tmpSt = curClass ->pHeadStudent;
                int i = 1;
                while (i < choice){
                    tmpSt = tmpSt -> next;
                    ++i;
                }
                return true;
            }
            else option = false;
        }
    }
}

bool addAStudent(CoreData &data){
    Student *tmpSt = new Student;
    Student *curSt;
    Class *curClass;
    string classname;
    cout << "Input: "<<endl;
    cout <<"    "<<"ID:" ;
    cin >> tmpSt->id;
    if(findStudent(tmpSt->id,data,curSt,curClass)){
        cout << "Existing student!"<<endl;
        cout << "       1.Input again."<<endl;
        cout << "       2.Return"<<endl;
        int choice;
        cout << "       >Your choice: ";
        cin >> choice;
        switch(choice){
        case 1:
            return addAStudent(data);
            case 2:
                return false;
            default:
                break;
        }
    }
    else{
        cout << "    "<<"Last name:" ;
        cin.ignore();
        getline(cin,tmpSt->lastName);
        cout << "    "<<"First name: " ;
        getline(cin,tmpSt->firstName);
        cout <<"    "<< "DoB : " ;
        getline(cin,tmpSt->dOB);
        inputGender(tmpSt->gender);
        creatClassToImport(data);
        cout <<"    "<< "Class: ";
        Class *tmpClass = NULL;
        menuClass(tmpClass,data);
        if (tmpClass == NULL) return addAStudent(data);
        tmpSt ->hashPassword = hashPass(to_string(tmpSt->id));
        addStudentToClass(tmpClass->name,tmpSt,data);
        return true;
    }
    return true;
}

void inputGender(string &gender){
    bool k = true;
    while (1){
        if (k == false) cout <<"    "<< "Invalid choice,try again"<<endl;
        cout << "    " <<"Gender(0.male)& (1.female): " ;
        int choice;
        cin >> choice;
        switch(choice){
            case 0:
                gender = "male";
                return;
            case 1:
                gender = "female";
                return;
            default:
                k = false;
                break;
        }
    }
}
bool removeAStudent(CoreData &data){
        Class *curClass = NULL;
        Student *curSt = NULL;
        if (!menuStudent(curClass,curSt,data)) return false;
        removeStudent(curSt->id,data);
        return true;
}

bool moveStudentFromAToB (CoreData &data){
    Student *tmpSt = NULL;
    Class *tmpClass = NULL;
    if (!menuStudent(tmpClass,tmpSt,data)) return false;
    Class *curClass = NULL;
    Student *curSt = new Student;
    copyStudentInfor(curSt,tmpSt);
    menuClass(curClass,data);
    if (curClass != nullptr){
        removeStudent(tmpSt ->id,data);
        addStudentToClass(curClass->name,curSt,data);
        return true;
    }
    else return moveStudentFromAToB(data);
}

void copyStudentInfor(Student *&dup,Student *tmpSt){
    dup->id = tmpSt->id;
    dup->lastName = tmpSt->lastName;
    dup->firstName = tmpSt->firstName;
    dup->dOB = tmpSt->dOB;
    dup->gender = tmpSt->gender;
    dup->hashPassword = tmpSt->hashPassword;
    dup->next = NULL;
    dup->numOfCourse = tmpSt->numOfCourse;
    dup->pHeadCourseManager = tmpSt ->pHeadCourseManager;
}

void activity6(string pathname, CoreData &data){
    Class *curClass = NULL;
    if (!viewListOfStudents(curClass,data)) return;
    cout << "Input any integer to run again (0 to return): ";
    int choice;
    cin >> choice;
    if(choice == 0) return;
    activity6(pathname,data);
}

void activity3(string pathname, CoreData &data){
    int choice;
    cout << "1.Input ID to edit." <<endl;
    cout << "2.View menu." <<endl;
    cout <<"Your choice (0 to return): ";
    cin >> choice;
    switch(choice){
        case 0:
            return;
        case 1:{
            if (!editAnExistingStudent(data)){
                activity3(pathname,data);
                return;
            }
            break;
        }
        case 2:
            if (!editByMenu(data)){
                activity3(pathname,data);
                return;
            }
            break;
        default:{
            cout << "Invalid choice,try again.";
            activity3(pathname,data);
            return;
        }
    }
    saveToDataBase(pathname,data);
    cout << "Input any integer to run again (0 to return): ";
    cin >> choice;
    if(choice == 0) return;
    activity3(pathname,data);
}

void activity5(string pathname, CoreData &data){
    if (!moveStudentFromAToB(data)) return;
    saveToDataBase(pathname,data);
    cout << "Change successfully!" << endl;
    cout << "Input any integer to run again (0 to return): ";
    int choice;
    cin >> choice;
    if(choice == 0) return;
    activity5(pathname,data);
}

void activity2(string pathname, CoreData &data){
    if (!addAStudent(data)) return;
    saveToDataBase(pathname,data);
    cout << "Add student successfully!"<<endl;
    cout << "Input any integer to run again (0 to return): ";
    int choice;
    cin >> choice;
    if(choice == 0) return;
    activity5(pathname,data);
}

void activity4(string pathname, CoreData &data){
    if (!removeAStudent(data)) return;
    saveToDataBase(pathname,data);
    cout << "Remove student successfully!"<<endl;
     cout << "Input any integer to run again (0 to return): ";
    int choice;
    cin >> choice;
    if(choice == 0) return;
    activity4(pathname,data);
}

void activity1(string pathname, CoreData &data){
    importStudentFromCsvFile(data);
    cout << "Import successfully!"<<endl;
    cout << "Input any integer to run again (0 to return): ";
    int choice;
    cin >> choice;
    if(choice == 0) return;
    activity5(pathname,data);
}
