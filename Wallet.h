#pragma once
#include <fstream>
#include "Transaction.h"
#include "Dynamicarray.h"

using std::string;

struct Wallet{
    string ID;
    string Name;
    int quantity=0;
    Transaction* List=nullptr;
};

void addTransaction(Wallet&, Transaction&);

struct Wallet {
    string wID;
    string wName;
    int income;
    int expense;

    func<Transaction> inc;
    func<Transaction> exp;

    //create a new wallet
    void creallet() {
        inc.alloc();
        exp.alloc();
    }

    void incomeAdd(Transaction t) {
        inc.push(t);
    }

    void expenseAdd(Transaction t) {
        exp.push(t);
    }

    void totalIncome() {
        for (int i = 0; i < inc.store; i++) {
            income += inc.p[i].amount;
        }
    }

    void totalExpense() {
        for (int i = 0; i < exp.store; i++) {
            expense += exp.p[i].amount;
        }
    }

    //clear the current wallet's data
    void cleallet() {
        inc.dealloc();
        exp.dealloc();
    }
};

struct Wallist {
    func<Wallet> w;

    //create a new list of wallets
    void crealist() {
        w.alloc();
    }

    //clear list of wallets
    void clist() {
        for (int i = 0; i < w.store; i++) {
            w.p[i].cleallet();
        }
        w.dealloc();
    }
};