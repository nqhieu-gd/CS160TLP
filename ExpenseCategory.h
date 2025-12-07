#pragma once
#include <fstream>
#include <string>
#include "Transaction.h"

struct ExpenseCategory{
    std::string ID;
    std::string Name;
    int quantity=0;
    Transaction* List=nullptr;
};
