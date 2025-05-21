#pragma once
#include <memory>
#include <stdexcept>
using namespace std;

namespace mystl {

template<typename T>
class vector {
private:
    T* data;
    int nextIndex;
    int capacity;

public:
    // default constructor
    vector() {
        data = new T[5];
        nextIndex = 0;
        capacity = 5;
    }

    // constructor with size
    vector(int size) {
        data = new T[size];
        nextIndex = 0;
        capacity = size;
    }

    // constructor with size and initial value
    vector(int size, T value) {
        data = new T[size];
        nextIndex = size;
        capacity = size;
        for (int i = 0; i < size; i++)
            data[i] = value;
    }

    // copy constructor
    vector(const vector& v) {
        data = new T[v.capacity];
        for (int i = 0; i < v.nextIndex; i++)
            data[i] = v.data[i];
        nextIndex = v.nextIndex;
        capacity = v.capacity;
    }

    // assignment operator
    vector& operator=(const vector& v) {
        if (this != &v) {
            delete[] data;
            data = new T[v.capacity];
            for (int i = 0; i < v.nextIndex; i++)
                data[i] = v.data[i];
            nextIndex = v.nextIndex;
            capacity = v.capacity;
        }
        return *this;
    }

    // destructor
    ~vector() {
        delete[] data;
    }

    // push element to end
    void push_back(T element) {
        if (nextIndex == capacity) {
            T* newData = new T[2 * capacity];
            for (int i = 0; i < capacity; i++)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity *= 2;
        }
        data[nextIndex++] = element;
    }

    // replace element at index
    void replace(int index, T element) {
        if (index < nextIndex) {
            data[index] = element;
        } else if (index == nextIndex) {
            push_back(element);
        } else {
            throw out_of_range("Index out of bounds for replace");
        }
    }

    // get element
    T get(int index) const {
        if (index < nextIndex) {
            return data[index];
        }
        throw out_of_range("Index out of bounds for get");
    }

    // operator[] overloading
    T& operator[](int index) {
        if (index < 0 || index >= nextIndex) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= nextIndex) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // return current size
    int size() const {
        return nextIndex;
    }

    // return current capacity
    int get_capacity() const {
        return capacity;
    }

    // check if vector is empty
    bool empty() const {
        return nextIndex == 0;
    }
};

}
