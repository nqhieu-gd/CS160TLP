#pragma once
#include <fstream>
#include "Transaction\Tstn.h"
#include "..\..\Utilities\DA\Dynamicarray.h"
#include "..\Income Source\Sour.cpp"
#include "..\Expense Category\Cate.cpp"

using std::string;

struct Wallet {
    string wID;
    string wName;

    func<IncomeSource> is;
    func<ExpenseCategory> ec;

    int totalBalance();

    Wallet();
    ~Wallet();

    void outWal();

    void newSource(IncomeSource &ie, const string ID);
    
    void newExpense(ExpenseCategory &et, const string ID);

    void incomeAdd(const Transaction t, const string ID);

    void expenseAdd(const Transaction t, const string ID);

    void rename();
};

struct Wallist {
    func<Wallet> w;

    Wallist();
    ~Wallist();

    void CreateWallet();
};