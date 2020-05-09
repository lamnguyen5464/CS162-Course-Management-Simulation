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
            cout << "__________________MENU__________________" << endl;
            cout << "1.Import students of a class from the csv file." << endl;
            cout << "2.Manually add a student to a class." << endl;
            cout << "3.Edit an existing student" << endl;
            cout << "4.Remove a student" << endl;
            cout << "5.Change a student from class A to class B." << endl;
            cout << "6.View list of classes." << endl;
            cout << "7.View list of students in a class."<<endl;
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

            case 1:
                importStudentFromCsvFile(data);
                break;
            case 2:

            case 3:
                editAnExistingStudent (data);
            case 4:

            case 5:

            case 6:
                viewListOfClasses(data);
                break;
            case 7:
                viewListOfStudents(data);
                break;
            default:
                showOption = false;
                break;
        }
    }
}

void importStudentFromCsvFile (CoreData &data){
    ifstream fin;
    string linkOfFile,nameOfClass;
    cout << "Which class do you want to import: ";
    getline(cin, nameOfClass);
    cout << "Please let us know the link of your csv file: ";
    getline(cin, linkOfFile);
    fin.open(linkOfFile);
    if (!fin.is_open()){
        cout << "can not open file"<<endl;
    }
    else{
        int choice = 2;
        Class *tmpClass = NULL;
        while (findClass(nameOfClass,data,tmpClass) && choice == 2){////check whether the class has existed
            cout << "This class has already existed"<<endl;
            cout << "1.Add to the existing class."<<endl;
            cout << "2.Input another class. "<<endl;
            cout << "Your choice: "<<endl;
            cin >> choice;
            switch (choice){
                case 2:
                    cout << "Which class do you want to import: ";
                    getline(cin, nameOfClass);
                    break;
                default:
                    break;
            }
        }
        Student *tmpSt;
        int number;
        // ? how to ignore the header
        if (choice == 1){//user choose to add the file to the existing class.
            while (!fin.eof()){
                fin >> number;
                fin >> tmpSt->id;
                getline(fin,tmpSt-> lastName);
                getline(fin,tmpSt->firstName);
                getline(fin,tmpSt->gender);
                getline(fin,tmpSt->dOB);
                tmpClass->numOfStudents++;
                addStudentToClass(tmpClass,tmpSt);
            }
        }
        else{//a new class.
            createNewEmptyClass(nameOfClass,data);
            while (!fin.eof()){
                fin >> number;
                fin >> tmpSt->id;
                getline(fin,tmpSt-> lastName);
                getline(fin,tmpSt->firstName);
                getline(fin,tmpSt->gender);
                getline(fin,tmpSt->dOB);
                tmpClass->numOfStudents++;
                addStudentToClass(data.pHeadClass,tmpSt);//the new class become pheadclass
            }
        }
        fin.close();
    }
}
void edit(Student *&tmpSt,int choice){
    switch(choice){
        case 1:{
            cout << "New ID: ";
            long long tmpID;
            cin >> tmpID;
            tmpSt ->id = tmpID;
            cout << "Edit successfully";
            break;
        }
        case 2:{
            cout << "New last name: ";
            string tmpLast;
            getline(cin,tmpLast);
            tmpSt ->lastName = tmpLast;
            cout << "Edit successfully";
            break;
        }
        case 3:{
            cout << "New first name: ";
            string tmpFirst;
            getline(cin,tmpFirst);
            tmpSt ->firstName = tmpFirst;
            cout << "Edit successfully";
            break;
        }
        case 4:{
            cout << "New doB: ";
            string tmpdob;
            getline(cin,tmpdob);
            tmpSt ->dOB = tmpdob;
            cout << "Edit successfully";
            break;
        }
        case 5:{
            cout << "New gender: ";
            string tmpgender;
            getline(cin,tmpgender);
            tmpSt ->gender= tmpgender;
            cout << "Edit successfully";
            break;
        }
        default:
            break;
    }
}
void editAnExistingStudent (CoreData &data){
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
        cout << "Your choice: ";
        cin >> choice;
        edit(tmpSt,choice);

    }
    else{
        cout << "Can not find student"<<endl;
        cout << "1.Input another student."<<endl;
        cout << "2.Return";
        cout << "Your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
            //input another student.
            default:
                break;
        }
    }
}

void viewListOfClasses(CoreData data){
    Class *curClass = data.pHeadClass;
    if (data.numOfClasses == 0) cout << "There is no class"<<endl;
    else{
        while (curClass != NULL){
            cout << "Class: " << curClass ->name << " has " << curClass ->numOfStudents << "students." <<endl;
            curClass = curClass ->next;
        }
    }
    //return to the previous menu.
}

void viewListOfStudents(CoreData data){
    Class *tmpClass = NULL;
    string classname;
    int choice = 1;
    cout << "Which class do you want to view list: ";
    getline(cin,classname);
    while(findClass(classname,data,tmpClass) == false && choice == 1){
        cout << "Can not find this class"<<endl;
        cout << "1.Please input again: " << endl;
        cout << "2.Return: " <<endl;
        cout << "Your choice: ";
        cin >> choice;
        switch(choice){
            case 1:{
                getline(cin,classname);
                break;
            }
            default:
                break;
        }
    }
    if (choice != 2){
        Student *curSt = tmpClass ->pHeadStudent;
        if (curSt == NULL){
            cout << "This class is empty";
            //return;
        }
        while (curSt != NULL){
            cout << curSt->id << " " << curSt ->lastName << " "<<curSt ->firstName<< " "<<curSt->dOB<<" "<<curSt->gender<<endl;
            curSt = curSt ->next;
        }
    }
}
