#include <iostream>
#include <fstream>
#include "..\Wallet Info\Transaction\Tstn.h"
#include "Cate.h"
using namespace std;

ExpenseCategory :: ExpenseCategory(): eID(""), eName("") {}

ExpenseCategory :: ExpenseCategory(string ID): eID(""), eName("") {
    exp.alloc();
    eID = ID;
    std::cout << "Enter a new expense category: ";
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