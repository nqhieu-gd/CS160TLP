#pragma once
#include <fstream>
#include <string>
#include "Tstn.h"
#include "Auto_Trtn.h"
#include "../../Utilities/DA/Dynamicarray.h"

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

    void iRename(string name);
};
