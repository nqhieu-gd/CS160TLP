#pragma once
#include "../DA/Dynamicarray.h"
#include "iostream"

using std::string;

struct HashNode {
    string name;
    func<string> IDlist;

    HashNode();
    HashNode(string n);
    ~HashNode();

    int getIndexWal(int x);
    int getIndexLocation(int x);
};

struct HashMap {
    func<HashNode> map;

    HashMap();
    ~HashMap();

    long search(string n);

    long insert(string n);
};