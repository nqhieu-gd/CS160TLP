#pragma once
#include <iostream>
#include <fstream>
#include <string>

struct Date{
    int day;
    int month;
    int year;
};

struct Transaction{
    long long amount;
    Date date;
    std::string description;
};

bool CheckvalidDate(const Date&); // Only check if it's a valid Date or not - don't care about the current Date
void inputTransactionFromFile(std::ifstream&,Transaction&); //Date->Amount->size of string ->Note
void outputTransactiontoFile(std::ofstream&,const Transaction&);
int CompareTransaction(const Transaction& a, const Transaction& b); //Sort via Date -> Calculate and Statistic