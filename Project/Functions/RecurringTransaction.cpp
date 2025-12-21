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
        cout<<"          Amount: "<<temp.atm.p[i].transaction.amount<<endl;
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
    int count=0;
    for (int i=0;i<atl.store;++i){
        for (int j=0;j<atl.p[i].atm.store;++j){
            cout.width(8);
            cout<<++count;
            cout<<". Wallet: "<<wallist.w.p[adrs.p[i].w_index].wName<<endl;
            if (adrs.p[i].i_index!=-1) cout<<"          Income Source: "<<wallist.w.p[adrs.p[i].w_index].is.p[adrs.p[i].i_index].iName<<endl;
            else cout<<"          Income Source: "<<wallist.w.p[adrs.p[i].w_index].ec.p[adrs.p[i].e_index].eName<<endl;
            printatl(atl.p[i]);
            cout<<endl;
        }
    }
}

//Check all the Wallet, IS and EC to find ATM
//Add Transaction if it meets conditions
//Use whenever we start over the programme
void Operation(Wallist& wallist, ATM_Management& atmm){
    atmm.init(); //Clear old data and set up an empty DA
    for (int i=0;i<wallist.w.store;++i){
        for (int j=0;j<wallist.w.p[i].is.store;++j){
            //First, we check if it meets conditions to add
            if (wallist.w.p[i].is.p[j].i_atm.atm.store!=0){
                for (int k=0;k<wallist.w.p[i].is.p[j].i_atm.atm.store;++k){
                    int count=wallist.w.p[i].is.p[j].i_atm.atm.p[k].autoadd();
                    if (count!=0){
                        Transaction temp=wallist.w.p[i].is.p[j].i_atm.atm.p[k].transaction;
                        temp.date=GetCurrDate();
                        for (int n=1;n<=count;++n) wallist.w.p[i].is.p[j].inc.push(temp);
                    }
                }
            //After add, check if any autotransaction is expired
            wallist.w.p[i].is.p[j].i_atm.checkexpired();
            if (wallist.w.p[i].is.p[j].i_atm.atm.store!=0){
                Address temp_address;
                temp_address.w_index=i;
                temp_address.i_index=j;
                atmm.add(wallist.w.p[i].is.p[j].i_atm,temp_address);
            }
        }
    }
        //Similarly to Expense Category
        for (int j=0;j<wallist.w.p[i].ec.store;++j){
            //First, we check if it meets conditions to add
            if (wallist.w.p[i].ec.p[j].e_atm.atm.store!=0){
                for (int k=0;k<wallist.w.p[i].ec.p[j].e_atm.atm.store;++k){
                    int count=wallist.w.p[i].ec.p[j].e_atm.atm.p[k].autoadd();
                    if (count!=0){
                        Transaction temp=wallist.w.p[i].ec.p[j].e_atm.atm.p[k].transaction;
                        temp.date=GetCurrDate();
                        for (int n=1;n<=count;++n) wallist.w.p[i].ec.p[j].exp.push(temp);
                    }
                }
            //After add, check if any autotransaction is expired
            wallist.w.p[i].ec.p[j].e_atm.checkexpired();
            if (wallist.w.p[i].ec.p[j].e_atm.atm.store!=0){
                Address temp_address;
                temp_address.w_index=i;
                temp_address.e_index=j;
                atmm.add(wallist.w.p[i].ec.p[j].e_atm,temp_address);
            }
        }
    }
}
}

void AddRecurringTransaction(Wallist& wallist){
    cout<<"1. Add an Income recurring transaction "<<endl;
    cout<<"2. Add an Expense recurring transaction "<<endl;
    cout<<"0. Go back to the dash board"<<endl;
    cout<<"Please enter the task number:";
    int iore;
    do {
        cin>>iore;
        if (iore<0&&iore>2) cout<<"Invalid! Please enter again: ";
    } while (iore<0&&iore>2);
    if (iore==0) return;
    cout<<"This is list of Wallets"<<endl;
    for (int i=0;i<wallist.w.store;++i){
        cout.width(4);
        cout<<i+1;
        cout<<". "<<wallist.w.p[i].wName<<endl;
    }
    cout.width(4);
    cout<<wallist.w.store+1<<". Create a new Wallet"<<endl;
    cout<<"    0. Go back to dashboard"<<endl;
    cout<<"Enter wallet number: ";
    int choosewallet;
    do{
        cin>>choosewallet;
        if (choosewallet<0&&choosewallet>wallist.w.store+1) cout<<"Invalid number! Please input again:";
    } while (choosewallet<0&&choosewallet>wallist.w.store+1);
    if (choosewallet==0) return;
    if (choosewallet==wallist.w.store+1); // Create a new wallet
    
}