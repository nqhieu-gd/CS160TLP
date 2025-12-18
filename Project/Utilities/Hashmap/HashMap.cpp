#include "HashMap.h"

HashNode :: HashNode(string n): name(n) {
    IDlist.alloc();
}

HashNode :: ~HashNode() {
    IDlist.dealloc();
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