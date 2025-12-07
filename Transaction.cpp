#include <iostream>
#include <fstream>
#include <string.h>
#include "Transaction.h"
using namespace std;

bool CheckvalidDate(Date);
void inputTransactionFromConsole(Transaction&);
void inputTransactionFromFile(ifstream&,Transaction&);
void outputTransactiontoFile(std::ofstream&,Transaction);