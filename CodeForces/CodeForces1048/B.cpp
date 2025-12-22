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
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        vector<int> left(n, -1), right(n, -1);
        stack<pair<int, int>> s;
        for(int i = 0; i < n; i++) {
            while(!s.empty() && s.top().first < a[i])
                s.pop();
            if(!s.empty())
                left[i] = s.top().second;
            s.push({a[i], i});
        }
        while(!s.empty())
            s.pop();
        for(int i = n-1; i >= 0; i--) {
            while(!s.empty() && s.top().first > a[i])
                s.pop();
            if(!s.empty())
                right[i] = s.top().second;
            s.push({a[i], i});
        }
        vector<int> cap(n, n);
        for(int i = 0; i < n; i++) {
            if(left[i] != -1 && right[i] != -1) {
                cap[left[i]] = min(cap[left[i]], right[i]);
            }
        }
        for(int i = n-2; i >= 0; i--)
            cap[i] = min(cap[i], cap[i+1]);
        vector<bool> ans(q);
        for(int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            if(cap[l] <= r)
                cout << "NO\n";
            else
                cout << "YES\n";
        }
    }
}