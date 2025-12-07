#pragma once
#include <iostream>

using std::string;

template <typename T>
class func {
public:
    T* p;
    int size = 0, store = 0;

    void alloc() {
        p = new T[this->size];
    }

    void dealloc() {
        delete[] p;
    }

    //increase the list's capacity if not sufficent
    void stretch() {
        T* temp = new T[this->size*2 + 1]
        for (int t = 0; t < this->size; t++) {
            temp[t] = p[t];
        }
        delete[] p;
        p = temp;
        this->size*=2;
        this->size+=1;
    }

    //add a new item k to the list as the newest item (aka the highest in term of number order)
    void push(T k) {
        while (this->store >= this->size) this->stretch();
        p[this->store] = k;
        this->store++;
    }

    //delete item k at index x of the list
    void sub(T k, int x) {
        if (x > this->store) return;
        for (int i = x - 1; i < this->store - 1; i++) p[i] = p[i + 1];
        this->store--;
    }
};