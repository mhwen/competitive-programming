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

constexpr int B = 330;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, q;
        cin >> n >> q;
        vector<int> r(n), s(n);
        for(int i = 0; i < n; i++) {
            cin >> r[i];
            r[i]--;
        }
        for(int i = 0; i < n; i++) {
            cin >> s[i];
            s[i]--;
        }
        vector<int> p(n), revP(n);
        for(int i = 0; i < n; i++)
            p[r[i]] = s[i];
        for(int i = 0; i < n; i++)
            revP[p[i]] = i;
            
        int blocks = (n+B-1)/B;
        vector<int> maxes(blocks);
        vector<int> lastChange(blocks);
        vector<int> change(n);
        vector<ll> gain(n);
        
        auto print = [&]() {
            return;
            for(auto A : p)
                cout << A+1 << " ";
            cout << endl;
            for(auto A : maxes)
                cout << A+1 << " ";
            cout << endl;
            for(auto A : lastChange)
                cout << A+1 << " ";
            cout << endl;
            for(auto A : change)
                cout << A+1 << " ";
            cout << endl;
            for(auto A : gain)
                cout << A << " ";
            cout << endl;
        };
        
        auto query = [&](int block, int prevMax, int prevChange) {
            // cout << "query " << block+1 << " " << prevMax+1 << " " << prevChange+1 << endl;
            int start = block*B;
            prevMax = max(start, prevMax);
            if(prevMax > lastChange[block])
                return pair{0LL, -1};
            return pair{gain[prevMax] - (ll)(prevChange+1)*(change[prevMax]+1), lastChange[block]};
        };
        
        auto update = [&](int block, int prevMax, int prevChange) {
            int start = block*B;
            int end = min(n, (block+1)*B)-1;
            int currMax = -1;
            lastChange[block] = -1;
            for(int i = start; i <= end; i++) {
                currMax = max(currMax, p[i]);
                gain[i] = 0;
                change[i] = -1;
                if(currMax <= i) {
                    lastChange[block] = i;
                    change[i] = i;
                    gain[i] += (ll)(i+1)*(i+1);
                }
            }
            for(int i = end-1; i >= start; i--) {
                gain[i] += gain[i+1];
                if(change[i] != -1)
                    gain[i] -= (ll)(change[i+1]+1)*(i+1);
                else
                    change[i] = change[i+1];
            }
            maxes[block] = currMax;
        };
        
        int prevMax = -1, prevChange = -1;
        for(int i = 0; i < blocks; i++) {
            update(i, prevMax, prevChange);
            auto [amt, lChange] = query(i, prevMax, prevChange);
            prevMax = max(prevMax, maxes[i]);
            prevChange = max(prevChange, lChange);
        }
        while(q-->0) {
            int type, a, b;
            cin >> type >> a >> b;
            a--; b--;
            if(type == 1) {
                swap(r[a], r[b]);
                a = r[a];
                b = r[b];
            }
            else {
                swap(s[a], s[b]);
                a = revP[s[a]];
                b = revP[s[b]];
            }
            swap(revP[p[a]], revP[p[b]]);
            swap(p[a], p[b]);
            assert(revP[p[a]] == a && revP[p[b]] == b);
            ll res = 0;
            prevMax = -1;
            prevChange = -1;
            for(int i = 0; i < blocks; i++) {
                if(i == a/B || i == b/B)
                    update(i, prevMax, prevChange);
                auto [amt, lChange] = query(i, prevMax, prevChange);
                res += amt;
                prevMax = max(maxes[i], prevMax);
                prevChange = max(prevChange, lChange);
            }
            cout << res << "\n";
            print();
        }
    }
    
}