#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>
using namespace std;

#define ll long long
#define ld long double
#define endl '\n'
#define N 1000005
#define MOD 1000000007

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifndef ONLINE_JUDGE
        freopen("/Users/nitinkumar/Desktop/containers/input.txt", "r", stdin);
        freopen("/Users/nitinkumar/Desktop/containers/output.txt", "w", stdout);
    #endif

    vector<int> v1 = {2, 4, 7, 8};

    vector<int> v2(4, 2);

    v1.push_back(2);
    v1.pop_back();

    v1.insert(v1.begin() + 1, 2);

    v1.erase(v1.begin() + 2);
    v1.clear();
    
    int lastElement = v1.back();

    // common utlities 
    // sorts the vector
    sort(v1.begin(), v1.end());

    // reverses the vector
    reverse(v1.begin(), v1.end());
    
    // removes consecutive duplicates
    unique(v1.begin(), v1.end());

    // sum of elements
    ll sum = accumulate(v1.begin(), v1.end(), (ll)0);

    // count the frequency of a number
    int freq = count(v1.begin(), v1.end(), 2);

    // max element 
    int maxElement = *max_element(v1.begin(), v1.end());
    // min element
    int minElement = *min_element(v1.begin(), v1.end());

    return 0;
}