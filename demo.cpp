#include <iostream>
#include "containers/vector.hpp"
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

    cout << endl;

    return 0;
}
