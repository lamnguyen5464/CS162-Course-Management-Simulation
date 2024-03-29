#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

// clear screen
void clearScreen();
//academic staff-class;
void staffClassMenu (string pathname,CoreData &data);
void menuClass(Class *&tmpClass,CoreData data);
bool menuStudent(Class *&curClass,Student *&curSt,CoreData data);
//

void creatClassToImport(CoreData &data);
void inputStudentFromFile(Student *tmpSt,Class *&tmpClass,ifstream &fin,CoreData &data);
void importStudentFromCsvFile (CoreData &data,string pathname);
void getClassName(string &classname,string linkOfFile);

void inputGender(string &gender);
bool addAStudent(CoreData &data);

bool removeAStudent(CoreData &data);

void copyStudentInfor(Student *&dup,Student *tmpSt);
bool moveStudentFromAToB (CoreData &data);

void edit(Student *&tmpSt,int choice,bool &checkChoice);
bool editAnExistingStudent (CoreData &data);
bool editByMenu (CoreData &data);

void toUpper(string& str);
void findMaxLengthOfStudentInfo(Student *curSt,int &last,int &first,int &dob);
bool viewListOfStudents(Class *curClass,CoreData data);

//
void activity2_1(string pathname, CoreData &data);
void activity2_2(string pathname, CoreData &data);
void activity2_3(string pathname, CoreData &data);
void activity2_4(string pathname, CoreData &data);
void activity2_5(string pathname, CoreData &data);
void activity2_6(string pathname, CoreData &data);
#endif // FUNCTION_QHUY_H_INCLUDED
