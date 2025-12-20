#pragma once
#include "../../../Utilities/DA/Dynamicarray.h"

struct Monthly {
    int month;
    int year;
    long long amount;

    Monthly();
    Monthly(int m, int y, long long a);
    ~Monthly();
};