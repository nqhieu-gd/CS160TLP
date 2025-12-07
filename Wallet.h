#pragma once
#include <fstream>
#include "Transaction.h"
#include "Dynamicarray.h"

using std::string;

struct Wallet {
    string wID;
    string wName;
    long long income;
    long long expense;

    func<Transaction> inc;
    func<Transaction> exp;

    void creallet();

    void incomeAdd(Transaction t);

    void expenseAdd(Transaction t);

    void totalIncome();

    void totalExpense();

    void cleallet();
};

struct Wallist {
    func<Wallet> w;

    void crealist();

    void clist();
};

void addTransaction(Wallet&, Transaction&);