#pragma once

#include <iostream>
#include <fstream>
#include "../Data Structures/Cate.h"
#include "../Data Structures/Sour.h"
#include "../Data Structures/Tstn.h"
#include "../Data Structures/Wallet.h"
#include "../../Utilities/DA/Dynamicarray.h"
#include "../../Utilities/Hashmap/Hashmap.h"

//Calculate Total Balance of all Wallets and Total Balances of each wallets
//Use whenever start over the programme and in the dashboard
void DashboardStatistics(const Wallist&);

//Calculate Total Balance within a date range
void TotalBalance(const Wallist&);

//Time-Wallet based Statistics
void TimeWalletStatistics(const Wallist&);

//AnnualOverview Statistics
void AnnualOverviewStatistics(const Wallist&);

//AnnualIncomeBreakdown Statistics
void AnnualIncomeBreakdownStatistics(Wallist&);

//AnnualExpenseBreakdown Statistics
void AnnualExpenseBreakdownStatistics(Wallist&);

//main function
void Statisticfunction(Wallist&);