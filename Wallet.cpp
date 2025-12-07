#include <iostream>
#include <fstream>
#include <string>
#include "Transaction.h"
#include "Wallet.h"
#include "Dynamicarray.h"

using std::string;

long long income;
long long expense;

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
    income = 0;
    for (int i = 0; i < inc.store; i++) {
        income += inc.p[i].amount;
    }
}

void totalExpense() {
    expense = 0;
    for (int i = 0; i < exp.store; i++) {
        expense += exp.p[i].amount;
    }
}

//clear the current wallet's data
void cleallet() {
    inc.dealloc();
    exp.dealloc();
}