#ifndef FUNCTION_QHUY_H_INCLUDED
#define FUNCTION_QHUY_H_INCLUDED

//academic staff-class;
void staffClassMenu (CoreData &data);

void inputStudentFromFile(Student *tmpSt,Class *&tmpClass,ifstream &fin);
void importStudentFromCsvFile (CoreData &data);

void addAStudent(CoreData &data);

void removeAStudent(CoreData &data);

void copyStudentInfor(Student *&dup,Student *tmpSt);
void moveStudentFromAToB (CoreData &data);

void edit(Student *&tmpSt,int choice,bool &checkChoice);
void editAnExistingStudent (CoreData &data);

void viewListOfClasses(CoreData data);
void viewListOfStudents(Class *curClass);
#endif // FUNCTION_QHUY_H_INCLUDED
