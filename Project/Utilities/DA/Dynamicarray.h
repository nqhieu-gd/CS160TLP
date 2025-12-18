#pragma once
#include <iostream>

using std::string;

template <typename T>
class func {
public:
    T* p;
    int size = 64, store = 0;

    void alloc() {
        p = new T[this->size];
    }

    void dealloc() {
        if(p) delete[] p;
        size = 64;
        store = 0;
    }

    //Increase the list's size if not sufficent
    void stretch() {
        T* temp = new T[this->size*2];
        for (int t = 0; t < this->size; t++) {
            temp[t] = p[t];
        }
        delete[] p;
        p = temp;
        this->size*=2;
    }

    //Add a new item k to the list as the newest item (aka the highest in term of number order)
    void push(T k) {
        while (this->store >= this->size) this->stretch();
        p[this->store] = k;
        this->store++;
    }

    //Delete item k at index x of the list
    void sub(int x) {
        if (x > this->store) return;
        for (int i = x - 1; i < this->store - 1; i++) p[i] = p[i + 1];
        this->store--;
    }

    //Create a completely new array with default constructor.
    func() {
        p = nullptr;
        size = 64;
        store = 0;
    }

    //Create a copy of the pdif array.
    func(const func& pdif) {
        size = pdif.size;
        store = pdif.store;
        
        if (pdif.size > 0) {
            p = new T[size];
            for (int i = 0; i < store; i++) {
                p[i] = pdif.p[i];
            }
        } else {
            p = nullptr;
        }
    }

    //Adjust the "=" operator so that it transfer real data, used in sub(int x) (haven't touched yet tho).
    func& operator=(const func& pdif) {
        if (this == &pdif) return *this;
        
        if (p != nullptr) {
            delete[] p;
        }
        
        size = pdif.size;
        store = pdif.store;
        if (size > 0) {
            p = new T[size];
            for (int i = 0; i < store; i++) {
                p[i] = pdif.p[i];
            }
        } else {
            p = nullptr;
        }
        return *this;
    }
};