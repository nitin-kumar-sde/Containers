#include <initializer_list> 
namespace mystl {

template <typename T>
class DNode {
public:
    T data;
    DNode* prev;
    DNode* next;

    DNode(T val) : data(val), prev(nullptr), next(nullptr) {}
};
    
template <typename T>
class deque {
private:
    DNode<T>* head;
    DNode<T>* tail;
    int _size;
    
    public:
    deque() : head(nullptr), tail(nullptr), _size(0) {}


    deque(std::initializer_list<T> initList) : head(nullptr), tail(nullptr), _size(0) {
        for (const T& val : initList) {
            push_back(val);
        }
    }
    
    ~deque() {
        clear();
    }
    
    bool empty() const {
        return _size == 0;
    }
    
    int size() const {
        return _size;
    }
    
    void push_front(const T& val) {
        DNode<T>* newNode = new DNode<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        _size++;
    }
    
    void push_back(const T& val) {
        DNode<T>* newNode = new DNode<T>(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        _size++;
    }
    
    void pop_front() {
        if (empty()) throw std::runtime_error("Deque Underflow");
        DNode<T>* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        _size--;
    }
    
    void pop_back() {
        if (empty()) throw std::runtime_error("Deque Underflow");
        DNode<T>* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        _size--;
    }
    
    T& front() {
        if (empty()) throw std::runtime_error("Deque is empty");
        return head->data;
    }
    
    T& back() {
        if (empty()) throw std::runtime_error("Deque is empty");
        return tail->data;
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index out of bounds");
        }
    
        DNode<T>* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
    
        return temp->data;
    }    
    
    void clear() {
        while (head) {
            DNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        _size = 0;
    }
};
    
} 
    