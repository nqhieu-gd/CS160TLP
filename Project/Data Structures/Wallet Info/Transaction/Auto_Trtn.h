#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
#include "../../../Utilities/DA/Dynamicarray.h"
#include "Tstn.h"

using std::ifstream;
using std::ofstream;

struct Auto_Transaction{
    Transaction transaction;
    Date last_add={0,0,0};
    Date start_date;
    Date end_date={0,0,0};  //If it is forever, 0/0/0 too
    bool autoadd();
};

// Each Income Source or Expense Category will store a Auto_Transaction_Management
struct Auto_Transaction_List{
    func<Auto_Transaction> atm;
    void init(); // Initial an empty dynamic array
    void clear();// clear all dynamic data before closing the app
    void readatm(ifstream&); // Read data
    void writeatm(ofstream&);// Write data
    void erase(int k);// Erase tstn number k (index: k-1) 
    void checkexpired(); //If the transaction isn't added anymore-> delete
};
//add when reading the whole data T.T
