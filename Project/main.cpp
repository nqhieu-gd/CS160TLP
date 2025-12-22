#include "Data Structures/Expense Category/Cate.h"
#include "Data Structures/Income Source/Sour.h"
#include "Data Structures/Wallet Info/Wallet.h"
#include "Data Structures/Wallet Info/Transaction/Tstn.h"
#include "Data Structures/Wallet Info/Transaction/Auto_Trtn.h"
#include "Functions/RecurringTransaction.h"
#include "Functions/AddTransaction.h"
#include "Functions/EditWalletThings.h"
#include "Functions/Statistic.h"
#include "Utilities/DA/Dynamicarray.h"
#include "Utilities/Hashmap/Hashmap.h"
#include "Utilities/Uppercase/Uppercase.h"
#include "Utilities/Initialize/Ini.h"
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
    //Output all data to files before exiting
    atmm.clr();
    return 0;
}