#pragma once
#include <iostream>

using std::string;

template <typename T>
class func {
private:
    int size;
public:
    T* p;
    int store;

    void alloc() {
        if (p) return;
        p = new T[this->size];
    }

    void dealloc() {
        if(p) delete[] p;
        p=nullptr;
        size = 64;
        store = 0;
    }

    //Increase the list's size if not sufficent.
    void stretch() {
        if (!p) return;
        T* temp = new T[this->size*2];
        for (int t = 0; t < this->size; t++) {
            temp[t] = p[t];
        }
        delete[] p;
        p = temp;
        this->size*=2;
    }

    //Add a new item k to the list as the newest item (aka the highest in term of number order).
    void push(T k) {
        if (!p) return;
        while (this->store >= this->size) this->stretch();
        p[this->store] = k;
        this->store++;
    }

    //Delete item k at index x of the list.
    bool sub(int x) {
        if (x >= this->store || x < 0) return 0;
        for (int i = x; i < this->store - 1; i++) p[i] = p[i + 1];
        this->store--;
        return 1;
    }

    //Swap item at index a with item at index b.
    void swap(int a, int b) {
        if (a  < 0 || a >= store || b < 0 || b >= store || a == b) return;
        T temp = p[a];
        p[a] = p[b];
        p[b] = temp;
    }

    //Insert item at index a to index b without changing the array's stored item number.
    void insert(int a, int b) {
        if (a  < 0 || a >= store || b < 0 || b >= store || a == b) return;
        T temp = p[a];
        if (a > b) {
            for (int i = a - 1; i >= b; i--) {
                p[i + 1] = p[i];
            }
            p[b] = temp;
        }
        else {
            for (int i = a; i < b; i++) {
                p[i] = p[i + 1];
            }
            p[b] = temp;
        }
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
    ~func() {
        dealloc();
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