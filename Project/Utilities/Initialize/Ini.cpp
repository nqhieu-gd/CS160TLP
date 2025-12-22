#include <fstream>
#include "Ini.h"

void iniSaveNum() {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("Utility Save Files/WalletNumber.bin", std::ios::binary);
    if (!fin.is_open()) {
        fout.open("Utility Save Files/WalletNumber.bin", std::ios::binary);
        fout.close();
    }
    else fin.close();
}

void iniInwal() {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("Saved Wallet/W0000001.bin", std::ios::binary);
    if (!fin.is_open()) {
        fout.open("Saved Wallet/W0000001.bin", std::ios::binary);
        fout.close();
    }
    else fin.close();
}

void ini() {
    iniSaveNum();
    iniInwal();
}