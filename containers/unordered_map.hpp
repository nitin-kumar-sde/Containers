#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <memory>

using namespace std;

namespace mystl {

template <typename K, typename V, typename HashFunc = std::hash<K>>
class MapNode {
public:
    K key;
    V value;
    MapNode* next;

    MapNode(K key, V value) {
        this->key = key;
        this->value = value;
        next = nullptr;
    }

    ~MapNode() {
        delete next;
    }
};

template <typename K, typename V, typename HashFunc = std::hash<K>>
class unordered_map {
    MapNode<K, V>** buckets;
    int count;
    int numBuckets;
    float maxLoadFactor;
    HashFunc hashFunc;

public:
    unordered_map() {
        count = 0;
        numBuckets = 5;
        maxLoadFactor = 0.7f;
        buckets = new MapNode<K, V>*[numBuckets];
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
        MapNode<K, V>* current;
        MapNode<K, V>** buckets;
        int index;
        int numBuckets;
        mutable std::unique_ptr<std::pair<const K, V>> currentPairPtr;

        void advanceToNextValid() {
            while (!current && index < numBuckets) {
                current = buckets[index++];
            }
        }

    public:
        iterator(MapNode<K, V>** buckets, int numBuckets, int startIndex = 0)
            : buckets(buckets), numBuckets(numBuckets), index(startIndex), current(nullptr) {
            if (index < numBuckets) {
                current = buckets[index++];
                advanceToNextValid();
            }
        }

        std::pair<const K, V>& operator*() const {
            return *reinterpret_cast<std::pair<const K, V>*>(&current->key);
        }

        MapNode<K, V>* operator->() const {
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
        MapNode<K, V>* head = buckets[bucketIndex];

        while (head != nullptr) {
            if (head->key == key) {
                head->value = value;
                return;
            }
            head = head->next;
        }

        head = buckets[bucketIndex];
        MapNode<K, V>* node = new MapNode<K, V>(key, value);
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
        MapNode<K, V>* head = buckets[bucketIndex];
        MapNode<K, V>* prev = nullptr;

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
        MapNode<K, V>* head = buckets[bucketIndex];
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
        MapNode<K, V>* head = buckets[bucketIndex];
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
        MapNode<K, V>** oldBuckets = buckets;

        buckets = new MapNode<K, V>*[numBuckets];
        for (int i = 0; i < numBuckets; i++) {
            buckets[i] = nullptr;
        }

        count = 0;

        for (int i = 0; i < oldNumBuckets; i++) {
            MapNode<K, V>* head = oldBuckets[i];
            while (head != nullptr) {
                insert(head->key, head->value);
                MapNode<K, V>* temp = head;
                head = head->next;
                temp->next = nullptr;
                delete temp;
            }
        }
        delete[] oldBuckets;
    }
};

}
