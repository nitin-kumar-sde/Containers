#pragma once
#include <cstring>
#include <iostream>

namespace mystl {

class string {
private:
    char* data;
    size_t len;

public:
    string() : data(new char[1]{'\0'}), len(0) {}

    string(const char* str) {
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
    }

    string(const string& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
    }

    string& operator=(const string& other) {
        if (this != &other) {
            delete[] data;
            len = other.len;
            data = new char[len + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    string(string&& other) noexcept : data(other.data), len(other.len) {
        other.data = nullptr;
        other.len = 0;
    }

    // Move Assignment
    string& operator=(string&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            len = other.len;
            other.data = nullptr;
            other.len = 0;
        }
        return *this;
    }

    ~string() {
        delete[] data;
    }

    // Size
    size_t size() const {
        return len;
    }

    // Operator []
    char& operator[](size_t index) {
        return data[index];
    }

    const char& operator[](size_t index) const {
        return data[index];
    }

    // Append
    string& operator+=(const string& rhs) {
        char* new_data = new char[len + rhs.len + 1];
        strcpy(new_data, data);
        strcat(new_data, rhs.data);
        delete[] data;
        data = new_data;
        len += rhs.len;
        return *this;
    }

    string& operator+=(char c) {
        char* new_data = new char[len + 2];
        strcpy(new_data, data);
        new_data[len] = c;
        new_data[len + 1] = '\0';
        delete[] data;
        data = new_data;
        ++len;
        return *this;
    }

    // Concatenation
    friend string operator+(string lhs, const string& rhs) {
        lhs += rhs;
        return lhs;
    }

    friend bool operator==(const string& lhs, const string& rhs) {
        return strcmp(lhs.data, rhs.data) == 0;
    }

    friend bool operator!=(const string& lhs, const string& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const string& lhs, const string& rhs) {
        return strcmp(lhs.data, rhs.data) < 0;
    }

    friend bool operator>(const string& lhs, const string& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const string& lhs, const string& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const string& lhs, const string& rhs) {
        return !(lhs < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const string& str) {
        os << str.data;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, string& str) {
        char buffer[1000];
        is >> buffer;
        str = string(buffer);
        return is;
    }
};

}
