#include <iostream>
#include <fstream>
#include "..\\Wallet Info\\Transaction\\Tstn.h"
#include "Cate.h"
using namespace std;

ExpenseCategory :: ExpenseCategory(): eID("00000000"), eName("") {
    exp.alloc();
}

ExpenseCategory :: ExpenseCategory(string ID): eID(ID), eName("") {
    exp.alloc();
    std::cout << "Enter a new expense category: ";
    if (cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, eName);
}

ExpenseCategory :: ~ExpenseCategory() {}

long long ExpenseCategory :: expense() {
    long long a = 0;
    for (int i = 0; i < exp.store; i++) {
        a += exp.p[i].amount;
    }
    return a;
}