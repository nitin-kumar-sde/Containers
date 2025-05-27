#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <fstream>
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

    unordered_map<int, string> mp = {{1, "abc"}, {2, "def"}};

    // will insert if key doesn't exist else ignore
    mp.insert({1, "xyz"});
    mp[3] = "tuv";
    unordered_map<int, string>::iterator it = mp.begin();

    mp.erase(2);
    
    while(it != mp.end()) {
        cout << it->first << " " << it->second << endl;
        it++;
    }
    it = mp.find(2);

    if(it == mp.end()) {
        cout << "key does npt exist";
    }
    else 
    cout << it->first << " " << it->second;

    cout << mp.at(1) << endl;




    return 0;
}