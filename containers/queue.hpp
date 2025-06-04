#include <iostream>
using namespace std;

namespace mystl {

template <typename T>
class queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int _size;

public:
    queue() : head(nullptr), tail(nullptr), _size(0) {}

    ~queue() {
        clear();
    }

    void push(const T& element) {
        Node<T>* newNode = new Node<T>(element);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        _size++;
    }

    void pop() {
        if (empty()) {
            throw runtime_error("Queue Underflow");
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        _size--;
        if (!head) tail = nullptr;
    }

    T& front() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        return head->data;
    }

    T& back() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        return tail->data;
    }

    const T& front() const {
        if (empty()) {
            throw runtime_error("Queue is empty");
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
        tail = nullptr;
        _size = 0;
    }
};

}
