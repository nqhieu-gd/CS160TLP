#include "HashMap.h"
#include <fstream>

HashNode :: HashNode(string n, string id): name(n), ID(id) {}

HashNode :: ~HashNode() {}

HashMap :: HashMap() {
    map.alloc();
}

HashMap :: ~HashMap() {
    map.dealloc();
}

void HashMap :: GenSource(Wallist wlist) {
    std::ofstream fout;
    fout.open("..\\..\\Utility Save Files\\SourceList.bin");
}

void HashMap :: GenCategory(Wallist wlist) {}