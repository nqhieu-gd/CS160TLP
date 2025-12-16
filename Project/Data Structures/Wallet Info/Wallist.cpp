#include <iostream>
#include <fstream>
#include <string>
#include "Transaction\Tstn.h"
#include "Wallet.h"
#include "..\..\Utilities\DA\Dynamicarray.h"

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
    sub[0] = s%10 + 48;
    while (s >= 10) {
        s = s/10;
        sub += " ";
    }
    s = w.store;
    int k = sub.size();
    while (k > 0) {
        sub[--k] = s%10 + 48;
    }
    wal.wName += sub;
//Generate wallet's ID by default.
    int k = sub.size();
    wal.wID = "W";
    for (int i = 1; i < 8 - k; i++) {
        wal.wID += "0";
    }
    wal.wID += sub;
    w.push(wal);
}

void Wallist :: inWal(string name) {
    string file = "..\\..\\Saved Wallet\\";
    file += name;
    file += ".bin";
    std::ifstream fin;
    fin.open(file, std::ios::binary | std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Can not find the wallet source file.";
        return;
    }
    int k = w.store, ind = 8, temp = 0;
    for (int i = 0; i < k; i++) {
        if (w.p[i].wName == name) k = i;
        break;
    }
    if (k == w.store) CreateWallet;
    for (int i = 1; i < ind; i++) w.p[k].wID[i] = '\0';
    fin.read(&w.p[k].wID[1], 7);
    fin.read((char*) &ind, 4);
    w.p[k].wName.erase(0, w.p[k].wName.size());
    for (int i = 0; i < ind; i++) {
        w.p[k].wName += " ";
    }
    fin.read(&w.p[k].wName[0], ind);
    fin.read((char*) &ind, 4);
    for (int i = 0; i < ind; i++) {
        for (int j = 0; j < 8; j++) w.p[k].is.p[i].iID[j] = '\0';
        fin.read(&w.p[k].is.p[i].iID[0], 8);
        fin.read((char*) &temp, 4);
        w.p[k].is.p[i].iName.erase(0, w.p[k].is.p[i].iName.size());
        for (int i = 0; i < ind; i++) {
            w.p[k].is.p[i].iName += " ";
        }
        fin.read(&w.p[k].is.p[i].iName[0], temp);
    }
}