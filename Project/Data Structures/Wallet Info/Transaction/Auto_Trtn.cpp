#include <iostream>
#include <ctime>
#include <fstream>
#include "Auto_Trtn.h"

using std::ifstream;
using std::ofstream;
//identify how many times need to auto add transaction
int Auto_Transaction::autoadd() {
    Date end_count;
    
    //Identify the end date for counting
    if (end_date.day != 0 && CompareDate(GetCurrDate(), end_date)) {
        end_count = end_date;
    } else {
        end_count = GetCurrDate();
    }
    if (CompareDate(start_date, end_count)) return 0;

    //Compute the number of months between start_date and end_count
    int current_total_months = end_count.year * 12 + end_count.month;
    int maxday[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (end_count.year % 400 == 0 || (end_count.year % 4 == 0 && end_count.year % 100 != 0)) {
        maxday[1] = 29; 
    }

    //Check if the current month has passed the day of start_date
    bool is_pass_due = (end_count.day >= start_date.day) || (end_count.day == maxday[end_count.month - 1]);

    //If not passed, decrease one month
    if (!is_pass_due) {
        current_total_months--;
    }

    //Calculate the number of months last added
    int last_added_months;
    if (last_add.day == 0) {
        // If never added before, use start_date
        last_added_months = start_date.year * 12 + start_date.month - 1;
    } else {
        last_added_months = last_add.year * 12 + last_add.month;
    }
    //Calculate how many times need to add
    int needed = current_total_months - last_added_months;
    if (needed < 0) needed = 0; 
    if (needed > 0) {
        //Update last_add date
        last_add = GetCurrDate();
    }
    return needed;
}


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
    atm.sub(k - 1);
}

//Erase all the tstn not available
void Auto_Transaction_List:: checkexpired(){
    for (int i=0;i<atm.store;++i)
        //Check if the autotransaction is infinite?
        if (atm.p[i].end_date.day==0&&atm.p[i].end_date.month==0&&atm.p[i].end_date.year==0) continue;
        else if (CompareDate(GetCurrDate(),atm.p[i].end_date)){
            atm.sub(i--);
        }
}