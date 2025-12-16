#include <iostream>
#include <fstream>
#include <string>
#include "Wallet.h"
#include "..\..\Utilities\DA\Dynamicarray.h"

using std::string;

//create a new wallet
Wallet :: Wallet() {
    is.alloc();
    ec.alloc();
}

void Wallet :: newSource(IncomeSource &ie, const string ID) {
    std::cout << "Enter a new income source: ";
    std::getline(std::cin, ie.iName);
}

void Wallet :: newExpense(ExpenseCategory &et, const string ID) {
    std::cout << "Enter a new expense category: ";
    std::getline(std::cin, et.eName);
}

//Add an income, if the source ID has already presented in is (list of income sources),
//add t to that ID, else create a new ID name.
void Wallet :: incomeAdd(const Transaction t, const string ID) {
    for (int i = 0; i < is.store; i++) {
        if (ID == is.p[i].iID) is.p[i].inc.push(t);
        return;
    }
    IncomeSource ie;
    string sub = " ";
    for (int i = 0; i < ID.size(); i++) {
        sub[0] = ID[i];
        ie.iID += sub;
    }
    newSource(ie, ID);
    ie.income = t.amount;
    ie.inc.push(t);
    is.push(ie);
}

//Add an expense, if the category ID has already presented in ec (list of expense categories),
//add t to that ID, else create a new ID name.
void Wallet :: expenseAdd(const Transaction t, const string ID) {
    for (int i = 0; i < ec.store; i++) {
        if (ID == ec.p[i].eID) ec.p[i].exp.push(t);
        return;
    }
    ExpenseCategory et;
    string sub = " ";
    for (int i = 0; i < ID.size(); i++) {
        sub[0] = ID[i];
        et.eID += sub;
    }
    newExpense(et, ID);
    et.expense = t.amount;
    et.exp.push(t);
    ec.push(et);
}

//Calculate the current wallet's total balance (total income minus total expense),
//can be negative, automatically update for each changes in wallet.
int Wallet :: totalBalance() {
    long long c = 0;
    for (int i = 0; i < is.store; i++) {
        c += is.p[i].income;
    }
    for (int i = 0; i < ec.store; i++) {
        c -= ec.p[i].expense;
    }
    return c;
}

//Clear the current wallet's data
Wallet :: ~Wallet() {
    for (int i = 0; i < is.store; i++) {
        is.p[i].inc.dealloc();
    }
    for (int i = 0; i < ec.store; i++) {
        ec.p[i].exp.dealloc();
    }
    is.dealloc();
    ec.dealloc();
}