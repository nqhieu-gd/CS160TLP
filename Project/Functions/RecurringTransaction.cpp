#include <iostream>
#include <fstream>
#include "RecurringTransaction.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;


//Allocate an empty dynamic array
void ATM_Management:: init(){
    clr();
    atl.alloc();
    adrs.alloc();
}

//Clear dynamic array
void ATM_Management:: clr(){
    atl.dealloc();
    adrs.dealloc();
}

//Get ATM into ATM_Management
void ATM_Management:: add(const Auto_Transaction_List& a,const Address& b){
    atl.push(a);
    adrs.push(b);
}

//Build using for print all auto transactions
void printatl(const Auto_Transaction_List& temp){
    for (int i=0;i<temp.atm.store;++i){
        cout.width(8);
        cout<<i+1;
        cout<<". Amount: "<<temp.atm.p[i].transaction.amount<<endl;
        cout<<"          Description: "<<temp.atm.p[i].transaction.description<<endl;
        cout<<"          Start Date: "<<temp.atm.p[i].start_date.day<<"/"<<temp.atm.p[i].start_date.month<<"/"<<temp.atm.p[i].start_date.year<<endl;
        //Check if it's an infinite loop transaction
        if (temp.atm.p[i].end_date.day==0) cout<<"          No end Date(infinite loop)"<<endl;
        else cout<<"          End Date: "<<temp.atm.p[i].end_date.day<<"/"<<temp.atm.p[i].end_date.month<<"/"<<temp.atm.p[i].end_date.year<<endl;
    }
}

//Print list of all auto_transactions 
void ATM_Management:: prt(const Wallist& wallist){
    cout<<"This is list of recurring transactions!"<<endl;
    for (int i=0;i<atl.store;++i){
        cout<<"Wallet: "<<wallist.w.p[adrs.p[i].w_index].wName<<endl;
        if (adrs.p[i].i_index!=-1)
            cout<<"Income Source: "<<wallist.w.p[adrs.p[i].w_index].is.p[adrs.p[i].i_index].iName<<endl;
        else{
            cout<<"Expense Category: "<<wallist.w.p[adrs.p[i].w_index].ec.p[adrs.p[i].e_index].eName<<endl;
        }
        printatl(atl.p[i]);
    }
}

//Check all the Wallet, IS and EC to find ATM
void AddRecurringTransaction(Wallist& wallist, ATM_Management& atmm){
    for (int i=0;i<wallist.w.store;++i){
        for (int j=0;j<wallist.w.p[i].is.store;++j)
            if (wallist.w.p[i].is.p[j].i_atm.atm.store!=0){
                Address temp_address;
                temp_address.w_index=i;
                temp_address.i_index=j;
                atmm.add(wallist.w.p[i].is.p[j].i_atm,temp_address);
            }
    }
}