//
//  Data.cpp
//  Project
//
//  Created by Lam Nguyen on 4/18/20.
//  Copyright © 2020 Lam Nguyen. All rights reserved.
//
#include <fstream>
#include "Data.hpp"
using namespace std;
ifstream fin;
void importDataBase(string pathName, CoreData &data){
    //scan Academic.txt
    fin.open(pathName + "Academic.txt");
    if (!fin.is_open()){
        ofstream fout;
        fout.open(pathName+"Academic.txt");
        data.numOfYears = 0;                //neu ma ko co Academic.txt thi ko co du lieu year->=0
        fout.close();
    }else{
        fin>>data.numOfYears;
        for(int i=1; i <= data.numOfYears; i++){
            //create tmp = new Year -> add tmp;
            //Year *cur = pYear;
        }
        
        fin.close();
    }
    //Student.txt
    fin.open(pathName + "Students.txt");
    if (!fin.is_open()){
        ofstream fout;
        fout.open(pathName+"Students.txt");
        data.numOfClasses = 0;
        fout.close();
    }else{
        fin>>data.numOfClasses;
        for(int i=1; i <= data.numOfClasses; i++){
            //create new Class;
            //read Student
            //Course student
        }
        
        fin.close();
    }
    

}
