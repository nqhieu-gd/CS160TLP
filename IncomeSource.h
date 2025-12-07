#pragma once
#include <fstream>
#include <string>
#include "Transaction.h"
#include "Dynamicarray.h"

using std::string;

struct IncomeSource {
    string iID;
    string iName;
    func<Transaction> inc;
    long long income;

    //create income source list
    void crincourse();

    void incAdd();

    void incSub();

    //clear income source list
    void clincourse();
};
