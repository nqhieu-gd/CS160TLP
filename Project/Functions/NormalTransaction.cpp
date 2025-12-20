#include <iostream>
#include <fstream>
#include "NormalTransaction.h"

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

//Check if the Date is suitable
bool ExamineDate(const Date& a){
    if (!CheckvalidDate(a)) return false;
    if (CompareDate(a,GetCurrDate())==1) return false;
    return true;
}

//Choose Wallet
int chooseWallet(const Wallist& wallist){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of Wallets:"<<endl;
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

//Input Date
Date inputDate(){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"1. Get current Date"<<endl;
    cout<<"2. Enter the date manually (Note: this function does not accept future dates)"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the utility:";
    int choose;
    cin>>choose;
    if (choose==1) return GetCurrDate();
    cout<<"Please input the Date (format: dd mm yyyy):";
    Date a;
    cin>>a.day>>a.month>>a.year;
    while (!ExamineDate(a)){
        cout<<"Invalid Date! Please try again!"<<endl;
        cout<<"Please input the Date (format: dd mm yyyy):";
        Date a;
        cin>>a.day>>a.month>>a.year;
    }
    return a;
}

//Choose Income Source
int chooseIS(const Wallist& wallist){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of Income Sources"<<endl;
    for (int i=0;i<wallist.w.p[0].is.store;++i)
        cout<<i+1<<". "<<wallist.w.p[0].is.p[i].iName<<endl;
    cout<<wallist.w.p[0].is.store+1<<". Create a new Income Source."<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the Income Source number:"<<endl;
    int choose;
    cin>>choose;
    while (choose<0||choose>wallist.w.p[0].is.store){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Income Source number:"<<endl;
        cin>>choose;
    }
    return choose;
}

//Choose Expense Category
int chooseEC(const Wallist& wallist){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"This is the list of Expense Category"<<endl;
    for (int i=0;i<wallist.w.p[0].ec.store;++i)
        cout<<i+1<<". "<<wallist.w.p[0].ec.p[i].eName<<endl;
    cout<<wallist.w.p[0].ec.store+1<<". Create a new Expense Category."<<endl;
    cout<<"0. Back to the Dashboard"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the Expense Category number:"<<endl;
    int choose;
    cin>>choose;
    while (choose<0||choose>wallist.w.p[0].ec.store){
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Please enter the Expense Category number:"<<endl;
        cin>>choose;
    }
    return choose;
}

//Input other information
void inputRest(Transaction& a){
    cout<<"Amount of Money:";
    cin>>a.amount;
    while (a.amount<0) {
        cout<<"Invalid number! Please try again!"<<endl;
        cout<<"Amount of Money:";
        cin>>a.amount;
    }
    cout<<"Description:";
    getline(cin,a.description);
}

//mainfunction
void TransactionManagement(Wallist& wallist){
    int index_wallet=chooseWallet(wallist);
    if (index_wallet==0) return;
    if (--index_wallet==wallist.w.store) wallist.CreateWallet();
    switch (ChooseIMorEM()){
        case 0: return;
        case 1: {int index_IS=chooseIS(wallist);
                if (index_IS==0) return;
//                if (--index_IS==wallist.w.p[index_wallet].is.store) wallist.CreateInSr();    //Create new IS and EC
                cout<<"========================================================"<<endl;
                cout<<endl;
                cout<<"Wallet: "<<wallist.w.p[index_wallet].wName<<endl;
                cout<<"Income Source: "<<wallist.w.p[index_wallet].is.p[index_IS].iName;
                cout<<endl;
                cout<<"========================================================"<<endl;
                Transaction a;
                a.date=inputDate();
                inputRest(a);
                wallist.w.p[index_wallet].is.p[index_IS].inc.push(a);
                break;}
        case 2: {int index_EC=chooseEC(wallist);
                if (index_EC==0) return;
//                if (--index_EC==wallist.w.p[index_wallet].ec.store) wallist.CreateEcCa();    //Create new IS and EC
                cout<<"========================================================"<<endl;
                cout<<endl;
                cout<<"Wallet: "<<wallist.w.p[index_wallet].wName<<endl;
                cout<<"Expense Category: "<<wallist.w.p[index_wallet].ec.p[index_EC].eName;
                cout<<endl;
                cout<<"========================================================"<<endl;
                Transaction a;
                a.date=inputDate();
                inputRest(a);
                wallist.w.p[index_wallet].ec.p[index_EC].exp.push(a);
                break;}
    }
}

Wallist inWallist() {
    Wallist def;
    string id = "W0000001";
    while (def.inWal(id)) {
        for (int i = 7; i >= 0; i--) {
            if (i == 0) {
                std::cerr << "Wallet limit exceeded!";
                return def;
            }
            if (id[i] == '9') {
                id[i] = '0';
                continue;
            }
            id[i]++;
            break;
        }
    }
    return def;
}