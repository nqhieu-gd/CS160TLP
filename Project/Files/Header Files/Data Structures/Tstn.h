#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

using std::string;

struct Date{
    int day;
    int month;
    int year;
};

struct Transaction{
    long long amount;
    Date date;
    string description;

    Transaction(): amount(0) {
        date.day = 0;
        date.month = 0;
        date.year = 0;
    };
};

bool ExamineDate(const Date&);

Date inputDate();

Transaction ipt();

bool CheckvalidDate(const Date&); // Only check if it's a valid Date or not - don't care about the current Date

void inputTransactionFromFile(std::ifstream&, Transaction&); //Date->Amount->size of string ->Note

void outputTransactiontoFile(std::ofstream&,const Transaction&);

bool CompareDate(const Date& a, const Date& b); // 1: a>b; -1: a<b; 0: a=b
//Sort via Date -> Calculate and Statistic

Date GetCurrDate(); //Get Current Date :))