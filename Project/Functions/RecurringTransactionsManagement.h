#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"
#include "TransactionManagement.h"

struct Auto_Transaction{
    Transaction transaction;
    Date last_add={0,0,0};
    Date start_date;
    Date end_date;
    string wID="";
    string iID="";
    string eID="";
};

struct Auto_Transaction_Management{
    func<Auto_Transaction> atm;
    void init(); // Initial an empty dynamic array
    void clear();// clear all dynamic data before closing the app
    void read(); // Read data from "autotstn.bin"
    void write();// Write data to "autotstn.bin"
    void erase(int k);// Erase tstn number k (index: k-1) 
    void checkexpired(); //If the transaction isn't added anymore-> delete
    //If its Wallet or its IS/EC was deleted -> Deleted it too
    //If its Wallet ID / IS/EC ID was in delete list -> erase
};

void autoadd(); //If the date is ok ->add
// At the same time, it will clear expired Transaction
void editautotransaction(Auto_Transaction_Management& ); //User can delete or add an auto transaction
