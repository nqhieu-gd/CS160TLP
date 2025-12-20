#pragma once
#include <fstream>
#include "Monthly Record/MonthlyRecord.h"
#include "Transaction/Tstn.h"
#include "../Income Source/Sour.h"
#include "../Expense Category/Cate.h"
#include "../../Utilities/DA/Dynamicarray.h"
#include "../../Utilities/Hashmap/HashMap.h"
#include "../../Utilities/Uppercase/Uppercase.h"

using std::string;

struct Wallet {
    string wID;
    string wName;

    //List of income sources and their transaction.
    func<IncomeSource> is;
    //List of expense categories and their transaction.
    func<ExpenseCategory> ec;
    //Each month's statistic.
    func<Monthly> Statistic;

    //Current balance of this wallet, accounting for all transaction since the beginning.
    long long curBalance();

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