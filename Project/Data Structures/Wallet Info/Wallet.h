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
    long long bal;

    func<IncomeSource> is;
    func<ExpenseCategory> ec;

    void creallet();

    void incomeAdd(Transaction t);

    void expenseAdd(Transaction t);

    void totalBalance();

    void cleallet();
};

struct Wallist {
    func<Wallet> w;

    void crealist();

    void clist();
};

void addTransaction(Wallet&, Transaction&);