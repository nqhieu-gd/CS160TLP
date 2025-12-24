#include <fstream>
#include "../../Header Files/Operations/Ini.h"

void iniSaveNum() {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("Personal Financial Management App/Save Files/Utility Save Files/WalletNumber.bin", std::ios::binary);
    if (!fin.is_open()) {
        fout.open("Utility Save Files/WalletNumber.bin", std::ios::binary);
        fout.close();
    }
    else fin.close();
}

void iniInwal() {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("Personal Financial Management App/Save Files/Saved Wallet/W0000001.bin", std::ios::binary);
    if (!fin.is_open()) {
        fout.open("Personal Financial Management App/Save Files/Saved Wallet/W0000001.bin", std::ios::binary);
        fout.close();
    }
    else fin.close();
}

void ini() {
    iniSaveNum();
    iniInwal();
}