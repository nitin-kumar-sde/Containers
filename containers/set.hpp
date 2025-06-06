#pragma once

#include <iostream>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <stack>

namespace mystl {

    template <typename T>
    class SetNode {
    public:
        T value;
        SetNode* left;
        SetNode* right;
        int height;

        SetNode(T v) : value(v), left(nullptr), right(nullptr), height(1) {}

        ~SetNode() {
            delete left;
            delete right;
        }
    };

    template <typename T, typename Comp = std::less<T>>
    class set {
    private:
        SetNode<T>* root = nullptr;
        Comp comp;

        int height(SetNode<T>* node) {
            return node ? node->height : 0;
        }

        int getBalance(SetNode<T>* node) {
            return node ? height(node->left) - height(node->right) : 0;
        }

        SetNode<T>* rightRotate(SetNode<T>* y) {
            SetNode<T>* x = y->left;
            SetNode<T>* T2 = x->right;
            x->right = y;
            y->left = T2;
            y->height = 1 + std::max(height(y->left), height(y->right));
            x->height = 1 + std::max(height(x->left), height(x->right));
            return x;
        }

        SetNode<T>* leftRotate(SetNode<T>* x) {
            SetNode<T>* y = x->right;
            SetNode<T>* T2 = y->left;
            y->left = x;
            x->right = T2;
            x->height = 1 + std::max(height(x->left), height(x->right));
            y->height = 1 + std::max(height(y->left), height(y->right));
            return y;
        }

        SetNode<T>* insert(SetNode<T>* node, const T& value) {
            if (!node) return new SetNode<T>(value);

            if (comp(value, node->value))
                node->left = insert(node->left, value);
            else if (comp(node->value, value))
                node->right = insert(node->right, value);
            else
                return node;

            node->height = 1 + std::max(height(node->left), height(node->right));
            int balance = getBalance(node);

            if (balance > 1 && comp(value, node->left->value))
                return rightRotate(node);
            if (balance < -1 && comp(node->right->value, value))
                return leftRotate(node);
            if (balance > 1 && comp(node->left->value, value)) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (balance < -1 && comp(value, node->right->value)) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        SetNode<T>* minValueNode(SetNode<T>* node) {
            SetNode<T>* current = node;
            while (current && current->left)
                current = current->left;
            return current;
        }

        SetNode<T>* erase(SetNode<T>* root, const T& value) {
            if (!root) return root;

            if (comp(value, root->value))
                root->left = erase(root->left, value);
            else if (comp(root->value, value))
                root->right = erase(root->right, value);
            else {
                if (!root->left || !root->right) {
                    SetNode<T>* temp = root->left ? root->left : root->right;
                    if (!temp) {
                        temp = root;
                        root = nullptr;
                    } else {
                        *root = *temp;
                    }
                    temp->left = temp->right = nullptr;
                    delete temp;
                } else {
                    SetNode<T>* temp = minValueNode(root->right);
                    root->value = temp->value;
                    root->right = erase(root->right, temp->value);
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

    public:
        class iterator {
        public:
            std::stack<SetNode<T>*> stk;
        private:
            T* current = nullptr;

            void pushLeft(SetNode<T>* node) {
                while (node) {
                    stk.push(node);
                    node = node->left;
                }
            }

        public:
            iterator(SetNode<T>* root) { pushLeft(root); }
            iterator() = default;

            bool operator!=(const iterator& other) const { return stk != other.stk; }

            const T& operator*() const {
                return stk.top()->value;
            }

            const T* operator->() const {
                current = &stk.top()->value;
                return current;
            }

            iterator& operator++() {
                SetNode<T>* node = stk.top();
                stk.pop();
                if (node->right) pushLeft(node->right);
                return *this;
            }
        };

        set() = default;

        set(std::initializer_list<T> initList) {
            for (const auto& val : initList)
                insert(val);
        }

        ~set() {
            delete root;
        }

        iterator begin() const { return iterator(root); }
        iterator end() const { return iterator(); }

        void insert(const T& value) {
            root = insert(root, value);
        }

        void erase(const T& value) {
            root = erase(root, value);
        }

        iterator find(const T& value) const {
            std::stack<SetNode<T>*> path;
            SetNode<T>* current = root;

            while (current) {
                if (comp(value, current->value)) {
                    path.push(current);
                    current = current->left;
                } else if (comp(current->value, value)) {
                    path.push(current);
                    current = current->right;
                } else {
                    path.push(current);
                    break;
                }
            }

            if (path.empty() || path.top()->value != value)
                return end();

            iterator it;
            it.stk = path;
            return it;
        }
    };

}
