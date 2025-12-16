#pragma once
#include <fstream>
#include <string>
#include "..\Wallet Info\Transaction\Tstn.h"
#include "..\..\Utilities\DA\Dynamicarray.h"

using std::string;

struct IncomeSource {
    string iID;
    string iName;
    func<Transaction> inc;
    
    long long income();

    //create income source list
    IncomeSource();
    //clear income source list
    ~IncomeSource();

    void incAdd();

    void incSub();
};
