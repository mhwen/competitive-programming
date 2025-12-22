#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        string s;
        cin >> s;
        int ans = 0;
        auto go = [&](int start) {
            map<char, int> freq;
            freq[s[start-1]]++;
            int lastId = sz(s)-1;
            for(int i = 0; i+start < sz(s); i++) {
                if(i%2==0 && s[start+i] != 'I') {
                    lastId = start+i-1;
                    break;
                }
                if(i%2==1 && s[start+i] == 'I') {
                    lastId = start+i-1;
                    break;
                }
                freq[s[start+i]]++; 
            }
            ans += min(freq['M'], freq['T']/2);
            return lastId;
        };
        for(int i = 1; i < sz(s); i++) {
            if(s[i] == 'I') {
                i = go(i);
            }
        }
        cout << ans << "\n";
    }
}