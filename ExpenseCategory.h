#pragma once
#include <fstream>
#include <string>
#include "Transaction.h"
#include "Dynamicarray.h"

using std::string;

struct ExpenseCategory {
    string eID;
    string eName;
    func<Transaction> exp;
    long long expense;

    //create expense category list
    void crexpegory();

    void expAdd();

    void expSub();

    //clear expense category list
    void clexpegory();
};