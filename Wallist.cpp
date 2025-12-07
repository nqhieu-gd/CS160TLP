#include <iostream>
#include <fstream>
#include <string>
#include "Transaction.h"
#include "Wallet.h"
#include "Dynamicarray.h"

using std::string;

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