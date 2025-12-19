#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"

struct Auto_Transaction{
    Transaction auto_transaction;
    Date last_add;
    Date start_date;
    Date end_date;
};

struct Auto_Transaction_Management{
    func<Auto_Transaction> atm;
    void init();
    void clear();
};

void Auto_Transaction_Management :: init(){
    if (atm.p==nullptr){
        atm.dealloc();
        atm.alloc();
    }
}

void Auto_Transaction_Management :: clear(){
    atm.dealloc();
}