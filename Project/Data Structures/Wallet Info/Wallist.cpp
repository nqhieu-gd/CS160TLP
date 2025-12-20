#include <iostream>
#include <fstream>
#include "Wallet.h"

using std::string;

//create a new list of wallets
Wallist :: Wallist() {
    w.alloc();
}

//clear list of wallets
Wallist :: ~Wallist() {
    w.dealloc();
}

//Create a new wallet.
void Wallist :: CreateWallet() {
    Wallet wal;
//Generate wallet's name by default.
    int s = w.store; 
    wal.wName = "Wallet number ";
    string sub = " ";
    while (s >= 10) {
        s = s/10;
        sub += " ";
    }
    s = w.store;
    int k = sub.size();
    while (k > 0) {
        sub[--k] = s%10 + 48;
        s/=10;
    }
    wal.wName += sub;
//Generate wallet's ID by default.
    k = sub.size();
    wal.wID = "W";
    for (int i = 1; i < 8 - k; i++) {
        wal.wID += "0";
    }
    wal.wID += sub;
    w.push(wal);
}

bool Wallist :: inWal(string id) {
//Create a string represent the save file of the wallet.
    string file = "..\\..\\Saved Wallet\\";
    file += id;
    file += ".bin";
    Transaction t;
    std::ifstream fin;
    fin.open(file, std::ios::binary | std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Can not find the wallet source file.";
        return 0;
    }
    fin.seekg(0, std::ios::end);
    if (fin.tellg() == 0) return 0;
    fin.seekg(0, std::ios::beg);
//If wID already presented in wallet list, update wallet of that ID, else create a new wallet.
    int k = w.store, ind = 8, temp = 0; //k represent the index of the wallet we want to update/add;
                                        //ind is for processing the size of name or id of the wallet, as well as the number of IS and EC.
                                        //temp is for processing the size of IS and EC, as well as the number of transactions of each type.
    for (int i = 0; i < k; i++) {
        if (w.p[i].wID == id) {
            k = i;
            w.p[k].is.dealloc();
            w.p[k].is.alloc();
            w.p[k].ec.dealloc();
            w.p[k].ec.alloc();
            break;
        }
    }
    if (k == w.store) {
        CreateWallet();
    }
//Input wallet ID.
    w.p[k].wID = "W       ";
    fin.read(&w.p[k].wID[1], 7);
//Input the wallet's name.
    fin.read((char*) &ind, 4);
    if (w.p[k].wName.size()) w.p[k].wName.erase(0, w.p[k].wName.size());
    w.p[k].wName.resize(ind, ' ');
    fin.read(&w.p[k].wName[0], ind);
//Get the number of income sources and start inputting them.
    fin.read((char*) &ind, 4);
    for (int i = 0; i < ind; i++) {
        IncomeSource istemp;
    //Input income source's ID.
        istemp.iID.resize(0);
        istemp.iID.resize(8, '0');
        fin.read(&istemp.iID[0], 8);
    //Input income source's name.
        fin.read((char*) &temp, 4);
        if (istemp.iName.size()) istemp.iName.erase(0, istemp.iName.size());
        istemp.iName.resize(temp, ' ');
        fin.read(&istemp.iName[0], temp);
    //Input the number of transactions and start inputting them.
        fin.read((char*) &temp, 4);
        for (int j = 0; j < temp; j++) {
            inputTransactionFromFile(fin, t);
            istemp.inc.push(t);
        }
        w.p[k].is.push(istemp);
        istemp.inc.dealloc();
    }
//Tread similarly with expense categories.
    fin.read((char*) &ind, 4);
    for (int i = 0; i < ind; i++) {
        ExpenseCategory ectemp;
    //Input expense category's ID.
        ectemp.eID.resize(0);
        ectemp.eID.resize(8, '0');
        fin.read(&ectemp.eID[0], 8);
    //Input expense category's name.
        fin.read((char*) &temp, 4);
        ectemp.eName.erase(0, ectemp.eName.size());
        ectemp.eName.resize(temp, ' ');
        fin.read(&ectemp.eName[0], temp);
    //Input the number of transactions and start inputting them.
        fin.read((char*) &temp, 4);
        for (int j = 0; j < temp; j++) {
            inputTransactionFromFile(fin, t);
            ectemp.exp.push(t);
        }
        w.p[k].ec.push(ectemp);
        ectemp.exp.dealloc();
    }
    fin.close();
    return 1;
}

HashMap Wallist :: isource() {
    HashMap hm;
    for (int i = 0; i < w.store; i++) {
        for (int j = 0; j < w.p[i].is.store; j++) {
            string str = w.p[i].is.p[j].iName;
            string sub = w.p[i].wID + w.p[i].is.p[j].iID;
            for (int k = 0; k < str.size(); k++) {
                upper(str[k]);
            }
            int check = hm.insert(str);
            hm.map.p[check].IDlist.push(sub);
        }
    }
    return hm;
}

HashMap Wallist :: ecategory() {
    HashMap hm;
    for (int i = 0; i < w.store; i++) {
        for (int j = 0; j < w.p[i].ec.store; j++) {
            string str = w.p[i].ec.p[j].eName;
            string sub = w.p[i].wID + w.p[i].ec.p[j].eID;
            for (int k = 0; k < str.size(); k++) {
                upper(str[k]);
            }
            int check = hm.insert(str);
            hm.map.p[check].IDlist.push(sub);
        }
    }
    return hm;
}

//Output list of IS and EC to files.
void Wallist :: outSC() {
    std::ofstream fout;
    fout.open("..\\..\\Utility Save Files\\Income.bin", std::ios::binary);
    if (!fout.is_open()) {
        std::cerr << "Can not find the income sources list file.";
        return;
    }
    HashMap hm = isource();
    int k = hm.map.store;
    fout.write((char*) &k, 4);
    for (int i = 0; i < hm.map.store; i++) {
        k = hm.map.p[i].name.size();
        fout.write((char*) &k, 4);
        fout.write((char*) &hm.map.p[i].name[0], k);
        k = hm.map.p[i].IDlist.store;
        fout.write((char*) &k, 4);
        for (int j = 0; j < k; j++) {
            fout.write((char*) &hm.map.p[i].IDlist.p[j][0], 16);
        }
    }
    fout.close();
    fout.open("..\\..\\Utility Save Files\\Expense.bin", std::ios::binary);
    if (!fout.is_open()) {
        std::cerr << "Can not find the income expense categories list file.";
        return;
    }
    hm = ecategory();
    k = hm.map.store;
    fout.write((char*) &k, 4);
    for (int i = 0; i < hm.map.store; i++) {
        k = hm.map.p[i].name.size();
        fout.write((char*) &k, 4);
        fout.write((char*) &hm.map.p[i].name[0], k);
        k = hm.map.p[i].IDlist.store;
        fout.write((char*) &k, 4);
        for (int j = 0; j < k; j++) {
            fout.write((char*) &hm.map.p[i].IDlist.p[j][0], 16);
        }
    }
    fout.close();
}

//Delete a wallet.
void Wallist :: delWal(int x) {
    std::ofstream fout;
    fout.open("..\\..\\Utility Save Files\\DeletedWallet.bin", std::ios::binary);
    fout.write((char*) &w.p[w.store - 1].wID[0], 8);
    if (w.sub(x)) {
        for (int i = x - 1; i < w.store; i++) {
            for (int j = 7; j >= 0; j--) {
                if (w.p[i].wID[j] == '0') {
                    w.p[i].wID[j] = '9';
                    continue;
                }
                w.p[i].wID[j]--;
                break;
            }
        }
    }
    fout.close();
    outWallist();
}

//Output list of wallets to files.
void Wallist :: outWallist() {
    std::fstream file;
    string str = "W0000001";
    string term = "W0000000";
    file.open("..\\..\\Utility Save Files\\DeletedWallet.bin", std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::end);
    if (file.tellg() != 0) file.read((char*) &term[0], 8);
    file.close();
    int ind = 0;
    while (str != term && ind < w.store) {
        ind = 0;
        for (int i = 1; i < 8; i++) {
            ind += ind*9 + str[i] - 48;
        }
        w.p[ind - 1].outWal();
        for (int i = 7; i >= 0; i--) {
            if (str[i] == '9') {
                str[i] = '0';
                continue;
            }
            str[i]++;
            break;
        }
    }
    if (term != "W0000000") {
        term = "..\\..\\Saved Wallet\\" + term;
        file.open(term, std::ios::out | std::ios::binary);
        file.close();
    }
}