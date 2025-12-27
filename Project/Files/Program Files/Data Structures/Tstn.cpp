#include <fstream>
#include "../../Header Files/Data Structures/Tstn.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

bool CheckvalidDate(const Date& c){
    int time[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};
    if ((c.year % 4 == 0 && c.year % 100 != 0) || c.year % 400 == 0) time [1] = 29;
    if (c.month < 1 || c.month > 12 || c.day > time[c.month - 1] || c.day < 1) return 0;
    return 1;
}

void inputTransactionFromFile(std::ifstream& fin, Transaction& a){
    fin.read((char*)&a.date,sizeof(Date));
    fin.read((char*)&a.amount, sizeof(a.amount));
    int lengthofstring;
    fin.read((char*)&lengthofstring, sizeof(lengthofstring));
    if (lengthofstring) {
        a.description.resize(lengthofstring);
        fin.read(&a.description[0], lengthofstring);
    } else {
        a.description.clear(); 
    }
}

void outputTransactiontoFile(std::ofstream& fout,const Transaction& a){
    fout.write((char*)&a.date,sizeof(Date));
    fout.write((char*)&a.amount,sizeof(a.amount));
    int len=a.description.length();
    fout.write((char*)&len, sizeof(len));
    if (a.description != "") fout.write(&a.description[0], len);
}

bool CompareDate(const Date& a, const Date& b){
    int c = a.year*10000 + a.month*100 + a.day, d = b.year*10000 + b.month*100 + b.day;
    return (c > d);
}

//Check if the Date is suitable
bool ExamineDate(const Date& a){
    if (!CheckvalidDate(a)) return false;
    if (CompareDate(a,GetCurrDate())) return false;
    return true;
}

//Input Date
Date inputDate(){
    cout<<"========================================================"<<endl;
    cout<<endl;
    cout<<"1. Get current Date"<<endl;
    cout<<"2. Enter the date manually (Note: this function does not accept future dates)"<<endl;
    cout<<endl;
    cout<<"========================================================"<<endl;
    cout<<"Please enter the utility: ";
    int choose;
    while (true) {
        cin >> choose;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid input! Please enter a number: ";
        } else {
            cin.ignore(32767, '\n');
            break;
        }
    }
    if (choose < 1 || choose >2) {
        std::cerr << "Invalid option. Please try again!\n";
        return inputDate();
    }
    else if (choose==1) return GetCurrDate();
    cout<<"Please input the Date (format: dd mm yyyy): ";
    Date a;
    while (true) {
        cout << "Please input the Date (format: dd mm yyyy): ";
        cin >> a.day >> a.month >> a.year;
        if (cin.fail()) {
            cin.clear();          
            cin.ignore(32767, '\n'); 
            cout << "Invalid format! Please enter numbers only.\n";
        } 
        else if (!ExamineDate(a)) {
            cout << "Invalid Date ! Please try again.\n";
        } 
        else {
            cin.ignore(32767, '\n');
            break; 
        }
    }
    return a;
}
Transaction ipt() {
    Transaction t;
    t.date = inputDate();
    cout << "Enter the amount of money: ";
    while (true){
        cin >> t.amount;
        if (cin.fail()) {
            cin.clear();          
            cin.ignore(32767, '\n'); 
            cout << "Invalid amount! Please enter a number: ";
        } 
        else if (t.amount < 0) {
            cout << "Amount cannot be negative! Please try again: ";
        } 
        else {
            cin.ignore(32767, '\n');
            break; 
        }
    }
    return t;
}

//Get current Date
Date GetCurrDate(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Date a;
    a.year = 1900 + ltm->tm_year; 
    a.month = 1 + ltm->tm_mon;   
    a.day = ltm->tm_mday;
    return a;
}