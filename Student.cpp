//
//  Student.cpp
//  Project
//
//  Created by Lam Nguyen on 5/14/20.
//  Copyright © 2020 Lam Nguyen. All rights reserved.
//

#include "Student.hpp"
#include "Data.hpp"
#include <iostream>
#include <iomanip>

void viewCheckInResult(Student *me){
    CourseManager *cur;
    bool showOption = true;
    int cnt = 0;
    while (1){
        if (showOption){
            cout<<"     All your courses:"<<endl;
            cur = me->pHeadCourseManager;
            cnt = 0;
            while (cur != NULL){
                cout<<"     "<<++cnt<<") "<<cur->pCourse->name<<endl;
                cur = cur->next;
            }
            cout<<"     "<<0<<") Return"<<endl;
        }else{
            cout<<"Invalid choice! Try again"<<endl;
            showOption = true;
        }
        int yourChoice;
        cout<<"     >Your choice: ";
        cin>>yourChoice;
        if (!yourChoice) return;
        if (0 < yourChoice && yourChoice <= cnt){
            cnt = yourChoice;
            break;
        }else
            showOption = false;
    }
    cur = me->pHeadCourseManager;
    cnt--;
    while (cnt--)
        cur = cur->next;
    //show checkIn
    cout<<"         "<<cur->pCourse->name<<" check-in result of "<<me->lastName<<" "<<me->firstName<<""<<endl;
    //title
    cout<<"         |";
    for(int i=1; i<=11; i++) cout<<" ";
    cout<<"DATE";
    for(int i=1; i<=11; i++) cout<<" ";
    cout<<"|";
    for(int i=1; i<=2; i++) cout<<" ";
    cout<<"STATUS";
    for(int i=1; i<=2; i++) cout<<" ";
    cout<<"|"<<endl;
    cout<<"         |"; for(int i=1; i<=37; i++) cout<<"-"; cout<<"|"<<endl;
    CheckInCell *tmpCell = cur->checkIn.pHeadCell;
    while (tmpCell != NULL){
        TimeInfo tmp;
        tmp.constructor(tmpCell->startTime);
        string tmpString = to_string(tmp.date) + "/" + to_string(tmp.month) + "/" + to_string(tmp.year);
        cout<<"         |"<<setw(18)<<tmpString;
        for(int i=1; i<=8; i++) cout<<" ";
        cout<<"|";
        tmpString = (tmpCell->checked) ? "joined" : "not joined";
        cout<<setw(10)<<tmpString<<"|"<<endl;
        tmpCell = tmpCell->next;
    } 
    cout<<"         Enter any key to back: ";
    string tmp;
    cin>>tmp;

}
void checkInt(Student *me){
    CourseManager *cur;
    bool showOption = true;
    int cnt = 0;
    while (1){
        if (showOption){
            cout<<"     All your courses:"<<endl;
            cur = me->pHeadCourseManager;
            cnt = 0;
            while (cur != NULL){
                cout<<"     "<<++cnt<<") "<<cur->pCourse->name<<endl;
                cur = cur->next;
            }
            cout<<"     "<<0<<") Return"<<endl;
        }else{
            cout<<"Invalid choice! Try again"<<endl;
            showOption = true;
        }
        int yourChoice;
        cout<<"     >Your choice: ";
        cin>>yourChoice;
        if (!yourChoice) return;
        if (0 < yourChoice && yourChoice <= cnt){
            cnt = yourChoice;
            break;
        }else
            showOption = false;
    }
    cur = me->pHeadCourseManager;
    cnt--;
    while (cnt--)
        cur = cur->next;
    //Check-in
    CheckInCell *tmpCell = cur->checkIn.pHeadCell;
    TimeInfo current;
    current.setDate("12/5/2020");
    current.setTime("8:00");
    while (tmpCell != NULL){
        if (tmpCell->startTime <= current.getTimeCode() && current.getTimeCode() <= tmpCell->endTime){
            cout<<"         Check-in successfully!"<<endl;
            tmpCell->checked = true;
            break;
        }
        tmpCell = tmpCell->next;
    }

    
    //show checkIn
    cout<<"         "<<cur->pCourse->name<<" check-in result of "<<me->lastName<<" "<<me->firstName<<""<<endl;
    //title
    cout<<"         |";
    for(int i=1; i<=11; i++) cout<<" ";
    cout<<"DATE";
    for(int i=1; i<=11; i++) cout<<" ";
    cout<<"|";
    for(int i=1; i<=2; i++) cout<<" ";
    cout<<"STATUS";
    for(int i=1; i<=2; i++) cout<<" ";
    cout<<"|"<<endl;
    cout<<"         |"; for(int i=1; i<=37; i++) cout<<"-"; cout<<"|"<<endl;
    tmpCell = cur->checkIn.pHeadCell;
    while (tmpCell != NULL){
        TimeInfo tmp;
        tmp.constructor(tmpCell->startTime);
        string tmpString = to_string(tmp.date) + "/" + to_string(tmp.month) + "/" + to_string(tmp.year);
        cout<<"         |"<<setw(18)<<tmpString;
        for(int i=1; i<=8; i++) cout<<" ";
        cout<<"|";
        tmpString = (tmpCell->checked) ? "joined" : "not joined";
        cout<<setw(10)<<tmpString<<"|"<<endl;
        tmpCell = tmpCell->next;
    }
    cout<<"         Enter any key to back and save: ";
    string tmp;
    cin>>tmp;
    cout<<endl;
}
void viewScore(Student *me){
    CourseManager *cur;
    bool showOption = true;
    int cnt = 0;
    while (1){
        if (showOption){
            cout<<"     All your courses:"<<endl;
            cur = me->pHeadCourseManager;
            cnt = 0;
            while (cur != NULL){
                cout<<"     "<<++cnt<<") "<<cur->pCourse->name<<endl;
                cur = cur->next;
            }
            cout<<"     "<<0<<") Return"<<endl;
        }else{
            cout<<"Invalid choice! Try again"<<endl;
            showOption = true;
        }
        int yourChoice;
        cout<<"     >Your choice: ";
        cin>>yourChoice;
        if (!yourChoice) return;
        if (0 < yourChoice && yourChoice <= cnt){
            cnt = yourChoice;
            break;
        }else
            showOption = false;
    }
    cur = me->pHeadCourseManager;
    cnt--;
    while (cnt--)
        cur = cur->next;
    //show score
    cout<<"         Mid  : ";
    if (cur->scoreBoard.midTerm != -1){
        cout<<setprecision(2)<<cur->scoreBoard.midTerm<<endl;
    }else{
        cout<<"is not existing!"<<endl;
    }
    cout<<"         Final: ";
    if (cur->scoreBoard.finalTerm != -1){
        cout<<setprecision(2)<<cur->scoreBoard.finalTerm<<endl;
    }else{
        cout<<"is not existing!"<<endl;
    }
    cout<<"         Lab  : ";
    if (cur->scoreBoard.lab != -1){
        cout<<setprecision(2)<<cur->scoreBoard.lab<<endl;
    }else{
        cout<<"is not existing!"<<endl;
    }
    cout<<"         Bonus: ";
    if (cur->scoreBoard.bonus != -1){
        cout<<setprecision(2)<<cur->scoreBoard.bonus<<endl;
    }else{
        cout<<"is not existing!"<<endl;
    }
    cout<<"         Enter any key to back: ";
    string tmp;
    cin>>tmp;

}
void viewSchedule(Student *me){
    CourseManager *cur = me->pHeadCourseManager;
    int cnt = 0;
    //count total of day
    while (cur != NULL){
        cnt += cur->checkIn.numOfDays;
        cur = cur->next;
    }
    CheckInCell *buffer = new CheckInCell[cnt+1];
    cur = me->pHeadCourseManager;
    cnt = 0;
    while (cur != NULL){
        CheckInCell *tmp = cur->checkIn.pHeadCell;
        while (tmp != NULL){
            buffer[cnt].idCourse = cur->pCourse->id;
            buffer[cnt].startTime = tmp->startTime;
            buffer[cnt].endTime = tmp->endTime;
            cnt++;
            tmp = tmp->next;
        }
        cur = cur->next;
    }
    //sort startTime increasing order
    for(int i = 0; i < cnt; i++)
        for(int j = i+1; j < cnt; j++)
            if (buffer[i].startTime > buffer[j].startTime)
                swap(buffer[i], buffer[j]);
    //show schedule
    TimeInfo curDay;
    curDay.constructor(buffer[0].startTime);
    curDay.setTime("23:59");
    int index = 0;
    cout<<"     Your schedule: "<<endl;
    string date = to_string(curDay.date)+"/"+to_string(curDay.month)+"/"+to_string(curDay.year);
    cout<<"     "<<getStringDayFromInt(getDayOfWeek(curDay.date, curDay.month, curDay.year))<<" - "<<date<<": "<<endl;
    while (index < cnt){
        if (buffer[index].startTime > curDay.getTimeCode()){
            curDay.constructor(buffer[index].startTime);
            curDay.setTime("23:59");
            string date = to_string(curDay.date)+"/"+to_string(curDay.month)+"/"+to_string(curDay.year);
            cout<<"     "<<getStringDayFromInt(getDayOfWeek(curDay.date, curDay.month, curDay.year))<<" - "<<date<<": "<<endl;
        }
        TimeInfo tmp;
        tmp.constructor(buffer[index].startTime);
        cout<<"                "<<tmp.hour<<":"<<tmp.minnute;
        tmp.constructor(buffer[index].endTime);
        cout<<" - "<<tmp.hour<<":"<<tmp.minnute<<" | "<<buffer[index].idCourse<<endl;
        index++;
    }
}
void menuStudent(Student *me, CoreData &data, string pathName){
    bool showOption = true;
    while (1){
        if (showOption){
            cout<<"____________________MENU_STUDENT____________________"<<endl;
            cout<<"1) Check-in"<<endl;
            cout<<"2) View check-in result"<<endl;
            cout<<"3) View scheules"<<endl;
            cout<<"4) View your score"<<endl;
            cout<<"0) Return"<<endl;

        }else{
            cout<<"Invalid choice! Try again"<<endl;
            showOption = true;
        }
        int yourChoice;
        cout<<">Your choice: ";
        cin>>yourChoice;
        switch (yourChoice) {
            case 1:
                checkInt(me);
                saveToDataBase(pathName, data);
                break;
            case 2:
                viewCheckInResult(me);
                break;
            case 3:
                viewSchedule(me);
                break;
            case 4:
                viewScore(me);
                break;
            case 0:
                return;
            default:
                showOption = false;
                break;
        }
    }

}
