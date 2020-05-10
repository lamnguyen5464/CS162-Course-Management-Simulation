 
#include <iostream>
#include "Data.hpp"
using namespace std;
CoreData data;
const string pathName = "/Users/lforestor/Dev/CS/162/Project/Project/Project/";
int main() {
    importDataBase(pathName, data);
    Student *curSt;
    Class *curClass;
    Course *newCourse;
    Semester *curSem;
    
    showCourse(data);
    cout<<"_______________"<<endl;
    if (findCourse("19_20", "HK1", "CM", newCourse, data)){
        if (removeStudent(7, data)){
            cout<<"Remove "<<7<<" successfully"<<endl;
        }else{
            cout<<"Could not find "<<7<<" in database"<<endl;
        }
    }
//
    showCourse(data);
//    showDataStudent(data);
//    saveToDataBase(pathName, data);
    return 0;
}
