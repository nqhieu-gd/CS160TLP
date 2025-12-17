#include <iostream>
#include <fstream>
#include "..\Wallet Info\Transaction\Tstn.h"
#include "Sour.h"
using namespace std;

IncomeSource :: IncomeSource(): iID(""), iName("") {}

IncomeSource :: IncomeSource(string ID): iID(""), iName("") {
    inc.alloc();
    iID = ID;
    std::cout << "Enter a new expense category: ";
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