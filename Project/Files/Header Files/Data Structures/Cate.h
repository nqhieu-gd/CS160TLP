#pragma once
#include <fstream>
#include <string>
#include "Tstn.h"
#include "Auto_Trtn.h"
#include "../../Utilities/DA/Dynamicarray.h"

using std::string;

struct ExpenseCategory {
    Auto_Transaction_List e_atm;
    string eID;
    string eName;
    func<Transaction> exp;
    
    long long expense();

    //create expense category list.
    ExpenseCategory();
    //create expense category list with a specific ID.
    ExpenseCategory(string ID);
    ~ExpenseCategory();

    void eRename(string name);
};