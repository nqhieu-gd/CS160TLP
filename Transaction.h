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
    int amount;
    Date date;
    std::string description;
};

bool CheckvalidDate(Date);
void inputTransactionFromConsole(Transaction&);
void inputTransactionFromFile(std::ifstream&,Transaction&);
void outputTransactiontoFile(std::ofstream&,Transaction);