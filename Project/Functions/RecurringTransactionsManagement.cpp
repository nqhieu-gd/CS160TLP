#include <iostream>
#include <ctime>
#include <fstream>
#include "RecurringTransactionsManagement.h"
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"
#include "TransactionManagement.h"

void Auto_Transaction_Management :: init(){
    if (atm.p==nullptr){
        atm.alloc();
    }
}

void Auto_Transaction_Management :: clear(){
    atm.dealloc();
}

//Read from file
void Auto_Transaction_Management :: read(){
    ifstream fin;
    fin.open("autotstn.bin",std::ios::binary);
    if (!fin){
        std::cerr<<"Error opening autotstn.bin for reading!"<<std::endl;
        return;
    }
    int count;
    fin.read((char*)&count,sizeof(count));
    atm.store=count;
    for (int i=0;i<count;++i){
        Auto_Transaction at;
        fin.read((char*)&at.transaction.date,sizeof(Date));
        fin.read((char*)&at.transaction.amount, sizeof(at.transaction.amount));
        int lengthofstring;
        fin.read((char*)&lengthofstring, sizeof(lengthofstring));
        if (lengthofstring) {
            at.transaction.description.resize(lengthofstring);
            fin.read(&at.transaction.description[0], lengthofstring);
        } else {
            at.transaction.description.clear(); 
        }
        fin.read((char*)&at.last_add,sizeof(Date));
        fin.read((char*)&at.start_date,sizeof(Date));
        fin.read((char*)&at.end_date,sizeof(Date));
        atm.push(at);
    }
}

//Update to file
void Auto_Transaction_Management :: write(){
    ofstream fout;
    fout.open("autotstn.bin",std::ios::binary);
    if (!fout){
        std::cerr<<"Error opening autotstn.bin for writing!"<<std::endl;
        return;
    }
    int count=atm.store;
    fout.write((char*)&count,sizeof(count));
    for (int i=0;i<count;++i){
        Auto_Transaction at=atm.p[i];
        fout.write((char*)&at.transaction.date,sizeof(Date));
        fout.write((char*)&at.transaction.amount, sizeof(at.transaction.amount));
        int lengthofstring=at.transaction.description.size();
        fout.write((char*)&lengthofstring, sizeof(lengthofstring));
        if (lengthofstring) {
            fout.write(at.transaction.description.c_str(), lengthofstring);
        }
        fout.write((char*)&at.last_add,sizeof(Date));
        fout.write((char*)&at.start_date,sizeof(Date));
        fout.write((char*)&at.end_date,sizeof(Date));
    }
}

//Erase the tstn number k (index: k-1)
void Auto_Transaction_Management:: erase(int k){
    atm.sub(k);
}

//Erase all the tstn not available
void Auto_Transaction_Management:: checkexpired(){
    for (int i=0;i<atm.store;++i)
        if (CompareDate(GetCurrDate(),atm.p[i].end_date)){
            erase(i--);
            --atm.store;
        }
}

//Auto add Transaction (when starts the programme)
void autoadd(){ //If the date is ok ->add
    Auto_Transaction_Management temp;
    temp.init();
    temp.read();
    temp.checkexpired();
    for (int i=0;i<temp.atm.store;++i){
        //Check if last_add=0/0/0 and start_date<=CurrDate<=end_date -> add
        //If last_add!=0/0/0 -> check if start_date<=CurrDate<=end_date and CurrDate-last_add~>1 month =>add
    }


    temp.clear();
}
//Show list of auto transactions:
void OutputListAutoTrtn(const Auto_Transaction_Management& a){

}