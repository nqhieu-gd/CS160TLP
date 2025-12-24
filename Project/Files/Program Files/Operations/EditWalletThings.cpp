#include <iostream>
#include "../../Header Files/Operations/EditWalletThings.h"
#include "../../Header Files/Operations/AddTransaction.h"

int chooseOneThing() {
    int choice;
    std::cout << "========================================================"<<std::endl;
    std::cout << "Choose one operation to proceed:\n";
    std::cout << "1. Edit Wallets.\n";
    std::cout << "2. Edit Income Sources.\n";
    std::cout << "3. Edit Expense Categories.\n";
    std::cout << "0. Return to Dashboard.\n";
    std::cin >> choice;
    std::cout << "========================================================"<<std::endl;
    if (choice < 0 || choice > 3) {
        std::cerr << "Invalid choice.\n";
        choice = chooseOneThing();
    }
    return choice;
}

int chooseOneThingVer2() {
    int choice;
    std::cout << "========================================================";
    std::cout << "Choose one operation to proceed:\n";
    std::cout << "1. Rename a Wallet.\n";
    std::cout << "2. Delete a Wallet.\n";
    std::cout << "0. Return to Dashboard.\n";
    std::cin >> choice;
    std::cout << "========================================================";
    if (choice < 0 || choice > 2) {
        std::cerr << "Invalid choice.\n";
        choice = chooseOneThingVer2();
    }
    return choice;
}

int chooseOneThingVer3() {
    int choice;
    std::cout << "========================================================";
    std::cout << "Choose one operation to proceed:\n";
    std::cout << "1. Rename an Income Source.\n";
    std::cout << "2. Delete an Income Source.\n";
    std::cout << "0. Return to Dashboard.\n";
    std::cin >> choice;
    std::cout << "========================================================";
    if (choice < 0 || choice > 2) {
        std::cerr << "Invalid choice.\n";
        choice = chooseOneThingVer3();
    }
    return choice;
}

int chooseOneThingVer4() {
    int choice;
    std::cout << "========================================================";
    std::cout << "Choose one operation to proceed:\n";
    std::cout << "1. Rename an Expense Category.\n";
    std::cout << "2. Delete an Expense Category.\n";
    std::cout << "0. Return to Dashboard.\n";
    std::cin >> choice;
    std::cout << "========================================================";
    if (choice < 0 || choice > 2) {
        std::cerr << "Invalid choice.\n";
        choice = chooseOneThingVer4();
    }
    return choice;
}

void sthsthWallet(Wallist &wallist) {
    int k  = chooseOneThingVer2();
    switch (k) {
        case 0: return;
        case 1: {
            int x = chooseWalletWhatever(wallist) - 1;
            if (x == -1) return;
            string str;
            while (1) {
                std::cout << "Enter a new name for the wallet: ";
                while (std::cin.peek() == '\n') std::cin.ignore();
                std::getline(std::cin, str);
                if (!wallist.editWal(x, str)) {
                    std::cerr << "There was already a wallet with that name!\n";
                    continue;
                }
                break;
            }
            break;
        }
        case 2: {
            int x = chooseWalletWhatever(wallist) - 1;
            if (x == -1) return;
            wallist.delWal(x);
            break;
        }
        default: break;
    }
}

void sthsthIS(Wallist &wallist) {
    int k  = chooseOneThingVer3();
    switch (k) {
        case 0: return;
        case 1: {
            int x = chooseWalletWhatever(wallist) - 1;
            if (x == -1) return;
            k = chooseISWhatever(wallist, x);
            string str;
            while (1) {
                std::cout << "Enter a new name for the income source: ";
                while (std::cin.peek() == '\n') std::cin.ignore();
                std::getline(std::cin, str);
                if (!wallist.w.p[x].editIS(k, str)) {
                    std::cerr << "There was already an income source with that name!\n";
                    continue;
                }
                break;
            }
            break;
        }
        case 2: {
            int x = chooseWalletWhatever(wallist) - 1;
            if (x == -1) return;
            k = chooseISWhatever(wallist, x);
            wallist.w.p[x].delIS(k);
            break;
        }
        default: break;
    }
}

void sthsthEC(Wallist &wallist) {
    int k  = chooseOneThingVer4();
    switch (k) {
        case 0: return;
        case 1: {
            int x = chooseWalletWhatever(wallist) - 1;
            if (x == -1) return;
            k = chooseECWhatever(wallist, x);
            string str;
            while (1) {
                std::cout << "Enter a new name for the expense category: ";
                while (std::cin.peek() == '\n') std::cin.ignore();
                std::getline(std::cin, str);
                if (!wallist.w.p[x].editEC(k, str)) {
                    std::cerr << "There was already an expense category with that name!\n";
                    continue;
                }
                break;
            }
            break;
        }
        case 2: {
            int x = chooseWalletWhatever(wallist) - 1;
            if (x == -1) return;
            k = chooseECWhatever(wallist, x);
            wallist.w.p[x].delEC(k);
            break;
        }
        default: break;
    }
}

void implementWhateverYouWant(Wallist &wallist) {
    int x = chooseOneThing();
    switch (x) {
        case 0: return;
        case 1: {
            sthsthWallet(wallist);
            break;
        }
        case 2: {
            sthsthIS(wallist);
            break;
        }
        case 3: {
            sthsthEC(wallist);
            break;
        }
        default: break;
    }
}