 
#include <iostream>
#include <ctime>
#include "Data.hpp"
#include "Course.h" 
#include "Student.hpp"
#include "class.h"
using namespace std;
CoreData data;
const string pathName = "/Users/lforestor/Dev/CS/162/Project/Project/Project/Database/";
int main() {
    importDataBase(pathName, data);

    staffClassMenu(pathName, data);
////    showCourse(data);
    menuCourse(pathName, data);
//    showDataStudent(data);
////
    Student *st;
    Class *tmpClass;
    if (findStudent(19125001, data, st, tmpClass)){
        menuStudent(st, data, pathName);
    }
//
         saveToDataBase(pathName, data);
    return 0;
}
