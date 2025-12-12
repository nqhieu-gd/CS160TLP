#include <iostream>

using std::string;

template <typename T>
class func {
public:
    T* p;
    int size = 1024, store = 0;

    void alloc() {
        p = new T[this->size];
    }

    void dealloc() {
        delete[] p;
    }

    void stretch() {
        T* temp = new T[this->size*2]
        for (int t = 0; t < this->size; t++) {
            temp[t] = p[t];
        }
        delete[] p;
        p = temp;
        this->size*=2;
    }

    void push(T k) {
        while (store >= size) this->stretch();
        p[store] = k;
        store++;
    }
};

