#include "HashMap.h"
#include <fstream>

HashNode :: HashNode(string n, string id): name(n), ID(id) {}

HashNode :: ~HashNode() {}

HashMap :: HashMap() {
    map.alloc();
}

HashMap :: HashMap(Wallist wlist) {
    map.alloc();
}

HashMap :: ~HashMap() {
    map.dealloc();
}

void HashMap :: GenSource() {
    std::ofstream fout;
    fout.open("..\\..\\Utility Save Files\\SourceList.bin", std::ios::binary);
    if (!fout.is_open() || !fout) {
        std::cerr << "Can not find the income sources list.";
        return;
    }
}

void HashMap :: GenCategory() {}