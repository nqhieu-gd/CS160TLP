#include "HashMap.h"

HashNode :: HashNode(): name("") {
    IDlist.alloc();
}

HashNode :: HashNode(string n): name(n) {
    IDlist.alloc();
}

HashNode :: ~HashNode() {
    IDlist.dealloc();
}

int HashNode :: getIndexWal(int x) {
    if (x < 0 || x >= IDlist.store) return -1;
    std::string str = IDlist.p[x];
    int ind = 0;
    for (int i = 1; i < 8; i++) {
        ind *= 10;
        ind += str[i] - 48;
    }
    return ind - 1;
}

int HashNode :: getIndexLocation(int x) {
    if (x < 0 || x >= IDlist.store) return -1;
    std::string str = IDlist.p[x];
    int ind = 0;
    for (int i = 8; i < 16; i++) {
        ind *= 10;
        ind += str[i] - 48;
    }
    return ind;
}

HashMap :: HashMap() {
    map.alloc();
}

HashMap :: ~HashMap() {
    map.dealloc();
}

long HashMap :: search(string n) {
    for (int i = 0; i < map.store; i++) {
        if (n == map.p[i].name) return i;
    }
    return -1;
}

long HashMap :: insert(string n) {
    long ind = search(n);
    if (ind > -1) return ind;
    HashNode node(n);
    map.push(node);
    return map.store - 1;
}