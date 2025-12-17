#include <iostream>
#include <fstream>
#include <string>
#include "..\Wallet Info\Transaction\Tstn.h"
#include "Cate.h"
using namespace std;

ExpenseCategory :: ExpenseCategory(string ID): eID(""), eName("") {
    exp.alloc();
    string sub = " ";
    for (int i = 0; i < ID.size(); i++) {
        sub[0] = ID[i];
        eID += sub;
    }
    std::cout << "Enter a new expense category: ";
    std::getline(std::cin, eName);
}

ExpenseCategory :: ~ExpenseCategory() {
    exp.dealloc();
}

long long ExpenseCategory :: expense() {
    long long a = 0;
    for (int i = 0; i < exp.store; i++) {
        a += exp.p[i].amount;
    }
    return a;
}