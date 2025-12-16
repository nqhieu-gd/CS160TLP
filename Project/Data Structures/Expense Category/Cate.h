#pragma once
#include <fstream>
#include <string>
#include "..\Wallet Info\Transaction\Tstn.h"
#include "..\..\Utilities\DA\Dynamicarray.h"

using std::string;

struct ExpenseCategory {
    string eID;
    string eName;
    func<Transaction> exp;
    
    long long expense();

    //create expense category list
    ExpenseCategory();
    //clear expense category list
    ~ExpenseCategory();

    void expAdd();

    void expSub();
};