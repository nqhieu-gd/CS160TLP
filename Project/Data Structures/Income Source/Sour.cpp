#include <iostream>
#include <fstream>
#include <string>
#include "..\Wallet Info\Transaction\Tstn.h"
#include "Sour.h"
using namespace std;

IncomeSource :: IncomeSource(string ID): iID(""), iName("") {
    inc.alloc();
    string sub = " ";
    for (int i = 0; i < ID.size(); i++) {
        sub[0] = ID[i];
        iID += sub;
    }
    std::cout << "Enter a new expense category: ";
    std::getline(std::cin, iName);
}

IncomeSource :: ~IncomeSource() {
    inc.dealloc();
}

long long IncomeSource :: income() {
    long long a = 0;
    for (int i = 0; i < inc.store; i++) {
        a += inc.p[i].amount;
    }
    return a;
}