#pragma once
#include <fstream>
#include <string>
#include "../Wallet Info/Transaction/Tstn.h"
#include "../Wallet Info/Monthly Record/MonthlyRecord.h"
#include "../Wallet Info/Transaction/Auto_Trtn.h"
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
};