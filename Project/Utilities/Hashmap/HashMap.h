#pragma once
#include "../DA/Dynamicarray.h"

using std::string;

struct HashNode {
    string name;
    func<string> IDlist;

    HashNode();
    HashNode(string n);
    ~HashNode();
};

struct HashMap {
    func<HashNode> map;

    HashMap();
    ~HashMap();

    long search(string n);

    long insert(string n);
};