#include <iostream>
#include <ctime>
#include <fstream>
#include "Auto_Trtn.h"

using std::ifstream;
using std::ofstream;

int Auto_Transaction::autoadd() {
    Date end_count;
    
    // 1. Xác định mốc kết thúc (Limit Date)
    // Nếu có End Date và End Date < Hôm nay -> Lấy End Date. Ngược lại lấy Hôm nay.
    if (end_date.day != 0 && CompareDate(GetCurrDate(), end_date)) {
        end_count = end_date;
    } else {
        end_count = GetCurrDate();
    }

    // Nếu Start Date > End Count -> Chưa đến lúc bắt đầu -> Trả về 0
    if (CompareDate(start_date, end_count)) return 0;

    // 2. Tính Tọa độ tháng hiện tại (Current Limit)
    // Công thức: year * 12 + month
    int current_total_months = end_count.year * 12 + end_count.month;

    // === XỬ LÝ NGÀY TRONG THÁNG (Logic quan trọng nhất) ===
    int maxday[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Check năm nhuận cho end_count (để xác định ngày cuối tháng 2)
    if (end_count.year % 400 == 0 || (end_count.year % 4 == 0 && end_count.year % 100 != 0)) {
        maxday[1] = 29; // Tháng 2 là index 1
    }

    // Kiểm tra: Hôm nay đã "qua" ngày đến hạn chưa?
    // Qua hạn khi: (Ngày hiện tại >= Ngày Start) HOẶC (Hôm nay là ngày cuối cùng của tháng)
    bool is_pass_due = (end_count.day >= start_date.day) || (end_count.day == maxday[end_count.month - 1]);

    // Nếu chưa qua hạn, nghĩa là tháng này chưa được tính -> Trừ đi 1 tháng
    if (!is_pass_due) {
        current_total_months--;
    }

    // 3. Tính Tọa độ tháng của lần Add cuối (Last Add)
    int last_added_months;
    if (last_add.day == 0) {
        // Nếu chưa add lần nào: Coi như lần add cuối là "tháng trước" của start_date
        // Để khi trừ ra sẽ tính cả tháng start_date
        last_added_months = start_date.year * 12 + start_date.month - 1;
    } else {
        last_added_months = last_add.year * 12 + last_add.month;
    }

    // 4. Kết quả = Hiệu số
    int needed = current_total_months - last_added_months;

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