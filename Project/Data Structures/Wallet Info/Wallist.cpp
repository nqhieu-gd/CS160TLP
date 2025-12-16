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