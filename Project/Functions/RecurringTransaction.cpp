#include <iostream>
#include <fstream>
#include <ctime>
#include "RecurringTransaction.h"
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"
#include "../Data Structures/Wallet Info/Transaction/Auto_Trtn.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::cout;
using std::cin;
/*
//Auto add when start
void AddRecurringTransaction(Wallist& wallist){
    for (int i=0;i<wallist.w.store;i++){
        for (int j=0;j<wallist.w.p[i].is.store;++j)

    }
}
*/