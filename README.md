# 🪣 Containers - Custom implementation of STL containers

A lightweight and elegant C++ container library, mirroring the functionality of the Standard Template Library (STL).


## 🪂 Usage

Clone the project 

```
git clone https://github.com/nitin-kumar-sde/containers.git
cd containers
```

### 📦 Vector

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

### 🌍 unordered_map

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

### ♟️ Priority Queue
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
