//
//  Student.hpp
//  Project
//
//  Created by Lam Nguyen on 5/14/20.
//  Copyright © 2020 Lam Nguyen. All rights reserved.
//

#ifndef Student_hpp
#define Student_hpp

#include <stdio.h>
#include "Data.hpp"
void menuStudent(Student *me, CoreData &data, string pathName);
void viewCheckInResult(Student *me);
void checkInt(Student *me);
void viewSchedule(Student *me);
void viewScore(Student *me);
#endif /* Student_hpp */
