#include <iostream>
#include <fstream>
#include "../../Header Files/Statistics/Statistic.h"
#include "../../Header Files/Data Structures/Cate.h"
#include "../../Header Files/Data Structures/Sour.h"
#include "../../Header Files/Data Structures/Wallet.h"
#include "../../Header Files/Data Structures/Tstn.h"
#include "../../Utilities/DA/Dynamicarray.h"
#include "../../Utilities/Hashmap/HashMap.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

//Calculate Total Balance of all Wallets and Total Balances of each wallets
//Use whenever start over the programme and in the dashboard
void DashboardStatistics(const Wallist& wallist){
    if (wallist.w.store==0){
        cout<<"Total Balance of all Wallets: 0"<<endl;
        return;
    }
    else{
        long long* total_balance=new long long[wallist.w.store];
        for (int i=0;i<wallist.w.store;++i){
            total_balance[i]=wallist.w.p[i].curBalance();
        }
        long long grand_total=0;
        for (int i=0;i<wallist.w.store;++i){
            grand_total+=total_balance[i];
        }
        cout<<"Total Balance of all Wallets: "<<grand_total<<endl;
        for (int i=0;i<wallist.w.store;++i){
            cout.width(4);
            cout<<i+1;
            cout<<". "<<wallist.w.p[i].wName<<": "<<total_balance[i]<<endl;
        }
        delete[] total_balance;
    }
}

//Calculate Total Balance within a date range
void TotalBalance(const Wallist& wallist){
    //Tell user to enter date range
    Date A,B;
    do{
        cout<<"Please enter the start date (day month year): ";
        cin>>A.day>>A.month>>A.year;
        cout<<"Please enter the end date (day month year): ";
        cin>>B.day>>B.month>>B.year;
        if (CompareDate(A,B)) cout<<"Invalid date range, please re-enter."<<endl;
    }while (CompareDate(A,B));
    long long total_income=0;
    long long total_expense=0;
    for (int i=0;i<wallist.w.store;++i){
        for (int j=0;j<wallist.w.p[i].is.store;++j)
            for (int k=0;k<wallist.w.p[i].is.p[j].inc.store;++k)
            {
                if (CompareDate(wallist.w.p[i].is.p[j].inc.p[k].date,B)) break;
                if (!CompareDate(A,wallist.w.p[i].is.p[j].inc.p[k].date)) total_income+=wallist.w.p[i].is.p[j].inc.p[k].amount;
            }
        for (int j=0;j<wallist.w.p[i].ec.store;++j)
            for (int k=0;k<wallist.w.p[i].ec.p[j].exp.store;++k)
            {
                if (CompareDate(wallist.w.p[i].ec.p[j].exp.p[k].date,B)) break;
                if (!CompareDate(A,wallist.w.p[i].ec.p[j].exp.p[k].date)) total_expense+=wallist.w.p[i].ec.p[j].exp.p[k].amount;
    }
    }
    long long net_balance=total_income-total_expense;
    cout<<endl;
    cout<<"\n ======= Total Balance Statistics ======= \n";
    cout<<"Total Balance from "<<A.day<<"/"<<A.month<<"/"<<A.year<<" to "<<B.day<<"/"<<B.month<<"/"<<B.year<<endl;
    cout<<"Total Income: "<<total_income<<endl;
    cout<<"Total Expense: "<<total_expense<<endl;
    cout<<"Net Balance: "<<net_balance<<endl;
}

//Calculate Total Balance
//Then breakdown Wallet via time range
void TimeWalletStatistics(const Wallist& wallist){
    //Tell user to enter date range
    Date A,B;
    do{
        cout<<"Please enter the start date (day month year): ";
        cin>>A.day>>A.month>>A.year;
        cout<<"Please enter the end date (day month year): ";
        cin>>B.day>>B.month>>B.year;
        if (!CompareDate(A,B)) cout<<"Invalid date range, please re-enter."<<endl;
    }while (!CompareDate(A,B));
    cout<<endl;
    cout<<"\n ======= Time-Wallet Based Statistics ======= \n";
    cout<<"Total Balance from "<<A.day<<"/"<<A.month<<"/"<<A.year<<" to "<<B.day<<"/"<<B.month<<"/"<<B.year<<endl;
    long long grand_total_income=0;
    long long grand_total_expense=0;
    long long grand_net_balance=0;
    for (int i=0;i<wallist.w.store;++i){
        cout.width(4);
        cout<<i+1<<". Wallet: "<<wallist.w.p[i].wName<<endl;
        long long total_income=0;
        long long total_expense=0;
        for (int j=0;j<wallist.w.p[i].is.store;++j)
            for (int k=0;k<wallist.w.p[i].is.p[j].inc.store;++k)
            {
                if (CompareDate(wallist.w.p[i].is.p[j].inc.p[k].date,B)) break;
                if (!CompareDate(A,wallist.w.p[i].is.p[j].inc.p[k].date)) total_income+=wallist.w.p[i].is.p[j].inc.p[k].amount;
            }
        for (int j=0;j<wallist.w.p[i].ec.store;++j)
            for (int k=0;k<wallist.w.p[i].ec.p[j].exp.store;++k)
            {
                if (CompareDate(wallist.w.p[i].ec.p[j].exp.p[k].date,B)) break;
                if (!CompareDate(A,wallist.w.p[i].ec.p[j].exp.p[k].date)) total_expense+=wallist.w.p[i].ec.p[j].exp.p[k].amount;
            }
        long long net_balance=total_income-total_expense;
        cout<<"    Total Income: "<<total_income<<endl;
        cout<<"    Total Expense: "<<total_expense<<endl;
        cout<<"    Net Balance: "<<net_balance<<endl;
        grand_total_income+=total_income;
        grand_total_expense+=total_expense;
    }
    grand_net_balance=grand_total_income-grand_total_expense;
    cout<<"Grand Total Income: "<<grand_total_income<<endl;
    cout<<"Grand Total Expense: "<<grand_total_expense<<endl;
    cout<<"Grand Net Balance: "<<grand_net_balance<<endl;
}

void AnnualOverviewStatistics(const Wallist& wallist){
    //First, ask user for the year they want to overview
    func<int> years;
    years.alloc();
    cout<<"Please enter the year you want to overview(enter a year> current year to stop): ";
    int year_input;
    while (true){
        cin>>year_input;
        if (year_input<=GetCurrDate().year){
            years.push(year_input);
        }
        else break;
    }
    //Then sort the years array
    for (int i=0;i<years.store-1;++i){
        for (int j=i+1;j<years.store;++j){
            if (years.p[i]>years.p[j]){
                years.swap(i,j);
            }
        }
    }
    //Clear duplicate years
    for (int i=0;i<years.store-1;++i){
        for (int j=i+1;j<years.store;++j){
            if (years.p[i]==years.p[j]){
                years.sub(j);
                j--;
            }
        }
    }

    long long total_income=0, total_expense=0, net_balance;
    //Then, for each year, calculate total income, total expense, net balance
    cout<<endl;
    cout<<"\n ======= Annual Overview Statistics ======= \n";
    cout<<"Annual Overview Statistics for the following years:"<<endl;
    for (int i=0;i<wallist.w.store;++i){
        for (int j=0;j<wallist.w.p[i].is.store;++j)
            for (int k=0;k<wallist.w.p[i].is.p[j].inc.store;++k)
            {
                for (int y=0;y<years.store;++y){
                    if (wallist.w.p[i].is.p[j].inc.p[k].date.year==years.p[y]){
                        total_income+=wallist.w.p[i].is.p[j].inc.p[k].amount;
                        break;
                    }
                }
                if (wallist.w.p[i].is.p[j].inc.p[k].date.year>years.p[years.store-1]) break;
            }
        for (int j=0;j<wallist.w.p[i].ec.store;++j)
            for (int k=0;k<wallist.w.p[i].ec.p[j].exp.store;++k)
            {
                for (int y=0;y<years.store;++y){
                    if (wallist.w.p[i].ec.p[j].exp.p[k].date.year==years.p[y]){
                        total_expense+=wallist.w.p[i].ec.p[j].exp.p[k].amount;
                        break;
                    }
                }
                if (wallist.w.p[i].ec.p[j].exp.p[k].date.year>years.p[years.store-1]) break;
            }
    }
    net_balance=total_income-total_expense;
    cout<<"    Total Income: "<<total_income<<endl;
    cout<<"    Total Expense: "<<total_expense<<endl;
    cout<<"    Net Balance: "<<net_balance<<endl;
    years.dealloc();
}

void AnnualIncomeBreakdownStatistics(Wallist& wallist){
    //First, ask user for the year they want to overview
    func<int> years;
    years.alloc();
    cout<<"Please enter the year you want to overview(enter a year> current year to stop): ";
    int year_input;
    while (true){
        cin>>year_input;
        if (year_input<=GetCurrDate().year){
            years.push(year_input);
        }
        else break;
    }
    //Then sort the years array
    for (int i=0;i<years.store-1;++i){
        for (int j=i+1;j<years.store;++j){
            if (years.p[i]>years.p[j]){
                years.swap(i,j);
            }
        }
    }
    //Clear duplicate years
    for (int i=0;i<years.store-1;++i){
        for (int j=i+1;j<years.store;++j){
            if (years.p[i]==years.p[j]){
                years.sub(j);
                j--;
            }
        }
    }

    func<long long> total_income;
    total_income.alloc();
    HashMap hm = wallist.isource();
    //Set up value
    for(int i = 0; i < hm.map.store; ++i) {
        total_income.push(0); 
    }
    // Examine all wallets and their income sources
    for (int i = 0; i < wallist.w.store; ++i) {
        // Examine all income sources in the current wallet
        for (int j = 0; j < wallist.w.p[i].is.store; ++j) {
            // Standardize the name to uppercase for consistent searching
            string name = wallist.w.p[i].is.p[j].iName;
            for(int k = 0; k < name.size(); ++k) upper(name[k]); 

            // Find the index of this income source in the HashMap
            long index = hm.search(name); //

            if (index != -1) {
                // Examine all transactions in the current income source
                for (int k = 0; k < wallist.w.p[i].is.p[j].inc.store; ++k) {
                    
                    int t_year = wallist.w.p[i].is.p[j].inc.p[k].date.year;
                    bool isSelected = false;
                    for(int y = 0; y < years.store; ++y) {
                        if (years.p[y] == t_year) {
                            isSelected = true;
                            break;
                        }
                        // Since years are sorted, we can break early
                        if (years.p[y] > t_year) break; 
                    }

                    // If the transaction's year is in the selected years, add its amount
                    if (isSelected) {
                        total_income.p[index] += wallist.w.p[i].is.p[j].inc.p[k].amount;
                    }
                }
            }
        }
    }

    // Output the Annual Income Breakdown
    
    cout << "Annual Income Breakdown for the following years:";

    long long grand_total = 0;
    
    if (hm.map.store == 0) {
        cout << "No income sources found." << endl;
    } else {
        for (int i = 0; i < hm.map.store; ++i) {
            
            cout<<"Income Source: " << hm.map.p[i].name<<endl;
            cout<<"Total: " << total_income.p[i] << endl;
            grand_total += total_income.p[i];
        }
        cout<<endl << "Grand Total: " << grand_total << endl;
    }

    //Cleanup
    years.dealloc();
    total_income.dealloc();
}

void AnnualExpenseBreakdownStatistics(Wallist& wallist){
    //First, ask user for the year they want to overview
    func<int> years;
    years.alloc();
    cout<<"Please enter the year you want to overview(enter a year> current year to stop): ";
    int year_input;
    while (true){
        cin>>year_input;
        if (year_input<=GetCurrDate().year){
            years.push(year_input);
        }
        else break;
    }

    //Then sort the years array
    for (int i=0;i<years.store-1;++i){
        for (int j=i+1;j<years.store;++j){
            if (years.p[i]>years.p[j]){
                years.swap(i,j);
            }
        }
    }

    func<long long> total_expense;
    total_expense.alloc();
    HashMap hm = wallist.ecategory();

    //Set up value
    for(int i = 0; i < hm.map.store; ++i) {
        total_expense.push(0); 
    }

    // Examine all wallets and their expense categories
    for (int i = 0; i < wallist.w.store; ++i) {
        // Examine all expense categories in the current wallet
        for (int j = 0; j < wallist.w.p[i].ec.store; ++j) {
            // Standardize the name to uppercase for consistent searching
            string name = wallist.w.p[i].ec.p[j].eName;
            for(int k = 0; k < name.size(); ++k) upper(name[k]); 

            // Find the index of this expense category in the HashMap
            long index = hm.search(name); 

            if (index != -1) {
                // Examine all transactions in the current expense category
                for (int k = 0; k < wallist.w.p[i].ec.p[j].exp.store; ++k) {
                    
                    int t_year = wallist.w.p[i].ec.p[j].exp.p[k].date.year;
                    bool isSelected = false;
                    for(int y = 0; y < years.store; ++y) {
                        if (years.p[y] == t_year) {
                            isSelected = true;
                            break;
                        }
                        // Since years are sorted, we can break early
                        if (years.p[y] > t_year) break; 
                    }

                    // If the transaction's year is in the selected years, add its amount
                    if (isSelected) {
                        total_expense.p[index] += wallist.w.p[i].ec.p[j].exp.p[k].amount;
                    }
                }
            }
        }
    }

    // Output the Annual Expense Breakdown
    
    cout << "Annual Expense Breakdown for the following years:";

    long long grand_total = 0;
    
    if (hm.map.store == 0) {
        cout << "No expense categories found." << endl;
    } else {
        for (int i = 0; i < hm.map.store; ++i) {
            
            cout<<"Expense Category: " << hm.map.p[i].name<<endl;
            cout<<"Total: " << total_expense.p[i] << endl;
            grand_total += total_expense.p[i];
        }
        cout<<endl << "Grand Total: " << grand_total << endl;
    }

    //Cleanup
    years.dealloc();
    total_expense.dealloc();
}

void Statisticfunction(Wallist& wallist){
    cout<<"=======================================\n";
    cout<<"This is menu for reporting statistics"<<endl;
    cout<<"1. Time-based Statistics"<<endl;
    cout<<"2. Time-Wallet based Statistics"<<endl;
    cout<<"3. Annual Overview Statistics"<<endl;
    cout<<"4. Annual Income Breakdown Statistics"<<endl;
    cout<<"5. Annual Expense Breakdown Statistics"<<endl;
    cout<<"0. Go back to Dashboard"<<endl;
    cout<<"=======================================\n";
    cout<<"Please enter your choice: ";
    int choice;
    do{
        cin>>choice;
        if (choice<0 || choice>5) cout<<"Invalid choice, please re-enter: ";
    }while(choice<0 || choice>5);
    switch (choice){
        case 1:
            TotalBalance(wallist);
            cout << "Press Enter to go back to the dashboard...";
            cin.ignore();
            cin.get();
            break;
        case 2:
            TimeWalletStatistics(wallist);
            cout << "Press Enter to go back to the dashboard...";
            cin.ignore();
            cin.get();
            break;
        case 3:
            AnnualOverviewStatistics(wallist);
            cout << "Press Enter to go back to the dashboard...";
            cin.ignore();
            cin.get();
            break;
        case 4:
            AnnualIncomeBreakdownStatistics(wallist);
            cout << "Press Enter to go back to the dashboard...";
            cin.ignore();
            cin.get();
            break;
        case 5:
            AnnualExpenseBreakdownStatistics(wallist);
            cout << "Press Enter to go back to the dashboard...";
            cin.ignore();
            cin.get();
            break;
        case 0:
            break;
    }
}