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
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        string r;
        cin >> r;
        vector<int> prev(26, n-1);
        vector<int> go(n);
        bool no = false;
        int time = 0;
        int mnSeen = n;
        for(int i = n-1; i >= 0; i--) {
            int id = r[i]-'a';
            mnSeen = min(mnSeen, i);
            while(prev[id] > mnSeen || (prev[id] >= 0 && s[prev[id]] != r[i]))
                prev[id]--;
            if(prev[id] < 0) {
                no = true;
                break;
            }
            time = max(time, i-prev[id]);
            mnSeen = prev[id];
            go[prev[id]] = max(go[prev[id]], i-prev[id]);
        }
        if(time > k)
            no = true;
            
        if(no) {
            cout << -1 << "\n";
            continue;
        }
        string og = s;
        cout << time << "\n";
        for(int T = 0; T < time; T++) {
            for(int i = 0; i < n; i++) {
                if(go[i] > T) {
                    s[i+T+1] = og[i];
                }
            }
            cout << s << "\n";
            if(T == time-1)
                assert(s == r);
        }
    }
}