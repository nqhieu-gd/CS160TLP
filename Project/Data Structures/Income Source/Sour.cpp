#include <iostream>
#include <fstream>
#include "Sour.h"
using namespace std;

IncomeSource :: IncomeSource(): iID("00000000"), iName("") {
    inc.alloc();
}

IncomeSource :: IncomeSource(string ID): iID(ID), iName("") {
    inc.alloc();
}

IncomeSource :: ~IncomeSource() {}

long long IncomeSource :: income() {
    long long a = 0;
    for (int i = 0; i < inc.store; i++) {
        a += inc.p[i].amount;
    }
    return a;
}

void IncomeSource :: iRename(string name) {
    iName = name;
}