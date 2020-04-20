 
#include <iostream>
#include "Data.hpp"

using namespace std;
CoreData data;
const string pathName = "/Users/lforestor/Dev/CS/162/Project/Project/Project/"; 
int main() {
    importDataBase(pathName, data);
    removeStudent(3, data);
    saveToDataBase(pathName, data); 
    return 0;
}
