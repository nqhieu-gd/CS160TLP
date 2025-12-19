#pragma once
#include <fstream>
#include "Transaction\Tstn.h"
#include "..\\..\\Utilities\\DA\\Dynamicarray.h"
#include "..\\Income Source\\Sour.h"
#include "..\\Expense Category\\Cate.h"
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

    void outWallist();

    void CreateWallet();

    bool inWal(string id);

    void outSC();

    void delWal(int x);
};