#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"
#include "../Data Structures/Wallet Info/Transaction/Auto_Trtn.h"

//We have 3 main functions:
//Auto add when start
//Add new recurring transaction
//Delete a recurring transaction


//Auto add when start
void AddRecurringTransaction(Wallist& wallist);