#include <fstream>
#include <string.h>
#include "Tstn.h"
using namespace std;

bool CheckvalidDate(const Date& c){
    int time[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};
    if (c.year % 4 == 0 && c.year % 100 != 0 || c.year % 400 == 0) time [1] = 29;
    if (c.day != time[c.month - 1]) return 0;
    return 1;
}

void inputTransactionFromFile(std::ifstream& fin, Transaction& a){
    fin.read((char*)&a.date,sizeof(Date));
    fin.read((char*)&a.amount, sizeof(a.amount));
    int lengthofstring;
    fin.read((char*)&lengthofstring, sizeof(lengthofstring));
    for (int i = 0; i <= lengthofstring; i++) a.description += "\0";
    fin.read(&a.description[0], lengthofstring);
}

void outputTransactiontoFile(std::ofstream& fout,const Transaction& a){
    fout.write((char*)&a.date,sizeof(Date));
    fout.write((char*)&a.amount,sizeof(a.amount));
    int len=a.description.length();
    fout.write((char*)&len, sizeof(len));
    fout.write(&a.description[0], len);
}

/*bool CompareDate(const Date& a, const Date& b){
    int c = a.year*10000 + a.month*100 + a.day, d = b.year*10000 + b.month*100 + b.day;
    return (c > d);
}*/

bool CompareTransaction(const Transaction& a, const Transaction& b) {
    int c = a.date.year*10000 + a.date.month*100 + a.date.day, d = b.date.year*10000 + b.date.month*100 + b.date.day;
    return (c > d);
}