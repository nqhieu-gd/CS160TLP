#pragma once
#include <iostream>

inline void upper(char &a) {
    if (a >= 97 && a <= 122) a = a - 32;
}

inline void upperStr(std::string &str) {
    for (int i = 0; i < str.size(); i++) {
        upper(str[i]);
    }
}