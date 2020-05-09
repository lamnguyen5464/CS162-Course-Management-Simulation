#ifndef FUNCTION_QHUY_H_INCLUDED
#define FUNCTION_QHUY_H_INCLUDED

//academic staff-class;
void staffClassMenu (CoreData &data);

void importStudentFromCsvFile (CoreData &data);

void edit(Student *&tmpSt,int choice);
void editAnExistingStudent ( CoreData &data);

void viewListOfClasses(CoreData data);
void viewListOfStudents(CoreData data);
#endif // FUNCTION_QHUY_H_INCLUDED
