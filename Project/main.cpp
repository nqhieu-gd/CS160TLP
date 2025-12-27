#include "Files/Header Files/Data Structures/Auto_Trtn.h"
#include "Files/Header Files/Data Structures//Cate.h"
#include "Files/Header Files/Data Structures/Sour.h"
#include "Files/Header Files/Data Structures/Tstn.h"
#include "Files/Header Files/Data Structures/Wallet.h"
#include "Files/Header Files/Operations/AllOperations.h"
#include "Files/Header Files/Operations/EditWalletThings.h"
#include "Files/Header Files/Operations/Ini.h"
#include "Files/Header Files/Operations/RecurringTransaction.h"
#include "Files/Header FIles/Statistics/Statistic.h"
#include "Files/Utilities/DA/Dynamicarray.h"
#include "Files/Utilities/Hashmap/Hashmap.h"
#include "Files/Utilities/Uppercase/Uppercase.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
    ini();
    Wallist wallist;
    inWallist(wallist);
    ATM_Management atmm;
    while (true){
        Operation(wallist, atmm); // Auto add recurring transactions at the start of each loop
        cout<<"======================================"<<endl;
        cout<<"        Personal Finance Manager        "<<endl;
        cout<<"======================================"<<endl;
        DashboardStatistics(wallist);
        cout<<"======================================="<<endl;
        cout<<"1. Add Transaction"<<endl;
        cout<<"2. Recurring Transaction Management"<<endl;
        cout<<"3. Edit Wallet/Income Source/Expense Category"<<endl;
        cout<<"4. Reporting and Statistics"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"Enter your choice: ";
        int choice;
        do{
            cin>>choice;
            if (choice<0||choice>4) cout<<"Invalid number! Please input again: ";
        } while (choice < 0 || choice > 4);
        if (choice==0) break;
        switch (choice){
            case 1: {
                TransactionManagement(wallist);
                break;
            }
            case 2: {
                RecurringTransactionFunction(wallist,atmm);
                break;
            }
            case 3: {
                implementWhateverYouWant(wallist);
                break;
            }
            case 4: {
                Statisticfunction(wallist);
                break;
            }
            default: break;
        }
    }
    cout<<"Thank you for using Personal Finance Manager. Goodbye!"<<endl;
    //Output all data to Files before exiting
    atmm.clr();
    return 0;
}