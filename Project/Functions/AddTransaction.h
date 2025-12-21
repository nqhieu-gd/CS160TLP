#pragma once

#include <iostream>
#include <fstream>
#include "../Utilities/DA/Dynamicarray.h"
#include "../Data Structures/Wallet Info/Wallet.h"
#include "../Data Structures/Expense Category/Cate.h"
#include "../Data Structures/Income Source/Sour.h"
#include "../Data Structures/Wallet Info/Transaction/Tstn.h"

int ChooseIMorEM();
int chooseWallet(const Wallist&);
int chooseIS(const Wallist&, int index);
int chooseEC(const Wallist&, int index);
void inputRest(Transaction&);
void TransactionManagement(Wallist&); //main function!