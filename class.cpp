#include <fstream>
#include <cstring>
#include <string>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Data.hpp"
#include "class.h"
#include "Student.hpp"
#include "Course.h"
using namespace std;

void clearScreen(){
    system("cls");
}

void toUpper(string &name){
    for (int i = 0;i < name.length();i++)
        if (name[i] >= 'a' && name[i] <='z')
        name[i] = name[i] - 32;
}
void staffClassMenu (string pathname,CoreData &data){
    clearScreen();
    bool showOption = true;
    while (1){
        if (showOption){
            cout <<"        "<<" ______________________________________________________________" << endl;
            cout <<"        "<<"|"<<"_______________________MENU_STAFF_CLASS_______________________"<<"|" << endl;
            cout <<"        "<<"|   "<<setw(56)<<left<< "0.Return to previous menu." <<"   |"<< endl;
            cout <<"        "<<"|   "<<setw(56)<<left<< "1.Import students of a class from the csv file." <<"   |"<< endl;
            cout <<"        "<<"|   "<<setw(56)<<left<< "2.Manually add a student to a class." <<"   |"<< endl;
            cout <<"        "<<"|   "<<setw(56)<<left<< "3.Edit an existing student" <<"   |"<< endl;
            cout <<"        "<<"|   "<<setw(56)<<left<< "4.Remove a student"<<"   |" << endl;
            cout <<"        "<<"|   "<<setw(56)<<left<< "5.Change a student from class A to class B." <<"   |"<< endl;
            cout <<"        "<<"|   "<<setw(56)<<left<< "6.View list of classes and list of students in a class." <<"   |"<< endl;
            cout <<"        "<<"|______________________________________________________________|" << endl;
        }
        else{
            cout <<"        "<< "Invalid choice!Try again!"<< endl;
            showOption = true;
        }
        int yourChoice;
        cout <<"        "<< ">Your choice: ";
        cin >> yourChoice;
        switch (yourChoice){
            case 0:
                return;
            case 1:
                activity2_1(pathname,data);
                break;
            case 2:
                activity2_2(pathname,data);
                break;
            case 3:
                activity2_3(pathname,data);
                break;
            case 4:
                activity2_4(pathname,data);
                break;
            case 5:
                 activity2_5(pathname,data);
                 break;
            case 6:{
                activity2_6(pathname,data);
                break;
            }
            default:
                showOption = false;
                break;
        }
        if(showOption) clearScreen();
    }
}

void inputStudentFromFile(Student *tmpSt,Class *&tmpClass,ifstream &fin,CoreData &data){
    string headers;
    string no;
    long long tmp = 0;
    getline(fin,headers,'\n'); //ignore headers
    while(!fin.eof()){
        getline(fin, no, ','); //ignore no
        tmpSt = new Student;
        fin >> tmp;
        if (tmp != 0){
            tmpSt -> id = tmp;
            fin.ignore(1);
            getline(fin,tmpSt->lastName,',');
            getline(fin,tmpSt->firstName,',');
            getline(fin,tmpSt->gender,',');
            getline(fin,tmpSt->dOB,'\n');
            tmpSt->hashPassword = hashPass(to_string(tmpSt->id));
            Student *curSt = NULL;
            Class *curClass = NULL;
            if (!findStudent(tmpSt->id,data,curSt,curClass))
                addStudentToClass(tmpClass->name,tmpSt,data);
            tmp = 0;
        }
    }
}

bool importStudentFromCsvFile (CoreData &data,string pathname){
    ifstream fin;
    string linkOfFile;
    cout <<"            "<< "Csv file(0 to return): ";
    cin.ignore();
    getline(cin, linkOfFile);
    if (linkOfFile == "0") return false;
    fin.open(pathname + linkOfFile);
    if (!fin.is_open()){
        cout <<"            "<< "can not open file"<<endl;
    }
    else{
        string classname = "";
        getClassName(classname,linkOfFile);
        Class *curClass = NULL;
        if (findClass(classname,data,curClass)){
            cout <<"            "<< "Existing class!"<<endl;
            return true;
        }
       // t chua biet xu li ten lop sao
        createNewEmptyClass(classname,data);
        Class *tmpClass = NULL;
        findClass(classname,data,tmpClass);
        Student *tmpSt = NULL ;
        inputStudentFromFile(tmpSt,tmpClass,fin,data);
        cout <<"            "<< "Import successfully!"<<endl;
        fin.close();
    }
    return true;
}
void getClassName(string &classname,string linkOfFile){
    int i = 0;
    while (linkOfFile[i]!= '.'){
        classname += linkOfFile[i];
        ++i;
    }
}

void createClassToImport(CoreData &data){
    bool k = true;
    string classname;
    while(1){
        if (!k) {
            cout <<"            "<< "Invalid choice. Try again."<<endl;
            k = true;
        }
        int choice;
        cout <<"            "<< "Do you want to create a new class(0.No)&(1.Yes): ";
        cin >> choice;
        switch(choice){
            case 1:{
                cout <<"            "<< "Class's name: ";
                cin.ignore();
                getline(cin,classname);
                Class *foundclass = NULL;
                if (!findClass(classname,data,foundclass))
                    createNewEmptyClass(classname,data);
                else{
                    cout <<"            "<< "Existing class!"<<endl;
                    createClassToImport(data);
                    return;
                }
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
            cout <<"            "<< "   New last name: ";
            string tmpLast;
            cin.ignore();
            getline(cin,tmpLast);
            if (tmpLast != "0" ){
                tmpSt ->lastName = tmpLast;
                cout <<"            "<< "   Edit successfully!"<<endl;
            }
            break;
        }
        case 2:{
            cout <<"            "<< "   New first name: ";
            string tmpFirst;
            cin.ignore();
            getline(cin,tmpFirst);
            if (tmpFirst != "0" ){
                tmpSt ->firstName = tmpFirst;
                cout <<"            "<< "   Edit successfully!"<<endl;
            }
            break;
        }
        case 3:{
            cout <<"            "<< "   New doB: ";
            string tmpdob;
            cin.ignore();
            getline(cin,tmpdob);
            if (tmpdob != "0" ){
                tmpSt ->dOB = tmpdob;
                cout <<"            "<< "   Edit successfully!"<<endl;
            }
            break;
        }
        case 4:{
            cout <<"            "<< "    New gender: "<<endl;
            string tmpgender;
            inputGender(tmpgender);
            if (tmpgender != "0" ){
                tmpSt ->gender = tmpgender;
                cout <<"            "<< "   Edit successfully!"<<endl;
            }
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
    cout <<"            "<< "Please input id of the student you want to edit(0 to return): ";
    cin >> ID;
    if (ID == 0) return false;
    Student *tmpSt=NULL;
    Class *tmpClass=NULL;
    int choice;
    if (findStudent(ID,data,tmpSt,tmpClass)){
        cout <<"            "<< "What part do you want to edit? "<<endl;
        cout <<"            "<< "1.Last name: " << tmpSt->lastName<< endl;
        cout <<"            "<< "2.First name: " << tmpSt->firstName << endl;
        cout <<"            "<< "3.DoB: " << tmpSt->dOB << endl;
        cout <<"            "<< "4.Gender: " << tmpSt->gender << endl;
        cout <<"            "<< ">Your choice (0 to return): ";
        cin >> choice;
        if (choice == 0) return false;
        edit(tmpSt,choice,checkChoice);
    }
    else{
        cout <<"            "<< "Can not find student"<<endl;
        cout <<"            "<< "0.Return" << endl;
        cout <<"            "<< "1.Input another student."<<endl;
        cout <<"            "<< ">Your choice: ";
        cin >> choice;
        switch(choice){
            case 0:
                return false;
            case 1:
                return editAnExistingStudent(data);
            default:
                break;
        }
    }
    if (checkChoice == false){
        cout << "Invalid choice. Try again."<<endl;
        checkChoice = true;
    }
    return true;
}

bool editByMenu (CoreData &data){
    Student *curSt = NULL;
    Class *curClass = NULL;
    bool checkChoice = true;
    int choice;
    if (!showMenuStudent(curClass,curSt,data)) return false;
    cout << endl;
    cout <<"            "<< "What part do you want to edit? "<<endl;
    cout <<"            "<< "1.Last name: " << curSt->lastName<< endl;
    cout <<"            "<< "2.First name: " << curSt->firstName << endl;
    cout <<"            "<< "3.DoB: " << curSt->dOB << endl;
    cout <<"            "<< "4.Gender: " << curSt->gender << endl;
    cout <<"            "<< ">Your choice (0 to return): ";
    cin >> choice;
    if (choice == 0) return false;
    edit(curSt,choice,checkChoice);
    if (checkChoice == false){
        cout << "Invalid choice. Try again."<<endl;
        checkChoice = true;
    }
    return true;
}

void menuClass(Class *&curClass,CoreData data){
    bool checkChoice = true;
    while(1){
        if (checkChoice == false) {
            cout <<"        "<< "Invalid choice. Try again. "<<endl;
            checkChoice = true;
        }
        if (data.numOfClasses == 0) {
            cout <<"        "<< "There is no class"<<endl;
            return;
        }
        curClass = data.pHeadClass;
        int a = 1,choice;
        cout <<"        "<< "Choose class: "<<endl;
        while (curClass != NULL){
            cout<<"        "<<"    "<< a <<". " << "Class " << curClass ->name << ": " << curClass ->numOfStudents << " students." <<endl;
            curClass = curClass ->next;
            a++;
        }
        cout <<"        " <<"    "<< "Choose class: (No - 0 to return): ";
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
    if (curClass == NULL){
        if (data.numOfClasses == 0){
            cout <<"    "<< "       "<< "Input any number to return: ";
            int tmp;
            cin >> tmp;
            return false;
        }
        else return false;
    }
    Student *tmpSt = curClass ->pHeadStudent;
    if (tmpSt == NULL){
        cout <<"    "<< "       "<< "There is no student. Input any number to return: ";
        int tmp;
        cin >> tmp;
        return false;
    }
    else{
        int last = 10,first = 10,dob = 5,id = 3;
        findMaxLengthOfStudentInfo(tmpSt,last,first,dob,id);
        int k =(last+first+dob+30);
        tmpSt = curClass ->pHeadStudent;
        int i = 1;
        cout <<"    "<<"        "<<setw(k/2+7)<< right << "CLASS " << curClass->name<<endl;
        cout <<"    "<< "       "<<"|"<<"No"<<" |" <<setw(id) <<left <<"ID"<<"|"<<"  "<<setw(last)<<left<<"Last name"<<"  |"<<"  "<<setw(first)<<left<<"First name"<<"  |"<<"  "<<setw(6)<<left<<"Gender"<<"  |"<<"  "<<setw(dob)<<left<<"DOB"<<"  |"<<endl;
        while(tmpSt != NULL){
            cout <<"    "<<"       "<< "|"<<i<<". |" <<setw(id) <<left <<tmpSt->id<<"|"<<"  "<<setw(last)<<left<<tmpSt->lastName<<"  |"<<"  "<<setw(first)<<left<<tmpSt->firstName<<"  |"<<"  "<<setw(6)<< left <<tmpSt->gender<<"  |"<<"  "<<setw(dob)<<left<<tmpSt->dOB<<"  |"<<endl;
            tmpSt = tmpSt -> next;
            ++i;
        }
    }
    return true;
}

void findMaxLengthOfStudentInfo(Student *curSt,int &last,int &first,int &dob,int &id){
    while(curSt != NULL){
        if ((to_string(curSt->id)).length() > id) id = (to_string(curSt->id)).length();
        if ((curSt ->lastName).length() > last) last = (curSt ->lastName).length();
        if ((curSt ->firstName).length() > first) first = (curSt ->firstName).length();
        if ((curSt ->dOB).length() > dob) dob = (curSt ->dOB).length();
        curSt = curSt ->next;
    }
}
bool showMenuStudent(Class *&curClass,Student *&tmpSt,CoreData data){
    bool option = true;
    while(1){
        if (!option){
            cout <<"    "<< "       "<< "Invalid choice. Try again."<<endl;
            option = true;
        }
        menuClass(curClass,data);
        if (curClass == NULL){
            if (data.numOfClasses == 0){
                cout <<"    "<< "       "<< "Input any number to return: ";
                int tmp;
                cin >> tmp;
                return false;
            }
            else return false;
        }
        tmpSt = curClass ->pHeadStudent;
        if (tmpSt == NULL){
            cout << "       "<< "There is no student in this class"<<endl;
            return false;
        }
        else{
            int last = 10,first = 10,dob = 5,id = 3;
            findMaxLengthOfStudentInfo(tmpSt,last,first,dob,id);
            int k =(last+first+dob+30);
            tmpSt = curClass ->pHeadStudent;
            int i = 1,choice;
            cout <<"    "<<"        "<<setw(k/2+7)<< right << "CLASS " << curClass->name<<endl;
            cout <<"    "<< "       "<<"|"<<"No"<<" |" <<setw(id) <<left <<"ID"<<"|"<<"  "<<setw(last)<<left<<"Last name"<<"  |"<<"  "<<setw(first)<<left<<"First name"<<"  |"<<"  "<<setw(dob)<<left<<"DOB"<<"  |"<<"  "<<setw(6)<<left<<"Gender"<<"  |"<<endl;
            while(tmpSt != NULL){
                cout <<"    "<<"       "<< "|"<<i<<". |" <<setw(id) <<left <<tmpSt->id<<"|"<<"  "<<setw(last)<<left<<tmpSt->lastName<<"  |"<<"  "<<setw(first)<<left<<tmpSt->firstName<<"  |"<<"  "<<setw(dob)<<left<<tmpSt->dOB<<"  |"<<"  "<<setw(6)<<left<<tmpSt->gender<<"  |"<<endl;
                tmpSt = tmpSt -> next;
                ++i;
            }
            cout << endl;
            cout <<"    "<< "       "<<">Choose student: (No - 0 to return): ";
            cin >> choice;
            if (choice == 0) return showMenuStudent(curClass,tmpSt,data);
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
    cout <<"            "<< "Input(0 to return): "<<endl;
    cout <<"            "<<"    "<<"ID:" ;
    cin >> tmpSt->id;
    if (tmpSt->id == 0) return false;
    if(findStudent(tmpSt->id,data,curSt,curClass)){
        cout <<"            "<< "Existing student!"<<endl;
        cout <<"            "<< "       1.Input again."<<endl;
        cout <<"            "<< "       2.Return"<<endl;
        int choice;
        cout <<"            "<< "       >Your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                return addAStudent(data);
            case 2:
                return false;
            default:
                cout <<"            "<< "Invalid choice!" <<endl;
                return addAStudent(data);
        }
    }
    else{
        cout <<"            "<< "    "<<"Last name: " ;
        cin.ignore();
        getline(cin,tmpSt->lastName);
        if (tmpSt->lastName == "0") return false;
        cout <<"            "<< "    "<<"First name: " ;
        getline(cin,tmpSt->firstName);
        if (tmpSt->firstName == "0") return false;
        cout <<"            "<<"    "<< "DoB: " ;
        getline(cin,tmpSt->dOB);
        if (tmpSt->dOB == "0") return false;
        inputGender(tmpSt->gender);
        if (tmpSt->gender == "0") return false;
        createClassToImport(data);
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
        if (k == false){
            cout <<"            "<<"    "<< "Invalid choice,try again"<<endl;
            k = true;
        }
        cout <<"            "<< "    " <<"Gender(1.male)& (2.female): " ;
        int choice;
        cin >> choice;
        switch(choice){
            case 0:
                gender = "0";
                return;
            case 1:
                gender = "male";
                return;
            case 2:
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
        if (!showMenuStudent(curClass,curSt,data)) return false;
        removeStudent(curSt->id,data);
        return true;
}

bool moveStudentFromAToB (CoreData &data){
    Student *tmpSt = NULL;
    Class *tmpClass = NULL;
    cout <<"        "<<"YOU WANT TO MOVE?: "<<endl;
    if (!showMenuStudent(tmpClass,tmpSt,data)) return false;
    Class *curClass = NULL;
    Student *curSt;
    cout <<"        "<<"CLASS TO MOVE THIS STUDENT INTO:"<<endl;
    menuClass(curClass,data);
    if (curClass != nullptr){
        removeStudent(tmpSt ->id,data, curSt);
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

void activity2_6(string pathname, CoreData &data){
    clearScreen();
    cout <<"        "<< "_____________VIEW LIST OF CLASSES AND STUDENTS_____________" << endl;
    Class *curClass = NULL;
    if (!viewListOfStudents(curClass,data)) return;
    cout <<"            "<< "Input any number to back and save (1 to run again): ";
    int choice;
    cin >> choice;
    if(choice != 1) return;
    activity2_6(pathname,data);
}


void activity2_3(string pathname, CoreData &data){
    clearScreen();
    cout <<"            "<< "_____________EDIT AN EXISTING STUDENT_____________" << endl;
    int choice;
    cout <<"            "<< "1.Input ID to edit." <<endl;
    cout <<"            "<< "2.View menu." <<endl;
    cout <<"            "<<"Your choice (0 to return): ";
    cin >> choice;
    switch(choice){
        case 0:
            return;
        case 1:{
            if (!editAnExistingStudent(data)){
                activity2_3(pathname,data);
                return;
            }
            break;
        }
        case 2:
            if (!editByMenu(data)){
                activity2_3(pathname,data);
                return;
            }
            break;
        default:{
            cout <<"            "<< "Invalid choice,try again."<<endl;
            activity2_3(pathname,data);
            return;
        }
    }
    saveToDataBase(pathname,data);
    cout <<"            "<< "Input any number to back and save (1 to run again): ";
    cin >> choice;
    if(choice != 1) return;
    activity2_3(pathname,data);
}

void activity2_5(string pathname, CoreData &data){
    clearScreen();
    cout <<"            "<< "_____________CHANGE CLASS OF A STUDENT_____________" << endl;
    if (!moveStudentFromAToB(data)) return;
    saveToDataBase(pathname,data);
    cout <<"            "<< "Change successfully!" << endl;
    cout <<"            "<< "Input any number to back and save (1 to run again): ";
    int choice;
    cin >> choice;
    if(choice != 1) return;
    activity2_5(pathname,data);
}

void activity2_2(string pathname, CoreData &data){
    clearScreen();
    cout <<"            "<< "_____________MANUALLY ADD A STUDENT_____________" << endl;
    if (!addAStudent(data)) return;
    saveToDataBase(pathname,data);
    cout <<"            "<< "Add student successfully!"<<endl;
    cout <<"            "<< "Input any number to back and save (1 to run again): ";
    int choice;
    cin >> choice;
    if(choice != 1) return;
    activity2_2(pathname,data);
}

void activity2_4(string pathname, CoreData &data){
    clearScreen();
    cout <<"            "<< "_____________REMOVE A STUDENT_____________" << endl;
    if (!removeAStudent(data)) return;
    saveToDataBase(pathname,data);
    cout <<"            "<< "Remove student successfully!"<<endl;
    cout <<"            "<< "Input any number to back and save (1 to run again): ";
    int choice;
    cin >> choice;
    if(choice != 1) return;
    activity2_4(pathname,data);
}

void activity2_1(string pathname, CoreData &data){
    clearScreen();
    cout <<"            "<< "_____________IMPORT STUDENTS FROM A CSV FILE_____________" << endl;
    if (!importStudentFromCsvFile(data,pathname)) return;
    saveToDataBase(pathname,data);
    cout <<"            "<< "Input any number to back and save (1 to run again): ";
    int choice;
    cin >> choice;
    if(choice != 1) return;
    activity2_1(pathname,data);
}

void login(CoreData &data,string pathName){
    clearScreen();
    bool showoption = true;
    string userName;
    string password = "";
    while(1){
        if (showoption == false){
            cout << endl;
            clearScreen();
            cout << "UserName or password is incorrect. Please try again!"<< endl;
            showoption = true;
        }
        cout << "_________________STUDENT_MANAGEMENT_SYSTEM_________________" << endl;
        cout << "UserName: ";
        cin.ignore();
        getline(cin,userName);
        cout << "Password: ";
        inputPassword(password);
        Student *curSt = NULL;
        Lecturer *curLec = NULL;
        Staff *curStaff = NULL;
        Class *tmpClass = NULL;
        int check = checkUser(userName,password,curSt,curLec,curStaff,tmpClass,data);
        password = "";
        if (check == 0){
            showoption = false;
        }
        else{
            showFunctions(check,data,pathName,curSt,curLec,curStaff,tmpClass);
            menuLogin(data,pathName);
        }
    }
}

void inputPassword(string &password){
    char ch;
    while((ch=getch()) != 13){
        if ((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z')||(ch >= '0' && ch <= '9')){
            cout << "*";
            password += ch;
        }
        else if (ch == 8)
            if (!password.empty()){
                cout << "\b" <<" "<<"\b";
                password.pop_back();
            }
    }
}

int checkUser(string Username,string password,Student *&curSt,Lecturer *&curLec,Staff *&curStaff,Class *&tmpClass,CoreData data){
    long long tmpHash = hashPass(password);
    bool isSt = true;
    for (int i = 0;i < Username.length();i++){
        if (!(Username[i] >= '0' && Username[i] <= '9' )){
            isSt = false;
            break;
        }
    }
    if (isSt == true){
        long long tmpID = 0;
        convertStringToId(Username,tmpID);
        if (findStudent(tmpID,data,curSt,tmpClass) && tmpHash == curSt->hashPassword){
            return 1;
        }
    }
    else{
        if (findLecturer(Username,data,curLec) && tmpHash == curLec->hashPassword)
            return 2;
        else if (findStaff(Username,data,curStaff) && tmpHash == curStaff->hashPassword)
            return 3;
    }
    return 0;

}

void convertStringToId (string Username,long long &ID){
    for (int i = 0;i < Username.length();i++){
        ID = ID*10  + (Username[i] - 48);
    }
}

void showFunctions (int check,CoreData &data,string pathName,Student *&curSt,Lecturer *&curLec,Staff *&curStaff,Class *&tmpClass){
    bool showoption = true;
    clearScreen();
    while(1){
        if (!showoption) {
            cout << "   "<< "Invalid choice. Try again."<<endl;
            showoption = true;
        }
        cout << endl;
        cout << "   " <<" _______________________________________________ "<<endl;
        cout << "   "<< "|"<< "____________________OPTIONS____________________"<<"|"<<endl;
        cout << "   "<<"| "<<setw(46)<<left<< "0.Logout."<< "|"<<endl;
        cout << "   "<<"| "<<setw(46)<<left<< "1.Show menu."<<"|"<<endl;
        cout << "   "<<"| "<<setw(46)<<left<< "2.View profile info."<<"|"<<endl;
        cout << "   "<<"| "<<setw(46)<<left<< "3.Change password."<<"|"<<endl;
        cout << "   "<<"|_______________________________________________|"<<endl;
        cout << "   "<< ">Your choice: ";
        int choice;
        cin >> choice;
        switch(choice){
            case 1:
                showMenu(check,data,pathName,curSt,curLec);
                break;
            case 2:
                showProfile(check,curSt,curLec,curStaff,tmpClass);
                break;
            case 3:
                changePassword(check,curSt,curLec,curStaff,pathName,data);
                break;
            case 0:
                cin.ignore();
                return;
                break;
            default:
                showoption = false;
                break;
        }
        if (showoption) clearScreen();
    }
}

void showProfile (int check,Student *curSt,Lecturer *curLec,Staff *curStaff,Class *tmpClass){
    clearScreen();
    cout<<"        " << "_____________PROFILE_____________" << endl;
    switch (check){
        case 1:{
            cout <<"        "<< "User: " <<  curSt->id << endl;
            cout <<"        "<< "   " << "ID: " << curSt->id <<endl;
            cout <<"        "<< "   " << "Name: " << curSt->lastName <<" "<<curSt->firstName <<endl;
            cout <<"        "<< "   " << "DOB: " << curSt->dOB <<endl;
            cout <<"        "<< "   " << "Gender: " << curSt->gender <<endl;
            cout <<"        "<< "   " << "Class: " << tmpClass->name <<endl;
            break;
        }
        case 2:{
            cout <<"        "<<"User: " << curLec->userName<<endl;
            break;
        }
        case 3:{
            cout <<"        "<<"User: " << curStaff->userName<<endl;
            break;
        }
        default:
            break;
    }
    cout <<"        "<< "Input any number to return: ";
    int tmp;
    cin >> tmp;
    return;
}

void changePassword(int check,Student *&curSt,Lecturer *&curLec,Staff *&curStaff,string pathName,CoreData &data){
    clearScreen();
    cout <<"        "<< "_____________CHANGE PASSWORD_____________" << endl;
    string oldPass = "";
    string newPass = "";
    string reNewPass = "";
    cout <<"        "<< "Recent password: ";
    inputPassword(oldPass);
    cout << endl;
    long long tmpHash = hashPass(oldPass);
    switch (check){
        case 1:{
            if (tmpHash != curSt->hashPassword){
                cout <<"        "<< "Your password is incorrect!"<<endl;
            }
            else{
                cout <<"        "<< "New password: ";
                inputPassword(newPass);
                cout << endl;
                cout <<"        "<< "Confirm password: ";
                inputPassword(reNewPass);
                cout << endl;
                if (newPass == reNewPass){
                    curSt->hashPassword=hashPass(newPass);
                    cout <<"        "<< "Change successfully"<<endl;
                }
                else{
                    cout <<"        "<< "Incorrect new pass!"<<endl;
                }
            }
            break;

        }
        case 2:{
            if (tmpHash != curLec->hashPassword){
                cout <<"        "<< "Your password is incorrect!"<<endl;
            }
            else{
                cout <<"        "<< "New password: ";
                inputPassword(newPass);
                cout << endl;
                cout <<"        "<< "Confirm password: ";
                inputPassword(reNewPass);
                cout << endl;
                if (newPass == reNewPass){
                    curLec->hashPassword=hashPass(newPass);
                    cout <<"        "<< "Change successfully!"<<endl;
                }
                else{
                    cout <<"        "<< "Incorrect new pass!"<<endl;
                }
            }
            break;

        }
        case 3:{
            if (tmpHash != curStaff->hashPassword){
                cout << "Your password is incorrect!"<<endl;
            }
            else{
                cout << "New password: ";
                inputPassword(newPass);
                cout << endl;
                cout << "Confirm password: ";
                inputPassword(reNewPass);
                cout << endl;
                if (newPass == reNewPass){
                    curStaff->hashPassword=hashPass(newPass);
                    cout << "Change successfully"<<endl;
                }
                else{
                    cout << "Incorrect new pass!"<<endl;
                }
            }
            break;

        }
        default:
            break;
    }
    saveToDataBase(pathName,data);
    cout << "Input any number to return: ";
    int tmp;
    cin >> tmp;
}

void showMenu (int check,CoreData &data,string pathName,Student *&curSt,Lecturer *&curLec){
    switch(check){
        case 1:
            menuStudent(curSt,data,pathName);
            break;
        case 2:
            menuLecturer(pathName,data,curLec);
            break;
        case 3:
            menuStaff(data,pathName);
            break;
        default:
            break;
    }
}

void menuStaff (CoreData &data,string pathName){
    clearScreen();
    while(1){
        cout <<"        "<< "_____________MENU FOR STAFF_____________" << endl;
        bool option = true;
        if (!option){
            cout<<"        "<< "Invalid choice. Try again."<<endl;
            option = true;
        }
        cout <<"        "<< "0.Return."<<endl;
        cout <<"        "<< "1.Class."<<endl;
        cout <<"        "<< "2.Course."<<endl;
        cout <<"        "<< "3.Scoreboard."<<endl;
        cout <<"        "<< "4.Attendance."<<endl;
        cout <<"        "<< ">Your choice: ";
        int choice;
        cin >> choice;
        switch(choice){
            case 0:
                return;
            case 1:
                staffClassMenu(pathName,data);
                break;
            case 2:
                menuStaffCourse(pathName,data);
                break;
            case 3:
                menuStaffScoreboard(pathName,data);
                break;
            case 4:
                menuStaffAttendance(pathName,data);
                break;
            default:
                option = false;
                break;
        }
        if (option) clearScreen();
    }
}

void menuLogin(CoreData &data,string pathName){
    clearScreen();
    bool option = true;
    while(1){
        if (!option){
            clearScreen();
            cout << "Invalid choice. Try again."<<endl;

            option = true;
        }
        cout << " ___________________________________"<<endl;
        cout << "|_____STUDENT_MANAGEMENT_SYSTEM_____|"<<endl;
        cout << "|                                   |"<<endl;
        cout << "|      "<< "0.Exit" << "                       |"<<endl;
        cout << "|      "<< "1.Login" << "                      |"<<endl;
        cout << "|___________________________________|"<<endl;
        cout << ">Your choice: ";
        int choice;
        cin >> choice;
        switch(choice){
            case 1:
                login(data,pathName);
                break;
            case 0:
                break;
            default:
                option = false;
                break;
        }
    }
}
