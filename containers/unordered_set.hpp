#pragma once
#include <initializer_list>
#include <functional>
#include <stdexcept>

namespace mystl {

template <typename K>
class USetNode {
public:
    K key;
    USetNode* next;

    USetNode(K key) : key(key), next(nullptr) {}

    ~USetNode() {
        delete next;
    }
};

template <typename K, typename HashFunc = std::hash<K>>
class unordered_set {
    USetNode<K>** buckets;
    int count;
    int numBuckets;
    float maxLoadFactor;
    HashFunc hashFunc;

public:
    unordered_set() {
        count = 0;
        numBuckets = 5;
        maxLoadFactor = 0.7f;
        buckets = new USetNode<K>*[numBuckets];
        for (int i = 0; i < numBuckets; i++) {
            buckets[i] = nullptr;
        }
    }

    unordered_set(std::initializer_list<K> initList) : unordered_set() {
        for (const auto& key : initList) {
            insert(key);
        }
    }

    ~unordered_set() {
        for (int i = 0; i < numBuckets; i++) {
            delete buckets[i];
        }
        delete[] buckets;
    }

    int size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    class iterator {
        USetNode<K>* current;
        USetNode<K>** buckets;
        int index;
        int numBuckets;

        void advance() {
            while (!current && index < numBuckets) {
                current = buckets[index++];
            }
        }

    public:
        iterator(USetNode<K>** buckets, int numBuckets, int index = 0, USetNode<K>* current = nullptr)
            : buckets(buckets), numBuckets(numBuckets), index(index), current(current) {
            if (!current && index < numBuckets) {
                current = buckets[index++];
                advance();
            }
        }

        const K& operator*() const {
            return current->key;
        }

        iterator& operator++() {
            if (current) current = current->next;
            if (!current) advance();
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        friend class unordered_set;
    };

    iterator begin() {
        return iterator(buckets, numBuckets, 0);
    }

    iterator end() {
        return iterator(buckets, numBuckets, numBuckets, nullptr);
    }

    iterator find(const K& key) {
        int index = getBucketIndex(key);
        USetNode<K>* head = buckets[index];
        while (head) {
            if (head->key == key)
                return iterator(buckets, numBuckets, index, head);
            head = head->next;
        }
        return end();
    }

    void insert(const K& key) {
        if (find(key) != end()) return;

        int index = getBucketIndex(key);
        USetNode<K>* node = new USetNode<K>(key);
        node->next = buckets[index];
        buckets[index] = node;
        count++;

        if (getLoadFactor() > maxLoadFactor) {
            rehash();
        }
    }

    void erase(const K& key) {
        int index = getBucketIndex(key);
        USetNode<K>* head = buckets[index];
        USetNode<K>* prev = nullptr;

        while (head) {
            if (head->key == key) {
                if (prev) prev->next = head->next;
                else buckets[index] = head->next;
                head->next = nullptr;
                delete head;
                count--;
                return;
            }
            prev = head;
            head = head->next;
        }
    }

    void clear() {
        for (int i = 0; i < numBuckets; i++) {
            delete buckets[i];
            buckets[i] = nullptr;
        }
        count = 0;
    }

private:
    int getBucketIndex(const K& key) const {
        return static_cast<int>(hashFunc(key) % numBuckets);
    }

    float getLoadFactor() const {
        return static_cast<float>(count) / numBuckets;
    }

    void rehash() {
        int oldNumBuckets = numBuckets;
        numBuckets *= 2;
        USetNode<K>** oldBuckets = buckets;

        buckets = new USetNode<K>*[numBuckets];
        for (int i = 0; i < numBuckets; i++) {
            buckets[i] = nullptr;
        }

        count = 0;

        for (int i = 0; i < oldNumBuckets; i++) {
            USetNode<K>* head = oldBuckets[i];
            while (head) {
                insert(head->key);
                USetNode<K>* temp = head;
                head = head->next;
                temp->next = nullptr;
                delete temp;
            }
        }

        delete[] oldBuckets;
    }
};

}