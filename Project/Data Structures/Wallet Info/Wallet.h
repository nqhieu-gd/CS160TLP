#pragma once
#include <fstream>
#include "Transaction/Tstn.h"
#include "../Income Source/Sour.h"
#include "../Expense Category/Cate.h"
#include "../../Utilities/DA/Dynamicarray.h"
#include "../../Utilities/Hashmap/HashMap.h"
#include "../../Utilities/Uppercase/Uppercase.h"

using std::string;

struct Wallet {
private:
    void incomeAdd(const Transaction t, const string ID);

    void expenseAdd(const Transaction t, const string ID);

public:
    string wID;
    string wName;

    //List of income sources and their transaction.
    func<IncomeSource> is;
    //List of expense categories and their transaction.
    func<ExpenseCategory> ec;

    //Current balance of this wallet, accounting for all transaction since the beginning.
    long long curBalance();

    Wallet();
    ~Wallet();

    void outWal();

    string convertNameInc(string name);

    void ISAdd(Transaction t, string name);

    void ECAdd(Transaction t, string name);

    bool editIS(int x, string name);

    bool editEC(int x, string name);

    bool delIS(int x);

    void delEC(int x);

    string convertNameExp(string name);

    void rename(string name);
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

    bool editWal(int x, string name);
};