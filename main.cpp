 
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
    if (findSemester("19_20", "HK1", curSem, data) && findCourse("MTH1", curSem, newCourse, data)){
        removeCourse(curSem, newCourse);
    }
//
    showCourse(data);
//    showDataStudent(data);
//    saveToDataBase(pathName, data);
    return 0;
}
