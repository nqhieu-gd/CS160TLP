#pragma once
#include <fstream>
#include <string>
#include "Transaction.h"

struct Wallet{
    std::string ID;
    std::string Name;
    int quantity=0;
    Transaction* List=nullptr;
};

void addTransaction(Wallet&, Transaction&);