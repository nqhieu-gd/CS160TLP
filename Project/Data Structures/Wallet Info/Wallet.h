#pragma once
#include <fstream>
#include "Transaction\Tstn.h"
#include "..\\..\\Utilities\\DA\\Dynamicarray.h"
#include "..\\Income Source\\Sour.cpp"
#include "..\\Expense Category\\Cate.cpp"
#include "..\\..\\Utilities\\Hashmap\\HashMap.h"
#include "..\\..\\Utilities\\Uppercase\\Uppercase.h"

using std::string;

struct Wallet {
    string wID;
    string wName;

    func<IncomeSource> is;
    func<ExpenseCategory> ec;

    long long totalBalance();

    Wallet();
    ~Wallet();

    void outWal();

    string convertNameInc(string name);

    string convertNameExp(string name);

    void incomeAdd(const Transaction t, const string ID);

    void expenseAdd(const Transaction t, const string ID);

    void rename();
};

struct Wallist {
    func<Wallet> w;
    HashMap isource();
    HashMap ecategory();

    Wallist();
    ~Wallist();

    void CreateWallet();

    void inWal(string id);
};