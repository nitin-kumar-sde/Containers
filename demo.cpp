#include <iostream>
#include "containers/vector.hpp"
#include "containers/unordered_map.hpp"
#include "containers/priority_queue.hpp"
#include "containers/stack.hpp"
#include "containers/queue.hpp"
#include "containers/deque.hpp"
#include "utilities/pair.hpp"
#include "utilities/tuple.hpp"


#include <algorithm>
#include <cmath>
#include <fstream>

#define ll long long
#define ld long double
#define endl '\n'
#define N 1000005
#define MOD 1000000007

using mystl::vector;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifndef ONLINE_JUDGE
        freopen("/Users/nitinkumar/Desktop/containers/input.txt", "r", stdin);
        freopen("/Users/nitinkumar/Desktop/containers/output.txt", "w", stdout);
    #endif

    mystl::vector<int> vct = {2,3,4}; 

    vct.push_back(4);
    vct.push_back(6);
    vct.push_back(8);

    for(int i=0;i<vct.size();i++) {
        cout << vct[i] << " ";
    }

    mystl::unordered_map<string, int> mp = {{"abc", 45}, {"def", 34}, {"ghi", 67}};
    mp.insert("abc", 123);
    cout << mp.getValue("abc") << endl;

    cout << mp["abc"] << endl;

    cout << endl;

    mystl::unordered_map<string, int>::iterator it = mp.begin();

    while(it != mp.end()) {
        cout << it->first << " " << it->second << endl;
        it++;
    }

    mystl::priority_queue<int, greater<int>> pq;
    pq.push(1);
    pq.push(4);
    pq.push(3);

    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    mystl::stack<int> s;
    s.push(3);
    s.push(5);
    s.push(7);

    cout << s.top();

    mystl::queue<int> q;
    q.push(3);
    q.push(5);
    q.push(7);

    cout << q.front();
    cout << q.back();

    mystl::deque<int> dq = {3, 5, 7};
    dq.push_back(9);
    dq.push_front(11);

    for(int i = 0;i<dq.size();i++) {
        cout << dq[i] << " ";
    }

    mystl::pair<int, string> p = {3, "nitin"};

    cout << p.first << " : " << p.second;

    mystl::tuple<int, string> p2 = {3, "nitin"};

    cout << get<1>(p2) << " : " << get<0>(p2);

    return 0;
}
