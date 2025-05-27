#include <vector>
#include <functional>
#include <stdexcept>

namespace mystl {

template <typename T, typename Comparator = std::less<T>>
class priority_queue {
private:
    std::vector<T> pq;
    Comparator comp;

    void heapifyUp(int index) {
        int child = index;
        int parent = (child - 1) / 2;
        while (child > 0 && comp(pq[parent], pq[child])) {
            std::swap(pq[parent], pq[child]);
            child = parent;
            parent = (child - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int parent = index;
        int size = static_cast<int>(pq.size());

        while (true) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int largest = parent;

            if (left < size && comp(pq[largest], pq[left]))
                largest = left;

            if (right < size && comp(pq[largest], pq[right]))
                largest = right;

            if (largest == parent)
                break;

            std::swap(pq[parent], pq[largest]);
            parent = largest;
        }
    }

public:
    priority_queue() = default;

    void push(const T& element) {
        pq.push_back(element);
        heapifyUp(static_cast<int>(pq.size()) - 1);
    }

    void push(T&& element) {
        pq.push_back(std::move(element));
        heapifyUp(static_cast<int>(pq.size()) - 1);
    }

    void pop() {
        if (pq.empty())
            throw std::out_of_range("priority_queue is empty");

        pq[0] = pq.back();
        pq.pop_back();

        if (!pq.empty())
            heapifyDown(0);
    }

    const T& top() const {
        if (pq.empty())
            throw std::out_of_range("priority_queue is empty");

        return pq[0];
    }

    bool empty() const {
        return pq.empty();
    }

    int size() const {
        return static_cast<int>(pq.size());
    }
};

}
