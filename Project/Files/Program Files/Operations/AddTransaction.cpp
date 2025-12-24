#include <iostream>
#include <fstream>
#include "../../Header Files/Operations/AddTransaction.h"
#include "../../Utilities/Uppercase/Uppercase.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

//Choosing between Income/ Expense Management
int ChooseIMorEM(){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the menu of Transaction Management"<<endl;
    cout<<"1. Income Management"<<endl;
    cout<<"2. Expense Management"<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the utility:"<<endl;
    int choose;
    cin>>choose;
    return choose;
}

//Choose Wallet
int chooseWallet(const Wallist& wallist){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of current available Wallets:"<<endl;
    for (int i=0;i<wallist.w.store;++i)
        cout<<i+1<<". "<<wallist.w.p[i].wName<<endl;
    cout<<wallist.w.store+1<<". Create a new Wallet."<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    int choose;
    cout<<"Please enter the Wallet number:"<<endl;
    cin>>choose;
    while (choose<0||choose>wallist.w.store+1){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Wallet number:"<<endl;
        cin>>choose;
    }
    return choose;
}

int chooseWalletWhatever(const Wallist& wallist){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of current available Wallets:"<<endl;
    for (int i=0;i<wallist.w.store;++i)
        cout<<i+1<<". "<<wallist.w.p[i].wName<<endl;
    cout<<"0. Return to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    int choose;
    cout<<"Please enter the Wallet number:"<<endl;
    cin>>choose;
    while (choose<0||choose>wallist.w.store){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Wallet number:"<<endl;
        cin>>choose;
    }
    return choose;
}

//Choose Income Source
int chooseIS(Wallist& wallist, int index){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of Income Sources"<<endl;
    for (int i=0;i<wallist.w.p[index].is.store;++i)
        cout<<i+1<<". "<<wallist.w.p[index].is.p[i].iName<<endl;
    cout<<wallist.w.p[index].is.store+1<<". Create a new Income Source."<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the Income Source number:"<<endl;
    int choose;
    cin>>choose;
    while (choose<0||choose>wallist.w.p[index].is.store + 1){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Income Source number: "<<endl;
        cin>>choose;
    }
    return choose;
}

int chooseISWhatever(Wallist& wallist, int index){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of Income Sources"<<endl;
    for (int i=0;i<wallist.w.p[index].is.store;++i)
        cout<<i+1<<". "<<wallist.w.p[index].is.p[i].iName<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the Income Source number:"<<endl;
    int choose;
    cin>>choose;
    while (choose<0||choose>wallist.w.p[index].is.store){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Income Source number: "<<endl;
        cin>>choose;
    }
    return choose;
}

//Choose Expense Category
int chooseEC(Wallist& wallist, int index){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of Expense Category in the current wallet."<<endl;
    for (int i=0;i<wallist.w.p[index].ec.store;++i)
        cout<<i+1<<". "<<wallist.w.p[index].ec.p[i].eName<<endl;
    cout<<wallist.w.p[index].ec.store+1<<". Create a new Expense Category."<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the Expense Category number: "<<endl;
    int choose;
    cin>>choose;
    while (choose<0||choose>wallist.w.p[index].ec.store + 1){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Expense Category number:"<<endl;
        cin>>choose;
    }
    return choose;
}

int chooseECWhatever(Wallist& wallist, int index){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of Expense Category in the current wallet."<<endl;
    for (int i=0;i<wallist.w.p[index].ec.store;++i)
        cout<<i+1<<". "<<wallist.w.p[index].ec.p[i].eName<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the Expense Category number: "<<endl;
    int choose;
    cin>>choose;
    while (choose<0||choose>wallist.w.p[index].ec.store){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Expense Category number:"<<endl;
        cin>>choose;
    }
    return choose;
}

//Input description for a transaction.
void inputRest(Transaction& a){
    cout<<"Description: ";
    while (cin.peek() == '\n') cin.ignore();
    getline(cin,a.description);
}

//Main function.
void TransactionManagement(Wallist& wallist){
    int index_wallet=chooseWallet(wallist);
    if (index_wallet==0) return;
    if (--index_wallet==wallist.w.store) {
        wallist.CreateWallet();
        string str;
        while (1) {
            std::cout << "Enter a name for the new wallet: ";
            while (cin.peek() == '\n') cin.ignore();
            std::getline(std::cin, str);
            if (!wallist.editWal(index_wallet, str)) {
                std::cerr << "There was already a wallet with that name!\n";
                continue;
            }
            break;
        }
    }
    switch (ChooseIMorEM()){
        case 0: return;
        case 1: {int index_IS=chooseIS(wallist, index_wallet);
                if (index_IS==0) return;
                string name;
                if (index_IS == wallist.w.p[index_wallet].is.store + 1) {
                    cout << "Enter new Income Source Name: ";
                    while (cin.peek() == '\n') cin.ignore();
                    getline(cin, name);
                } else {
                    name = wallist.w.p[index_wallet].is.p[index_IS - 1].iName;
                }
                cout<<"========================================================"<<endl;
                cout<<endl;
                cout<<"Wallet: "<<wallist.w.p[index_wallet].wName<<endl;
                cout<<"Income Source: "<<name;
                cout<<endl;
                cout<<"========================================================"<<endl;
                Transaction a = ipt();
                inputRest(a);
                wallist.w.p[index_wallet].ISAdd(a, name);
                break;}
        case 2: {int index_EC=chooseEC(wallist, index_wallet);
                if (index_EC==0) return;
                string name;
                if (index_EC == wallist.w.p[index_wallet].ec.store + 1) {
                    cout << "Enter new Expense Category name: ";
                    while (cin.peek() == '\n') cin.ignore();
                    getline(cin, name);
                } else {
                    name = wallist.w.p[index_wallet].ec.p[index_EC - 1].eName;
                }
                cout<<"========================================================"<<endl;
                cout<<endl;
                cout<<"Wallet: "<<wallist.w.p[index_wallet].wName<<endl;
                cout<<"Expense Category: "<<name;
                cout<<endl;
                cout<<"========================================================"<<endl;
                Transaction a = ipt();
                inputRest(a);
                wallist.w.p[index_wallet].ECAdd(a, name);
                break;}
    }
}

void inWallist(Wallist &wallist) {
    string id = "W0000001";
    while (wallist.inWal(id)) {
        for (int i = 7; i >= 0; i--) {
            if (i == 0) {
                std::cerr << "Wallet limit exceeded!";
                return;
            }
            if (id[i] == '9') {
                id[i] = '0';
                continue;
            }
            id[i]++;
            break;
        }
    }
}