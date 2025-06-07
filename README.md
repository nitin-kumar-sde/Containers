# 🪣 Containers - Custom implementation of STL containers

A lightweight and elegant C++ container library, mirroring the functionality of the Standard Template Library (STL).


## 🪂 Usage

Clone the project 

```
git clone https://github.com/nitin-kumar-sde/containers.git
cd containers
```

---

## 📚 Table of Contents
- [👩‍❤️‍👨 Pair](#-pair)
- [🌙🌗🪐 Tuple](#-tuple)
- [📦 Vector](#-vector)
- [📚 Stack](#-stack)
- [⌛ Queue](#-queue)
- [🧺 Deque](#-deque)
- [♟️ Priority Queue](#-priority-queue)
- [🌍 Map](#-map)
- [🔮 Unordered Map](#-unordered-map)
- [🗽 Set](#-set)
- [🗼 Unordered Set](#-unordered-set)
- [ 🌿 String](#-string)


---

## 👫 Pair 
A generic, efficient pair similar to STL in mystl namespace:

```
#include <iostream>
#include "utilities/pair.hpp"

int main() {

    mystl::pair<int, string> p = {3, "nitin"};

    cout << p.first << " : " << p.second;

    return 0;
}
```

---

## 🌙🌗🪐 Tuple
A generic, efficient tuple similar to STL in mystl namespace:

```
#include <iostream>
#include "utilities/tuple.hpp"

int main() {

    mystl::tuple<int, string> p2 = {3, "nitin"};

    cout << get<1>(p2) << " : " << get<0>(p2);

    return 0;
}

```

---

## 📦 Vector

A dynamic array implementation with:
- Automatic resizing  
- Element access via `operator[]`  
- Support for `push_back()`, `pop_back()`, `size()`, and `capacity()`  
- Iterator support for range-based loops  

**Example:**

```
#include "containers/vector.hpp"
#include <iostream>

int main() {
    mystl::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    for (auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
---

## 📚 Stack 
A generic, efficient stack supporting:

- Any data type (templated)
- Namespace mystl to avoid STL conflicts
- Optimized push/pop using linked list O(1)

**Example:**

```
#include <iostream>
#include "containers/stack.hpp"
int main() {

 mystl::stack<int> s;
    s.push(3);
    s.push(5);
    s.push(7);

    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    return 0;
}
```

## ⌛ Queue
A generic, efficient queue supporting:

- Any data type (templated)
- Namespace mystl to avoid STL conflicts
- Optimized push/pop using linked list O(1)

**Example:**

```
#include <iostream>
#include "containers/queue.hpp"
int main() {

 mystl::queue<int> q;
    q.push(3);
    q.push(5);
    q.push(7);

    cout << q.front() << endl;
    q.pop();
    cout << q.back() << endl;
    return 0;
}
```

## 🧺 Deque

A generic, efficient deque supporting:

- Any data type (templated)
- Namespace mystl to avoid STL conflicts
- Optimized push/pop at front and back using linked list O(1)
- Initialisation list at creation time
- Index access

**Example:**

```
#include <iostream>
#include "containers/deque.hpp"
int main() {

 mystl::deque<int> dq;
    dq.push_back(3);
    dq.push_front(5);
    dq.push_back(7);

    cout << dq.front() << endl;
    dq.pop_front();
    cout << dq.back() << endl;
    dq.pop_back();
    cout << dq.back() << endl;
    return 0;
}
```
---

## 👑 Priority Queue
A generic, efficient heap-based priority_queue supporting:

- Any data type (templated)
- Min-heap or Max-heap via custom comparator (➤ Max-Heap (Default))
- Namespace mystl to avoid STL conflicts
- Optimized push/pop using heapify logic

**Example:**

```
#include <iostream>
#include "containers/priority_queue.hpp"
int main() {

    mystl::priority_queue<int, greater<int>> pq;
    pq.push(1);
    pq.push(4);
    pq.push(3);

    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    return 0;
}
```

---

## 🌍 Map

A map container based on AVL trees

- Efficient insert, delete and find in O(logn)  
- Iterators for traversal using range-based loops  
- Custom comparator for ordering  

**Example:**

```cpp
#include "containers/map.hpp"
#include <iostream>
#include <string>

int main() {
    mystl::map<std::string, int> map;
    map.insert("apple", 3);
    map.insert("banana", 5);
    map.insert("orange", 2);

    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << "Value for key 'banana': " << map.getValue("banana") << std::endl;

    return 0;
}

```
---

## 🔮 Unordered Map

A hash table based key-value store with:

- Separate chaining collision resolution  
- Support for `insert()`, `remove()`, and `getValue()`  
- Iterators for traversal using range-based loops  
- Customizable hash function support  

**Example:**

```cpp
#include "containers/unordered_map.hpp"
#include <iostream>
#include <string>

int main() {
    mystl::unordered_map<std::string, int> map;
    map.insert("apple", 3);
    map.insert("banana", 5);
    map.insert("orange", 2);

    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << "Value for key 'banana': " << map.getValue("banana") << std::endl;

    return 0;
}

```

## 🗽 Set 
A set container based on AVL trees

- Efficient insert, delete and find in O(logn)  
- Iterators for traversal using range-based loops  
- Custom comparator for ordering

```
#include <iostream>
#include "containers/set.hpp"


#include <algorithm>
#include <cmath>
#include <fstream>

#define ll long long
#define ld long double
#define endl '\n'
#define N 1000005
#define MOD 1000000007

int main() {
    mystl::set<int> st;
    st.insert(10);
    st.insert(5);
    st.insert(20);
    st.insert(10);

    for (auto it = st.begin(); it != st.end(); ++it) {
        cout << *it << " ";
    }

    st.erase(10);

    for (auto x : st) cout << x << " ";

    auto uf = st.find(5);

    if (uf != st.end())
        cout << "5 is found" << endl;
    else
        cout << "5 not found" << endl;
    return 0;
}

```

---

## 🗼 Unordered Set 
A set container based on hash tables

- Efficient insert, delete and find in O(1)  
- Iterators for traversal using range-based loops  
- Custom hash function support

```
#include <iostream>
#include "containers/unordered_set.hpp"


#include <algorithm>
#include <cmath>
#include <fstream>

#define ll long long
#define ld long double
#define endl '\n'
#define N 1000005
#define MOD 1000000007

int main() {
    mystl::unordered_set<int> ust;
    ust.insert(10);
    ust.insert(5);
    ust.insert(20);
    ust.insert(10);

    for (auto it = ust.begin(); it != ust.end(); ++it) {
        cout << *it << " ";
    }

    ust.erase(10);

    for (auto x : ust) cout << x << " ";

    auto uf = ust.find(5);

    if (uf != ust.end())
        cout << "5 is found" << endl;
    else
        cout << "5 not found" << endl;
    return 0;
}

```

---

## 🌿 String 

```
#include <iostream>
#include "containers/string.hpp"

int main() {
    mystl::string str = "nitin";
    str+="kumar";
    cout << str << endl;
}

```
