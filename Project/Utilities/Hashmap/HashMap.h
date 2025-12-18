#pragma once
#include "..\\DA\\Dynamicarray.h"
#include "..\\..\\Data Structures\\Wallet Info\\Wallet.h"

using std::string;

struct HashNode {
    string name;
    string ID;

    HashNode(string n, string id);
    ~HashNode();
};

struct HashMap {
    func<HashNode> map;

    HashMap();
    ~HashMap();

    void GenSource(Wallist wlist);

    void GenCategory(Wallist wlist);
};