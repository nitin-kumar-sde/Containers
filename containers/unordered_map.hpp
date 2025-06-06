#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <memory>

using namespace std;

namespace mystl {

template <typename K, typename V, typename HashFunc = std::hash<K>>
class UMapNode {
public:
    K key;
    V value;
    UMapNode* next;

    UMapNode(K key, V value) {
        this->key = key;
        this->value = value;
        next = nullptr;
    }

    ~UMapNode() {
        delete next;
    }
};

template <typename K, typename V, typename HashFunc = std::hash<K>>
class unordered_map {
    UMapNode<K, V>** buckets;
    int count;
    int numBuckets;
    float maxLoadFactor;
    HashFunc hashFunc;

public:
    unordered_map() {
        count = 0;
        numBuckets = 5;
        maxLoadFactor = 0.7f;
        buckets = new UMapNode<K, V>*[numBuckets];
        for (int i = 0; i < numBuckets; i++) {
            buckets[i] = nullptr;
        }
    }

    unordered_map(std::initializer_list<std::pair<K, V>> initList) : unordered_map() {
        for (const auto& kv : initList) {
            insert(kv.first, kv.second);
        }
    }

    ~unordered_map() {
        for (int i = 0; i < numBuckets; i++) {
            delete buckets[i];
        }
        delete[] buckets;
    }

    class iterator {
        UMapNode<K, V>* current;
        UMapNode<K, V>** buckets;
        int index;
        int numBuckets;
        mutable std::unique_ptr<std::pair<const K, V>> currentPairPtr;

        void advanceToNextValid() {
            while (!current && index < numBuckets) {
                current = buckets[index++];
            }
        }

    public:
        iterator(UMapNode<K, V>** buckets, int numBuckets, int startIndex = 0)
            : buckets(buckets), numBuckets(numBuckets), index(startIndex), current(nullptr) {
            if (index < numBuckets) {
                current = buckets[index++];
                advanceToNextValid();
            }
        }

        std::pair<const K, V>& operator*() const {
            return *reinterpret_cast<std::pair<const K, V>*>(&current->key);
        }

        UMapNode<K, V>* operator->() const {
            return current;
        }

        iterator& operator++() {
            if (current) current = current->next;
            if (!current) advanceToNextValid();
            return *this;
        }

        iterator operator++(int) {
            iterator temp(buckets, numBuckets, index - 1); \
            temp.current = current;
            ++(*this);
            return temp;
        }
        
        
        std::pair<const K, V>* operator->() {
            if (!current) {
                throw std::runtime_error("Invalid iterator access");
            }
            currentPairPtr = std::make_unique<std::pair<const K, V>>(current->key, current->value);
            return currentPairPtr.get();
        }
        

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    int size() {
        return count;
    }

    iterator begin() {
        return iterator(buckets, numBuckets, 0);
    }

    iterator end() {
        return iterator(buckets, numBuckets, numBuckets);
    }

    void insert(K key, V value) {
        int bucketIndex = getBucketIndex(key);
        UMapNode<K, V>* head = buckets[bucketIndex];

        while (head != nullptr) {
            if (head->key == key) {
                head->value = value;
                return;
            }
            head = head->next;
        }

        head = buckets[bucketIndex];
        UMapNode<K, V>* node = new UMapNode<K, V>(key, value);
        node->next = head;
        buckets[bucketIndex] = node;
        count++;

        // ⬇️ Load factor check and rehash
        if (getLoadFactor() > maxLoadFactor) {
            rehash();
        }
    }

    V remove(K key) {
        int bucketIndex = getBucketIndex(key);
        UMapNode<K, V>* head = buckets[bucketIndex];
        UMapNode<K, V>* prev = nullptr;

        while (head != nullptr) {
            if (head->key == key) {
                if (prev == nullptr) {
                    buckets[bucketIndex] = head->next;
                } else {
                    prev->next = head->next;
                }
                V value = head->value;
                head->next = nullptr;
                delete head;
                count--;
                return value;
            }
            prev = head;
            head = head->next;
        }
        return V();
    }

    V getValue(K key) {
        int bucketIndex = getBucketIndex(key);
        UMapNode<K, V>* head = buckets[bucketIndex];
        while (head != nullptr) {
            if (head->key == key) {
                return head->value;
            }
            head = head->next;
        }
        return V();
    }

    V& operator[](const K& key) {
        int bucketIndex = getBucketIndex(key);
        UMapNode<K, V>* head = buckets[bucketIndex];
        while (head != nullptr) {
            if (head->key == key) {
                return head->value;
            }
            head = head->next;
        }
        throw std::runtime_error("key does not exist");
    }

private:
    int getBucketIndex(K key) {
        size_t hashCode = hashFunc(key);
        return static_cast<int>(hashCode % numBuckets);
    }

    float getLoadFactor() const {
        return (1.0f * count) / numBuckets;
    }

    void rehash() {
        int oldNumBuckets = numBuckets;
        numBuckets *= 2;
        UMapNode<K, V>** oldBuckets = buckets;

        buckets = new UMapNode<K, V>*[numBuckets];
        for (int i = 0; i < numBuckets; i++) {
            buckets[i] = nullptr;
        }

        count = 0;

        for (int i = 0; i < oldNumBuckets; i++) {
            UMapNode<K, V>* head = oldBuckets[i];
            while (head != nullptr) {
                insert(head->key, head->value);
                UMapNode<K, V>* temp = head;
                head = head->next;
                temp->next = nullptr;
                delete temp;
            }
        }
        delete[] oldBuckets;
    }
};

}
