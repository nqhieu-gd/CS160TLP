#include <iostream>
#include <fstream>
#include <string.h>
#include "Transaction.h"
using namespace std;

bool CheckvalidDate(const Date& c){
    switch (c.month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: if (c.day>=1&&c.day<=31) return 1;
                 else return 0;
        case 4:
        case 6:
        case 9:
        case 11: if (c.day>=1&&c.day<=31) return 1;
                 else return 0;
        case 2: if (c.year%400==0||(c.year%4==0&&c.year%100!=0))
                    if (c.day>=1&&c.day<=29) return 1;
                    else return 0;
                else if (c.day>=1&&c.day<=28) return 1;
                    else return 0;
        default: return 0;
    }
}
void inputTransactionFromFile(ifstream& fin,Transaction& a){
    fin.read((char*)&a.date,sizeof(Date));
    fin.read((char*)&a.amount, sizeof(a.amount));
    int lengthofstring;
    fin.read((char*)&lengthofstring, sizeof(lengthofstring));
    a.description.resize(lengthofstring);
    fin.read(&a.description[0], lengthofstring);
}
void outputTransactiontoFile(std::ofstream& fout,const Transaction& a){
    fout.write((char*)&a.date,sizeof(Date));
    fout.write((char*)&a.amount,sizeof(a.amount));
    int len=a.description.length();
    fout.write((char*)&len, sizeof(len));
    fout.write(&a.description[0],len*sizeof(char));
}
int CompareTransaction(const Transaction& a, const Transaction& b){
    if (a.date.year<b.date.year) return 1;
    if (b.date.year<a.date.year) return -1;
    if (a.date.month<b.date.month) return 1;
    if (b.date.month<a.date.month) return -1;
    if (a.date.day<b.date.day) return 1;
    if (b.date.day<a.date.day) return -1;
    return 0;
}