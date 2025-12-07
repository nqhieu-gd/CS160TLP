#include <iostream>
#include <fstream>
#include <string>
#include "Transaction.h"
#include "Wallet.h"
#include "Dynamicarray.h"

using std::string;

long long bal;

IncomeSource ie;
ExpenseCategory ec;

func<IncomeSource> iep;
func<ExpenseCategory> ecp;

//create a new wallet
void creallet() {
    iep.alloc();
    ie.inc.alloc();
    ecp.alloc();
    ec.exp.alloc();
}

void incomeAdd(Transaction t) {
    ie.inc.push(t);
}

void expenseAdd(Transaction t) {
    ec.exp.push(t);
}

void totalBalance() {
    bal = ie.income - ec.expense;
}

//clear the current wallet's data
void cleallet() {
    ie.inc.dealloc();
    iep.dealloc();
    ec.exp.dealloc();
    ecp.dealloc();
}