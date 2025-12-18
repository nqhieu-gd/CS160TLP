#include <iostream>
#include <fstream>
#include "Transaction\Tstn.h"
#include "Wallet.h"
#include "..\\..\\Utilities\\DA\\Dynamicarray.h"

using std::string;

//create a new list of wallets
Wallist :: Wallist() {
    w.alloc();
}

//clear list of wallets
Wallist :: ~Wallist() {
    w.dealloc();
}

//Create a new wallet.
void Wallist :: CreateWallet() {
    Wallet wal;
//Generate wallet's name by default.
    int s = w.store; 
    wal.wName = "Wallet number ";
    string sub = " ";
    while (s >= 10) {
        s = s/10;
        sub += " ";
    }
    s = w.store;
    int k = sub.size();
    while (k > 0) {
        sub[--k] = s%10 + 48;
        s/=10;
    }
    wal.wName += sub;
//Generate wallet's ID by default.
    k = sub.size();
    wal.wID = "W";
    for (int i = 1; i < 8 - k; i++) {
        wal.wID += "0";
    }
    wal.wID += sub;
    w.push(wal);
}

void Wallist :: inWal(string id) {
//Create a string represent the save file of the wallet.
    string file = "..\\..\\Saved Wallet\\";
    file += id;
    file += ".bin";
    Transaction t;
    std::ifstream fin;
    fin.open(file, std::ios::binary | std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Can not find the wallet source file.";
        return;
    }
//If wID already presented in wallet list, update wallet of that ID, else create a new wallet.
    int k = w.store, ind = 8, temp = 0; //k represent the index of the wallet we want to update/add;
                                        //ind is for processing the size of name or id of the wallet, as well as the number of IS and EC.
                                        //temp is for processing the size of IS and EC, as well as the number of transactions of each type.
    for (int i = 0; i < k; i++) {
        if (w.p[i].wID == id) {
            k = i;
            w.p[k].is.dealloc();
            w.p[k].is.alloc();
            w.p[k].ec.dealloc();
            w.p[k].ec.alloc();
            break;
        }
    }
    if (k == w.store) CreateWallet();
//Input wallet ID.
    for (int i = 1; i < ind; i++) {
        w.p[k].wID.resize(1);
        w.p[k].wID.resize(8, ' ');
    }
    fin.read(&w.p[k].wID[1], 7);
//Input the wallet's name.
    fin.read((char*) &ind, 4);
    if (w.p[k].wName.size()) w.p[k].wName.erase(0, w.p[k].wName.size());
    for (int i = 0; i < ind; i++) {
        w.p[k].wName += " ";
    }
    fin.read(&w.p[k].wName[0], ind);
//Get the number of income sources and start inputting them.
    fin.read((char*) &ind, 4);
    for (int i = 0; i < ind; i++) {
        IncomeSource istemp;
    //Input income source's ID.
        istemp.iID.resize(0);
        istemp.iID.resize(8, '0');
        fin.read(&istemp.iID[0], 8);
    //Input income source's name.
        fin.read((char*) &temp, 4);
        if (istemp.iName.size()) istemp.iName.erase(0, istemp.iName.size());
        istemp.iName.resize(temp, ' ');
        fin.read(&istemp.iName[0], temp);
    //Input the number of transactions and start inputting them.
        fin.read((char*) &temp, 4);
        for (int j = 0; j < temp; j++) {
            inputTransactionFromFile(fin, t);
            istemp.inc.push(t);
        }
        w.p[k].is.push(istemp);
    }
//Tread similarly with expense categories.
    fin.read((char*) &ind, 4);
    for (int i = 0; i < ind; i++) {
        ExpenseCategory ectemp;
    //Input expense category's ID.
        ectemp.eID.resize(0);
        ectemp.eID.resize(8, '0');
        fin.read(&ectemp.eID[0], 8);
    //Input expense category's name.
        fin.read((char*) &temp, 4);
        ectemp.eName.erase(0, ectemp.eName.size());
        ectemp.eName.resize(temp, ' ');
        fin.read(&ectemp.eName[0], temp);
    //Input the number of transactions and start inputting them.
        fin.read((char*) &temp, 4);
        for (int j = 0; j < temp; j++) {
            inputTransactionFromFile(fin, t);
            ectemp.exp.push(t);
        }
        w.p[k].ec.push(ectemp);
    }
    fin.close();
}