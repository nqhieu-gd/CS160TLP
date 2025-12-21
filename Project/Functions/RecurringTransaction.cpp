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
            wallist.w.p[i].outWal();
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
    if (choosewallet==wallist.w.store+1){
        wallist.CreateWallet();
        string str;
        while (cin.peek() == '\n') cin.ignore();
        while (1) {
            std::cout << "Enter a name for the new wallet: ";
            std::getline(std::cin, str);
            if (!wallist.editWal(choosewallet, str)) {
                std::cerr << "There was already a wallet with that name!\n";
                continue;
            }
            break;
        }
    }
    string i_iD="";
    string e_id="";
    if (iore==1){
        cout<<"This is list of Income Sources"<<endl;
        HashMap hm = wallist.isource();
        for (int i=0;i<hm.map.store;++i){
            cout.width(4);
            cout<<i+1;
            cout<<". "<<hm.map.p[i].name<<endl;
        }
        cout<<"    "<<hm.map.store+1<<". Create a new Income Source"<<endl;
        cout<<"    0. Go back to dashboard"<<endl;
        cout<<"Enter Income Source number: ";
        int chooseis;
        do{
            cin>>chooseis;
            if (chooseis<0&&chooseis>hm.map.store+1) cout<<"Invalid number! Please input again:";
        } while (chooseis<0&&chooseis>hm.map.store+1);
        if (chooseis==0) return;
        string name="";
        if (chooseis==hm.map.store+1){
            cout<<"Enter name of the new Income Source: ";
            cin.ignore();
            getline(cin,name);
            i_iD=wallist.w.p[choosewallet-1].convertNameInc(name);
        }
        else{
            i_iD=hm.map.p[chooseis-1].IDlist.p[0].substr(8,8);
        }
        string current_is_name = ""; // Save the current Income Source name
        if (chooseis == hm.map.store + 1) {
            current_is_name = name; // If new, use the entered name
        } else {
            current_is_name = hm.map.p[chooseis - 1].name;
        }

        cout << "Enter amount of money: ";
        long long amount;
        do {
            cin >> amount;
            if (amount < 0) cout << "Invalid amount! Please input again: ";
        } while (amount < 0);

        cout << "Enter description: ";
        string description;
        cin.ignore();
        getline(cin, description);

        cout << "Enter start date (dd mm yyyy): ";
        Date start_date;
        do {
            cin >> start_date.day >> start_date.month >> start_date.year;
            // Check logic for start date
            if (!(CheckvalidDate(start_date) && CompareDate(start_date, GetCurrDate()))) 
                cout << "Invalid date! Please input again: ";
        } while (!(CheckvalidDate(start_date) && CompareDate(start_date, GetCurrDate())));

        cout << "Enter end date (dd mm yyyy), enter 0 0 0 for infinite loop: ";
        Date end_date;
        do {
            cin >> end_date.day >> end_date.month >> end_date.year;
            // Check logic for end date
            bool isInfinite = (end_date.day == 0 && end_date.month == 0 && end_date.year == 0);
            if (!isInfinite && !(CheckvalidDate(end_date) && CompareDate(end_date, start_date))) 
                cout << "Invalid date! Please input again: ";
        } while (!((end_date.day == 0 && end_date.month == 0 && end_date.year == 0) || (CheckvalidDate(end_date) && CompareDate(end_date, start_date))));

        // Paste inputs into Auto_Transaction structure
        Transaction t;
        t.amount = amount;
        t.description = description;
        Auto_Transaction at;
        at.transaction = t;
        at.start_date = start_date;
        at.end_date = end_date;

        //Find if the Income Source with i_iD already exists in the chosen Wallet
        bool check = false;
        //If yes, just add the Auto_Transaction into that Income Source
        for (int i = 0; i < wallist.w.p[choosewallet - 1].is.store; ++i) {
            if (wallist.w.p[choosewallet - 1].is.p[i].iID == i_iD) {
                // Add the Auto_Transaction to the existing Income Source
                wallist.w.p[choosewallet - 1].is.p[i].i_atm.atm.push(at); //
                check = true;
                break; 
            }
        }

        //If not, create a new Income Source and add the Auto_Transaction into it
        if (!check) {
            // Create new Income Source with i_iD
            IncomeSource newIS(i_iD);
            //Name the Income Source
            newIS.iRename(current_is_name); //
            // Add the Auto_Transaction to the new Income Source
            newIS.i_atm.atm.push(at); //
            // Add the new Income Source to the chosen Wallet
            wallist.w.p[choosewallet - 1].is.push(newIS); //
        
    }
        //save data into file
        wallist.w.p[choosewallet - 1].outWal();
        cout << "Recurring transaction added successfully!" << endl;
        return;
    }
    else{
        cout<<"This is list of Expense Categories"<<endl;
        HashMap hm = wallist.ecategory();
        for (int i=0;i<hm.map.store;++i){
            cout.width(4);
            cout<<i+1;
            cout<<". "<<hm.map.p[i].name<<endl;
        }
        cout<<"    "<<hm.map.store+1<<". Create a new Expense Category"<<endl;
        cout<<"    0. Go back to dashboard"<<endl;
        cout<<"Enter Expense Category number: ";
        int chooseec;
        do{
            cin>>chooseec;
            if (chooseec<0&&chooseec>hm.map.store+1) cout<<"Invalid number! Please input again:";
        } while (chooseec<0&&chooseec>hm.map.store+1);
        if (chooseec==0) return;
        string name="";
        string current_ec_name = "";
        if (chooseec==hm.map.store+1){
            cout<<"Enter name of the new Expense Category: ";
            cin.ignore();
            getline(cin,name);
            e_id=wallist.w.p[choosewallet-1].convertNameExp(name);
            current_ec_name = name;
        }
        else{
            e_id=hm.map.p[chooseec-1].IDlist.p[0].substr(8,8);
        }
        //Similar to Income Source part, just change IS to EC and inc to exp
        cout << "Enter amount of money: ";
        long long amount;
        do {
            cin >> amount;
            if (amount < 0) cout << "Invalid amount! Please input again: ";
        } while (amount < 0);

        cout << "Enter description: ";
        string description;
        cin.ignore();
        getline(cin, description);

        cout << "Enter start date (dd mm yyyy): ";
        Date start_date;
        do {
            cin >> start_date.day >> start_date.month >> start_date.year;
            if (!(CheckvalidDate(start_date) && CompareDate(start_date, GetCurrDate()))) 
                cout << "Invalid date! Please input again: ";
        } while (!(CheckvalidDate(start_date) && CompareDate(start_date, GetCurrDate())));

        cout << "Enter end date (dd mm yyyy), enter 0 0 0 for infinite loop: ";
        Date end_date;
        do {
            cin >> end_date.day >> end_date.month >> end_date.year;
            bool isInfinite = (end_date.day == 0 && end_date.month == 0 && end_date.year == 0);
            if (!isInfinite && !(CheckvalidDate(end_date) && CompareDate(end_date, start_date))) 
                cout << "Invalid date! Please input again: ";
        } while (!((end_date.day == 0 && end_date.month == 0 && end_date.year == 0) || (CheckvalidDate(end_date) && CompareDate(end_date, start_date))));
        Transaction t;
        t.amount = amount;
        t.description = description;
        Auto_Transaction at;
        at.transaction = t;
        at.start_date = start_date;
        at.end_date = end_date;
        bool check = false;
        for (int i = 0; i < wallist.w.p[choosewallet - 1].ec.store; ++i) {
            if (wallist.w.p[choosewallet - 1].ec.p[i].eID == e_id) {
                wallist.w.p[choosewallet - 1].ec.p[i].e_atm.atm.push(at); //
                check = true;
                break; 
            }
        }
        if (!check) {
            ExpenseCategory newEC(e_id);
            newEC.eRename(current_ec_name); 
            newEC.e_atm.atm.push(at); 
            wallist.w.p[choosewallet - 1].ec.push(newEC); 
            cout << "Recurring transaction added successfully!" << endl;
            return;
        }
    }
}

void DeleteRecurringTransaction(Wallist& wallist, ATM_Management& atmm) {
    // Compute all recurring transactions available
    int total_transactions = 0;
    for (int i = 0; i < atmm.atl.store; ++i) {
        total_transactions += atmm.atl.p[i].atm.store;
    }

    if (total_transactions == 0) {
        cout << "There are no recurring transactions to delete." << endl;
        return;
    }

    //Print all recurring transactions with numbering
    atmm.prt(wallist);
    
    cout << "0. Go back to Dashboard" << endl;
    cout << "Enter the number of the transaction you want to delete: ";
    
    int choice;
    do {
        cin >> choice;
        if (choice < 0 || choice > total_transactions) {
            cout << "Invalid number! Please input again: ";
        }
    } while (choice < 0 || choice > total_transactions);

    if (choice == 0) return;

    // Find the real position of the chosen transaction
    int current_count = 0;
    int target_atl_index = -1; // Index of the Auto_Transaction_List in atmm.atl (0-based)
    int target_atm_index = -1; // Index of the Auto_Transaction in the selected list (0-based)

    bool found = false;
    for (int i = 0; i < atmm.atl.store; ++i) {
        // Iterate through each Auto_Transaction in the current Auto_Transaction_List
        for (int j = 0; j < atmm.atl.p[i].atm.store; ++j) {
            current_count++;
            if (current_count == choice) {
                target_atl_index = i;
                target_atm_index = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    // Delete the transaction from the appropriate Wallet
    if (found) {
        Address addr = atmm.adrs.p[target_atl_index]; // Get the address info
        int w_idx = addr.w_index;
        
        if (addr.i_index != -1) {
            // In case of Income Source
            wallist.w.p[w_idx].is.p[addr.i_index].i_atm.erase(target_atm_index + 1);
        } 
        else if (addr.e_index != -1) {
            // In case of Expense Category
            wallist.w.p[w_idx].ec.p[addr.e_index].e_atm.erase(target_atm_index + 1);
        }

        // Update the wallet file
        wallist.w.p[w_idx].outWal(); //
        cout << "Recurring transaction deleted successfully!" << endl;
    } else {
        cout << "Error: Could not locate the transaction." << endl;
    }
}

//main function
void RecurringTransactionFunction(Wallist& wallist, ATM_Management& atmm){
    cout<<"This is list of tasks with recurring transaction function"<<endl;
    cout<<"1. Add a recurring transaction"<<endl;
    cout<<"2. Delete a recurring transaction"<<endl;
    cout<<"0. Go back to Dashboard"<<endl;
    cout<<"Please enter your choice: ";
    int choice;
    do{
        cin>>choice;
        if (choice<0||choice>2) cout<<"Invalid number! Please input again: ";
    } while (choice<0||choice>2);
    if (choice==0) return;
    if (choice==1) AddRecurringTransaction(wallist);
    else DeleteRecurringTransaction(wallist,atmm);
    cout<<"Press enter to go back to Dashboard...";
    cin.ignore();
    cin.get();
}