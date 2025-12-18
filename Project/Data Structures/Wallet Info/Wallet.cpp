#include <iostream>
#include <fstream>
#include "Wallet.h"
#include "..\\..\\Utilities\\DA\\Dynamicarray.h"

using std::string;

//create a new wallet
Wallet :: Wallet() {
    is.alloc();
    ec.alloc();
}

//Output the current wallet to the designated save file.
//Used after each change made in the wallet.
void Wallet :: outWal() {
    std::ofstream fout;
    string path = "..\\..\\Saved Wallet\\";
    path += wID + ".bin";
    fout.open(path, std::ios::binary | std::ios::out);
    if (!fout.is_open()) {
        std::cerr << "Error opening the destination path.";
        return;
    }
    int k = 0;
//Output wID Wxxxxxxx (8 digits, the first digit is always W).
    fout.write(&wID[1], wID.size() - 1);
//Output size of wName and output wName.
    k = wName.size();
    fout.write((char*) &k, sizeof(int));
    fout.write(&wName[0], wName.size());
//Output the number of income sources in is (list of income sources).
    fout.write((char*) &is.store, sizeof(int));
    for (int i = 0; i < is.store; i++) {
    //Output ID of each income source.
        fout.write(&is.p[i].iID[0], is.p[i].iID.size());
    //Output size of iName and iName of each income source.
        k = is.p[i].iName.size();
        fout.write((char*) &k, sizeof(int));
        fout.write(&is.p[i].iName[0], is.p[i].iName.size());
    //Output the number of transactions in inc (list of transaction in an income source).
        fout.write((char*) &is.p[i].inc.store, sizeof(int));
        for (int j = 0; j < is.p[i].inc.store; j++) {
        //Output each transaction.
            outputTransactiontoFile(fout, is.p[i].inc.p[j]);
        }
    }
//Similarly with expense categories.
//Output the number of expense categories in is (list of expense categories).
    fout.write((char*) &ec.store, sizeof(int));
    for (int i = 0; i < ec.store; i++) {
    //Output ID of each expense category.
        fout.write(&ec.p[i].eID[0], ec.p[i].eID.size());
    //Output size of iName and iName of each expense category.
        k = ec.p[i].eName.size();
        fout.write((char*) &k, sizeof(int));
        fout.write(&ec.p[i].eName[0], ec.p[i].eName.size());
    //Output the number of transactions in exp (list of transaction in an expense category).
        fout.write((char*) &ec.p[i].exp.store, sizeof(int));
        for (int j = 0; j < ec.p[i].exp.store; j++) {
        //Output each transaction.
            outputTransactiontoFile(fout, ec.p[i].exp.p[j]);
        }
    }
//Close the output file.
    fout.close();
}

//Add an income, if the source ID has already presented in is (list of income sources),
//add t to that ID, else create a new ID name.
void Wallet :: incomeAdd(const Transaction t, const string ID) {
    for (int i = 0; i < is.store; i++) {
        if (ID == is.p[i].iID) is.p[i].inc.push(t);
        outWal();
        return;
    }
    IncomeSource ie(ID);
    ie.inc.push(t);
    is.push(ie);
    outWal();
}

//Add an expense, if the category ID has already presented in ec (list of expense categories),
//add t to that ID, else create a new ID name.
void Wallet :: expenseAdd(const Transaction t, const string ID) {
    for (int i = 0; i < ec.store; i++) {
        if (ID == ec.p[i].eID) ec.p[i].exp.push(t);
        outWal();
        return;
    }
    ExpenseCategory et(ID);
    et.exp.push(t);
    ec.push(et);
    outWal();
}

//Calculate the current wallet's total balance (total income minus total expense),
//can be negative, automatically update for each changes in wallet.
long long Wallet :: totalBalance() {
    long long c = 0;
    for (int i = 0; i < is.store; i++) {
        c += is.p[i].income();
    }
    for (int i = 0; i < ec.store; i++) {
        c -= ec.p[i].expense();
    }
    return c;
}

//Clear the current wallet's data.
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

void Wallet :: rename() {
    std::cout << "Enter new name for wallet ID " << wID << ": ";
    std::getline(std::cin, wName);
    outWal();
}