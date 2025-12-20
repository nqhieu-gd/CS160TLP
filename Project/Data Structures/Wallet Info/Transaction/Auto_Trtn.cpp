#include <iostream>
#include <ctime>
#include <fstream>
#include "Auto_Trtn.h"

using std::ifstream;
using std::ofstream;

void Auto_Transaction_List :: init(){
    if (atm.p==nullptr){
        atm.alloc();   
    }
}

void Auto_Transaction_List :: clear(){
    atm.dealloc();
}

//Read from file
void Auto_Transaction_List :: readatm(ifstream& fin){
    init();
    // Get number of auto trtn:
    int count=0;
    fin.read((char*)&count, sizeof(int));
    //Get each auto trtn:
    for (int i = 0;i < count; ++i){
        Auto_Transaction temp;
        //First, get the start Date->end Date->last Date
        fin.read((char*)&temp.start_date,sizeof(Date));
        fin.read((char*)&temp.end_date,sizeof(Date));
        fin.read((char*)&temp.last_add,sizeof(Date));
        //Then, get the information like a normal transaction
        inputTransactionFromFile(fin,temp.transaction);
        atm.push(temp);
    }
    //After finish reading the atm, then will erase some expired transactions
    checkexpired();
}

//Update to file
void Auto_Transaction_List :: writeatm(ofstream& fout){
    //First, number of autotransaction
    fout.write((char*) &atm.store,sizeof(int));
    //Print each auto transaction
    for (int i=0;i<atm.store;++i){
        //First, print start Date->end Date-> last Date
        fout.write((char*)&atm.p[i].start_date,sizeof(Date));
        fout.write((char*)&atm.p[i].end_date,sizeof(Date));
        fout.write((char*)&atm.p[i].last_add,sizeof(Date));
        //Then, print the information like a normal transaction
        outputTransactiontoFile(fout,atm.p[i].transaction);
    }
}

//Erase the tstn number k (index: k-1)
void Auto_Transaction_List:: erase(int k){
    atm.sub(k);
}

//Erase all the tstn not available
void Auto_Transaction_List:: checkexpired(){
    for (int i=0;i<atm.store;++i)
        //Check if the autotransaction is infinite?
        if (atm.p[i].end_date.day==0&&atm.p[i].end_date.month==0&&atm.p[i].end_date.year==0) continue;
        else if (CompareDate(GetCurrDate(),atm.p[i].end_date)){
            erase(i + 1);
            i--;
        }
}