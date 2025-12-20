#include <iostream>
#include <fstream>
#include "../Wallet Info/Transaction/Tstn.h"
#include "../Wallet Info/Transaction/Auto_Trtn.h"
#include "Sour.h"
using namespace std;

IncomeSource :: IncomeSource(): iID("00000000"), iName("") {
    inc.alloc();
}

IncomeSource :: IncomeSource(string ID): iID(ID), iName("") {
    inc.alloc();
    std::cout << "Enter a new income source: ";
    if (cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, iName);
}

IncomeSource :: ~IncomeSource() {}

long long IncomeSource :: income() {
    long long a = 0;
    for (int i = 0; i < inc.store; i++) {
        a += inc.p[i].amount;
    }
    return a;
}