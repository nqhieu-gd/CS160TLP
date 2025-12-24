#pragma once

#include <iostream>
#include <fstream>
#include "../Data Structures/Auto_Trtn.h"
#include "../Data Structures/Cate.h"
#include "../Data Structures/Sour.h"
#include "../Data Structures/Tstn.h"
#include "../Data Structures/Wallet.h"
#include "../../Utilities/DA/Dynamicarray.h"

struct Address{  //Save the Wallet index and IS/EC index
    int w_index=-1;
    int i_index=-1;
    int e_index=-1;
};

struct ATM_Management{    //A structure to manage auto_transaction-> For delete or print....
                          //Only create during operating (and after delete Wallet/IC/EC/Auto_Transaction) and don't save it
    func<Auto_Transaction_List> atl;// Save ATL
    func<Address> adrs; //Save index of ATL
    void init();
    void clr();
    void add(const Auto_Transaction_List&,const Address&);
    void prt(const Wallist&);
};

//Build for print all auto_transactions
void printatl(const Auto_Transaction_List&);
//We have 3 main functions:
//Auto add when start
//Add new recurring transaction
//Delete a recurring transaction


//Auto add when start
//And get data into the ATM_Management
void Operation(Wallist&, ATM_Management&);

//Add new recurring transaction
void AddRecurringTransaction(Wallist&);

//Delete a recurring transaction
void DeleteRecurringTransaction(Wallist&, ATM_Management&);

//main function
void RecurringTransactionFunction(Wallist&, ATM_Management&);