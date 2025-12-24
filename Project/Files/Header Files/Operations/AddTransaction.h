#pragma once

#include <iostream>
#include <fstream>
#include "../Data Structures/Cate.h"
#include "../Data Structures/Sour.h"
#include "../Data Structures/Tstn.h"
#include "../Data Structures/Wallet.h"
#include "../../Utilities/DA/Dynamicarray.h"

int ChooseIMorEM();
int chooseWallet(const Wallist&);
int chooseWalletWhatever(const Wallist& wallist);
int chooseIS(const Wallist&, int index);
int chooseISWhatever(Wallist& wallist, int index);
int chooseEC(const Wallist&, int index);
int chooseECWhatever(Wallist& wallist, int index);
void inputRest(Transaction&);
void TransactionManagement(Wallist&); //main function!
void inWallist(Wallist &wallist);