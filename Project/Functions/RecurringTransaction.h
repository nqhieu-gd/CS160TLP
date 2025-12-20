#pragma once

#include <iostream>
#include <fstream>
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"
#include "../Data Structures/Wallet Info/Transaction/Auto_Trtn.h"

struct Address{  //Save the Wallet index and IS/EC index
    int w_index=-1;
    int i_index=-1;
    int e_index=-1;
};

struct ATM_Management{    //A structure to manage auto_transaction-> For delete or print....
                          //Only create during operating (and after delete Wallet/IC/EC/Auto_Transaction) and don't save it
    func<Auto_Transaction_List> atl;
    func<Address> adrs;
    void init();
    void clr();
    void add(const Auto_Transaction_List&,const Address&);
    void prt(const Wallist& wallist);
};

//Build for print all auto_transactions
void printatl(const Auto_Transaction_List&);
//We have 3 main functions:
//Auto add when start
//Add new recurring transaction
//Delete a recurring transaction


//Auto add when start
//And get data into the ATM_Management
void AddRecurringTransaction(Wallist& wallist);