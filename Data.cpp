
#include <fstream>
#include <cstring>
#include <iostream>
#include "Data.hpp"
using namespace std;
ifstream fin;
char ch[1000];
void importDataBase(string pathName, CoreData &data){
    //scan Academic.txt
//    fin.open(pathName + "Academic.txt");
//    if (!fin.is_open()){
//        ofstream fout;
//        fout.open(pathName+"Academic.txt");
//        data.numOfYears = 0;                //neu ma ko co Academic.txt thi ko co du lieu year->=0
//        fout.close();
//    }else{
//        fin>>data.numOfYears;
//        for(int i=1; i <= data.numOfYears; i++){
//            //create tmp = new Year -> add tmp;
//            //Year *cur = pYear;
//        }
//
//        fin.close();
//    }
    //scan Student.txt
    fin.open(pathName + "Students.txt");
    if (!fin.is_open()){
        ofstream fout;
        fout.open(pathName+"Students.txt");
        data.numOfClasses = 0;
        fout.close();
    }else{               
        fin>>data.numOfClasses;
        for(int i=1; i <= data.numOfClasses; i++){
            Class *tmpClass = new Class;
            tmpClass->next = NULL;
            tmpClass->pHeadStudent = NULL;
            fin.ignore(256,'\n');
            getline(fin, tmpClass->name);
            parseString(tmpClass->name);
            fin>>tmpClass->numOfStudents;     
            for(int j=1; j<=tmpClass->numOfStudents; j++){
                Student *tmpSt = new Student;
                tmpSt->next = NULL;
                tmpSt->pCourseManager = NULL;
                fin>>tmpSt->id;
                fin.ignore(256,'\n');
                getline(fin, tmpSt->lastName); 
                getline(fin, tmpSt->firstName);
                getline(fin, tmpSt->gender);
                getline(fin, tmpSt->dOB);
                getline(fin, tmpSt->hashPassword);
                fin>>tmpSt->numOfCourse;
                //link Course of semester of year here;
                
                if (tmpClass->pHeadStudent==NULL){
                    tmpClass->pHeadStudent = tmpClass->pTailStudent = tmpSt;
                }else{
                    tmpClass->pTailStudent->next = tmpSt;
                    tmpClass->pTailStudent = tmpSt;
                }
            }
            if (data.pHeadClass == NULL){
                data.pHeadClass = data.pTailClass = tmpClass;
            }else{
                data.pTailClass->next = tmpClass;
                data.pTailClass = tmpClass;
            }
        }
        
        fin.close();
    }
}
void saveToDataBase(string pathName, CoreData data){
    ofstream fout;
    fout.open(pathName + "st.txt");
    fout<<data.numOfClasses<<endl;
    Class *curClass = data.pHeadClass;
    while (data.numOfClasses--){
        fout<<curClass->name<<endl;
        parseString(curClass->name);
        fout<<curClass->numOfStudents<<endl;
        Student *curSt = curClass->pHeadStudent;
        while (curClass->numOfStudents-- ){
            fout<<curSt->id<<endl;
            fout<<curSt->lastName<<endl;
            fout<<curSt->firstName<<endl;
            fout<<curSt->gender<<endl;
            fout<<curSt->dOB<<endl;
            fout<<curSt->hashPassword<<endl;
            fout<<curSt->numOfCourse<<endl;
            while (curSt->numOfCourse--){
                //
            }
            curSt = curSt->next;
        }
        curClass = curClass->next;
    }
    fout.close();
}
Student *findStudent(long long id, CoreData data){
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
                return curStudent;
            }
            curClass = curClass->next;
        }
    }
    return NULL;
}
void removeStudent(long long id, CoreData &data){
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
                    deallocatedStudent(preStudent);
                }else{
                    if (curStudent->next==NULL) curClass->pTailStudent = preStudent; //remove at ptail
                    preStudent->next = curStudent->next;
                    deallocatedStudent(curStudent);
                }
            }
            curClass = curClass->next;
        }
    }
}
void deallocatedStudent(Student *&st){
    while (st->numOfCourse--){
        //deallocate *year
    }
    delete st;
}
void addStudentToClass(Class *&pClass, Student *& tmpSt){
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
    while (cur != NULL && cur->next->id < tmpSt->id){
        cur = cur->next;
    }
    tmpSt->next = cur->next;
    cur->next = tmpSt;
    
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
}

void parseString(string &s){
    while (s.length() && s[0]==' ') s.erase(0,1);
    while (s.length() && s[s.length()-1]==' ') s.erase(s.length()-1,1);
}
