#include <iostream>
using namespace std;

namespace mystl {

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class stack {
private:
    Node<T>* head;
    int _size;

public:
    stack() : head(nullptr), _size(0) {}

    ~stack() {
        clear();
    }

    void push(const T& element) {
        Node<T>* newNode = new Node<T>(element);
        newNode->next = head;
        head = newNode;
        _size++;
    }

    void pop() {
        if (empty()) {
            throw runtime_error("Stack Underflow");
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        _size--;
    }

    T& top() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return head->data;
    }

    const T& top() const {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return head->data;
    }

    bool empty() const {
        return _size == 0;
    }

    int size() const {
        return _size;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        _size = 0;
    }
};

}
