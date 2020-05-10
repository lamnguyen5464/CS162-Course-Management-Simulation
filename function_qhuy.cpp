#include <fstream>
#include <cstring>
#include <iostream>
#include "Data.hpp"
#include "function_qhuy.h"
using namespace std;


void staffClassMenu (CoreData &data){
    cout << string (100,'\n');
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
        cout << "Your choice: ";
        cin >> yourChoice;
        switch (yourChoice){
            case 0:
                return;
            case 1:
                importStudentFromCsvFile(data);
                break;
            case 2:
                addAStudent(data);
                break;
            case 3:
                editAnExistingStudent(data);
                break;
            case 4:
                removeAStudent(data);
                break;
            case 5:
                 moveStudentFromAToB (data);
                 break;
            case 6:
                viewListOfClasses(data);
                break;
            default:
                showOption = false;
                break;
        }
    }
}

void inputStudentFromFile(Student *tmpSt,Class *&tmpClass,ifstream &fin){
    string tmp;
    int number;
    tmpSt = new Student;
    getline(fin,tmp,'\n');
    while(!fin.eof()){
        fin >> number;
        fin.ignore(1);
        fin >> tmpSt->id;
        fin.ignore(1);
        getline(fin,tmpSt->lastName,',');
        getline(fin,tmpSt->firstName,',');
        getline(fin,tmpSt->gender,',');
        getline(fin,tmpSt->dOB,'\n');
        tmpClass->numOfStudents++;
        addStudentToClass(tmpClass,tmpSt);
    }
}

void importStudentFromCsvFile (CoreData &data){
    ifstream fin;
    string linkOfFile,nameOfClass;
    while(1){
        cout << "Which class do you want to import: ";
        cin.ignore();
        getline(cin, nameOfClass);
        cout << "Please let us know the link of your csv file: ";
        getline(cin, linkOfFile);
        fin.open(linkOfFile);
        if (!fin.is_open()){
            cout << "can not open file"<<endl;
        }
        else{
            Class *tmpClass;
            Student *tmpSt;
            if (findClass(nameOfClass,data,tmpClass)){////check whether the class has existed
                cout << "This class has already existed"<<endl;
                cout << "1.Add to the existing class."<<endl;
                cout << "2.Input another class. "<<endl;
                cout << "3.Return"<<endl;
                cout << "Your choice: "<<endl;
                int choice;
                cin >> choice;
                switch(choice){
                    case 1:
                        inputStudentFromFile(tmpSt,tmpClass,fin);
                    case 3:
                        return;
                    default:
                        break;
                }
            }
            else{
                createNewEmptyClass(nameOfClass,data);
                inputStudentFromFile(tmpSt,data.pHeadClass,fin);
                int tmp;
                cout << "Do you want to continue(1.Yes 0.No): ";
                cin >> tmp;
                switch(tmp){
                    case 0:
                        return;
                    default:
                        break;
                }
            fin.close();
            }
        }
    }
}

void edit(Student *&tmpSt,int choice,bool &checkChoice){
    switch(choice){
        case 1:{
            cout << "New ID: ";
            long long tmpID;
            cin >> tmpID;
            tmpSt ->id = tmpID;
            cout << "Edit successfully"<<endl;
            break;
        }
        case 2:{
            cout << "New last name: ";
            string tmpLast;
            cin.ignore();
            getline(cin,tmpLast);
            tmpSt ->lastName = tmpLast;
            cout << "Edit successfully"<<endl;
            break;
        }
        case 3:{
            cout << "New first name: ";
            string tmpFirst;
            cin.ignore();
            getline(cin,tmpFirst);
            tmpSt ->firstName = tmpFirst;
            cout << "Edit successfully"<<endl;
            break;
        }
        case 4:{
            cout << "New doB: ";
            string tmpdob;
            cin.ignore();
            getline(cin,tmpdob);
            tmpSt ->dOB = tmpdob;
            cout << "Edit successfully"<<endl;
            break;
        }
        case 5:{
            cout << "New gender: ";
            string tmpgender;
            cin.ignore();
            getline(cin,tmpgender);
            tmpSt ->gender= tmpgender;
            cout << "Edit successfully"<<endl;
            break;
        }
        default:
            checkChoice = false;
            break;
    }
}
void editAnExistingStudent(CoreData &data){
    bool checkChoice = true;
    while(1){
        long long ID;
        if (checkChoice == false) cout << "Your choice is invalid"<<endl;
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
            if (choice == 0) return;
            edit(tmpSt,choice,checkChoice);

        }
        else{
            cout << "Can not find student"<<endl;
            cout << "1.Input another student."<<endl;
            cout << "2.Return" << endl;
            cout << "Your choice: ";
            cin >> choice;
            switch(choice){
                case 2:
                    return;
                default:
                    break;
            }
        }
    }
}

void viewListOfClasses(CoreData data){
    bool checkChoice = true;
    while(1){
        if (checkChoice == false) cout << "Your choice is invalid. "<<endl;
        Class *curClass = data.pHeadClass;
        if (data.numOfClasses == 0) {
            cout << "There is no class"<<endl;
            return;
        }
        else{
            int a = 1,choice;
            while (curClass != NULL){
                cout<< a <<". " << "Class: " << curClass ->name << " has " << curClass ->numOfStudents << " students." <<endl;
                curClass = curClass ->next;
                a++;
            }
            cout << "Which class do you want to view list of students (0 to return): ";
            cin >> choice;
            if (choice == 0) return;
            else if (choice <= data.numOfClasses){
                curClass = data.pHeadClass;
                int i = 1;
                while (i < choice){
                    curClass = curClass ->next;
                    i++;
                }
                viewListOfStudents(curClass);
            }
            else checkChoice = false;
        }
    }
}

void viewListOfStudents(Class *curClass){
    Student *tmpSt = curClass ->pHeadStudent;
    if (tmpSt == NULL){
        cout << "there is no student in this class"<<endl;
    }
    else{
        cout << "----LIST OF STUDENTS----"<<endl;
        while(tmpSt != NULL){
            cout << "--------------------------------"<<endl;
            cout <<"| " << tmpSt->id <<" | " << tmpSt->lastName <<" | " << tmpSt->firstName <<" | "<< tmpSt->dOB <<" | " << tmpSt->gender<<" |"<<endl;
            tmpSt = tmpSt ->next;
        }
        cout << "---------------------------------"<<endl;
    }
}

void addAStudent(CoreData &data){
    while(1){
        Student *tmpSt = new Student;
        Student *curSt;
        Class *curClass;
        string classname;
        cout << "Please input the student's ID: " ;
        cin >> tmpSt->id;
        if(findStudent(tmpSt->id,data,curSt,curClass)){
            cout << "This student has already exist"<<endl;
            cout << "1.Input another student."<<endl;
            cout << "2.Return"<<endl;
            int choice;
            cout << "Your choice: "<<endl;
            cin >> choice;
            switch(choice){
                case 2:
                    return;
                default:
                    break;
            }
        }
        else{
            cout << "Please input the student's last name: " ;
            cin.ignore();
            getline(cin,tmpSt->lastName);
            cout << "Please input the student's first name: " ;
            getline(cin,tmpSt->firstName);
            cout << "Please input the student's DoB : " ;
            getline(cin,tmpSt->dOB);
            cout << "Please input the student's gender: " ;
            getline(cin,tmpSt->gender);
            cout << "Which class you want to put this student in: ";
            getline(cin,classname);
            addStudentToClass(classname,tmpSt,data);
            int tmp;
            cout << "Do you want to continue(1.Yes 0.No): ";
            cin >> tmp;
            switch(tmp){
                case 0:
                    return;
                default:
                    break;
            }
        }
    }
}

void removeAStudent(CoreData &data){
    while(1){
        long long tmpid;
        cout << "Please input the id whose you want to delete: ";
        cin >> tmpid;
        removeStudent(tmpid,data);
        int tmp;
        cout << "Do you want to continue(1.Yes 0.No): ";
        cin >> tmp;
        switch(tmp){
            case 0:
                return;
            default:
                break;
        }
    }
}

void moveStudentFromAToB (CoreData &data){
    while(1){
        long long id;
        cout << "Please input the student's ID: ";
        cin >> id;
        Student *tmpSt;
        Class *tmpClass;
        string classmove;
        if (findStudent(id,data,tmpSt,tmpClass)){
            cout << "Name: " << tmpSt->lastName << " " << tmpSt->firstName << endl;
            cout << "Class: "<< tmpClass ->name <<endl;
            cout << "DoB: " << tmpSt->dOB<<endl;
            cout <<"Gender: "<<tmpSt->gender<<endl;
            cout << "Which class do you want this student to move to?" <<endl;
            cin.ignore();
            getline(cin,classmove);
            Student *cur = new Student;
            copyStudentInfor(cur,tmpSt);
            removeStudent(id,data);
            addStudentToClass(classmove,cur,data);
            int tmp;
            cout << "Do you want to continue(1.Yes 0.No): ";
            cin >> tmp;
            switch(tmp){
                case 0:
                    return;
                default:
                    break;
            }
        }
        else{
            cout << "can not find student." <<endl;
            cout <<"1.Input another id." <<endl;
            cout <<"2.Return."<<endl;
            int choice;
            cin >> choice;
            switch(choice){
                case 2:
                    return;
                default:
                    break;
            }
        }
    }
}

void copyStudentInfor(Student *&dup,Student *tmpSt){
    dup->id = tmpSt->id;
    dup->lastName = tmpSt->lastName;
    dup->firstName = tmpSt->firstName;
    dup->dOB = tmpSt->dOB;
    dup->gender = tmpSt->gender;
    dup->hashPassword = tmpSt->hashPassword;
    dup->next = tmpSt->next;
    dup->numOfCourse = tmpSt->numOfCourse;
    dup->pHeadCourseManager = tmpSt ->pHeadCourseManager;
}
