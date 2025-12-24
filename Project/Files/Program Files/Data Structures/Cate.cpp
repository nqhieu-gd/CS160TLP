#include <iostream>
#include <fstream>
#include "../../Header Files/Data Structures/Cate.h"
using namespace std;

ExpenseCategory :: ExpenseCategory(): eID("00000000"), eName("") {
    exp.alloc();
}

ExpenseCategory :: ExpenseCategory(string ID): eID(ID), eName("") {
    exp.alloc();
}

ExpenseCategory :: ~ExpenseCategory() {
    exp.dealloc();
    e_atm.clear();
}

long long ExpenseCategory :: expense() {
    long long a = 0;
    for (int i = 0; i < exp.store; i++) {
        a += exp.p[i].amount;
    }
    return a;
}

void ExpenseCategory :: eRename(string name) {
    eName = name;
}