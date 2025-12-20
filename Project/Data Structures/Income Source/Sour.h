#pragma once
#include <fstream>
#include <string>
#include "..\\Wallet Info\\Transaction\\Tstn.h"
#include "..\\..\\Utilities\\DA\\Dynamicarray.h"
#include "..\Wallet Info\Transaction\Auto_Trtn.h"

using std::string;

struct IncomeSource {
    Auto_Transaction_List i_atm;
    string iID;
    string iName;
    func<Transaction> inc;
    
    long long income();

    //create income source list.
    IncomeSource();
    //create income source list with a specific ID.
    IncomeSource(string ID);
    ~IncomeSource();
};
