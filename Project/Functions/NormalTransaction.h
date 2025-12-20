#pragma once

#include <iostream>
#include <ctime>
#include <fstream>
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"

int ChooseIMorEM();
bool ExamineDate(const Date&);
int chooseWallet(const Wallist&);
Date inputDate();
int chooseIS(const Wallist&);
int chooseEC(const Wallist&);
void inputRest(Transaction&);
void TransactionManagement(Wallist&); //main function!