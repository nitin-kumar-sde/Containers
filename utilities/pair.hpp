#pragma once

namespace mystl {

template <typename T1, typename T2>
class pair {
public:
    T1 first;
    T2 second;
    
    pair() : first(), second() {}

    pair(const T1& a, const T2& b) : first(a), second(b) {}

    pair(const pair<T1, T2>& other) : first(other.first), second(other.second) {}

    pair& operator=(const pair<T1, T2>& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
};

// Comparison operators
template <typename T1, typename T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs == rhs);
}

template <typename T1, typename T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <typename T1, typename T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(rhs < lhs);
}

template <typename T1, typename T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return rhs < lhs;
}

template <typename T1, typename T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs < rhs);
}

template <typename T1, typename T2>
pair<T1, T2> make_pair(const T1& a, const T2& b) {
    return pair<T1, T2>(a, b);
}

}
