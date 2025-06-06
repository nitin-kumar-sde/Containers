// map.hpp
#pragma once

#include <iostream>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <stack>

namespace mystl {

    template <typename K, typename V>
    class MapNode {
    public:
        K key;
        V value;
        MapNode* left;
        MapNode* right;
        int height;

        MapNode(K k, V v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}

        ~MapNode() {
            delete left;
            delete right;
        }
    };

    template <typename K, typename V, typename Comp = std::less<K>>
    class map {
    private:
        MapNode<K, V>* root = nullptr;
        Comp comp;

        int height(MapNode<K, V>* node) {
            return node ? node->height : 0;
        }

        int getBalance(MapNode<K, V>* node) {
            return node ? height(node->left) - height(node->right) : 0;
        }

        MapNode<K, V>* rightRotate(MapNode<K, V>* y) {
            MapNode<K, V>* x = y->left;
            MapNode<K, V>* T2 = x->right;
            x->right = y;
            y->left = T2;
            y->height = 1 + std::max(height(y->left), height(y->right));
            x->height = 1 + std::max(height(x->left), height(x->right));
            return x;
        }

        MapNode<K, V>* leftRotate(MapNode<K, V>* x) {
            MapNode<K, V>* y = x->right;
            MapNode<K, V>* T2 = y->left;
            y->left = x;
            x->right = T2;
            x->height = 1 + std::max(height(x->left), height(x->right));
            y->height = 1 + std::max(height(y->left), height(y->right));
            return y;
        }

        MapNode<K, V>* insert(MapNode<K, V>* node, K key, V value) {
            if (!node) return new MapNode<K, V>(key, value);

            if (comp(key, node->key))
                node->left = insert(node->left, key, value);
            else if (comp(node->key, key))
                node->right = insert(node->right, key, value);
            else {
                node->value = value;
                return node;
            }

            node->height = 1 + std::max(height(node->left), height(node->right));
            int balance = getBalance(node);

            if (balance > 1 && comp(key, node->left->key))
                return rightRotate(node);
            if (balance < -1 && comp(node->right->key, key))
                return leftRotate(node);
            if (balance > 1 && comp(node->left->key, key)) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (balance < -1 && comp(key, node->right->key)) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        MapNode<K, V>* minValueNode(MapNode<K, V>* node) {
            MapNode<K, V>* current = node;
            while (current && current->left)
                current = current->left;
            return current;
        }

        MapNode<K, V>* erase(MapNode<K, V>* root, K key) {
            if (!root) return root;

            if (comp(key, root->key))
                root->left = erase(root->left, key);
            else if (comp(root->key, key))
                root->right = erase(root->right, key);
            else {
                if (!root->left || !root->right) {
                    MapNode<K, V>* temp = root->left ? root->left : root->right;
                    if (!temp) {
                        temp = root;
                        root = nullptr;
                    } else {
                        *root = *temp;
                    }
                    temp->left = temp->right = nullptr;
                    delete temp;
                } else {
                    MapNode<K, V>* temp = minValueNode(root->right);
                    root->key = temp->key;
                    root->value = temp->value;
                    root->right = erase(root->right, temp->key);
                }
            }

            if (!root) return root;

            root->height = 1 + std::max(height(root->left), height(root->right));
            int balance = getBalance(root);

            if (balance > 1 && getBalance(root->left) >= 0)
                return rightRotate(root);
            if (balance > 1 && getBalance(root->left) < 0) {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
            if (balance < -1 && getBalance(root->right) <= 0)
                return leftRotate(root);
            if (balance < -1 && getBalance(root->right) > 0) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;
        }

        MapNode<K, V>* find(MapNode<K, V>* node, const K& key) const {
            if (!node) return nullptr;
            if (comp(key, node->key)) return find(node->left, key);
            if (comp(node->key, key)) return find(node->right, key);
            return node;
        }

    public:
        class iterator {
        public:
            using value_type = std::pair<const K, V>;

        private:
            std::stack<MapNode<K, V>*> stk;
            std::pair<K, V> current;

            void pushLeft(MapNode<K, V>* node) {
                while (node) {
                    stk.push(node);
                    node = node->left;
                }
            }

        public:
            iterator(MapNode<K, V>* root) { pushLeft(root); }
            iterator() = default;

            bool operator!=(const iterator& other) const {
                return stk != other.stk;
            }

            value_type operator*() const {
                auto* node = stk.top();
                return { node->key, node->value };
            }

            value_type* operator->() {
                auto* node = stk.top();
                current = { node->key, node->value };
                return reinterpret_cast<value_type*>(&current);
            }

            iterator& operator++() {
                auto* node = stk.top();
                stk.pop();
                if (node->right) pushLeft(node->right);
                return *this;
            }

            iterator operator++(int) {
                iterator temp = *this;
                ++(*this);
                return temp;
            }
        };

        map() = default;

        map(std::initializer_list<std::pair<K, V>> initList) {
            for (const auto& item : initList) {
                insert(item.first, item.second);
            }
        }

        void insert(K key, V value) {
            root = insert(root, key, value);
        }

        void erase(K key) {
            root = erase(root, key);
        }

        V& operator[](const K& key) {
            MapNode<K, V>* node = find(root, key);
            if (node) return node->value;
            root = insert(root, key, V());
            return find(root, key)->value;
        }

        iterator begin() const { return iterator(root); }
        iterator end() const { return iterator(); }

        void print() const {
            for (auto [k, v] : *this) {
                std::cout << k << " : " << v << std::endl;
            }
        }

        ~map() {
            delete root;
        }
    };

}
