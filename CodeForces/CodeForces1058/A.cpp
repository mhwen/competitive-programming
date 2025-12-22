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

int query(vector<int>& v) {
    cout << "? " << sz(v);
    for(int a : v)
        cout << " " << a;
    cout << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<int> q;
        vector<int> unknown, known;
        vector<int> ans(2*n+1);
        for(int i = 1; i <= 2*n; i++) {
            q.pb(i);
            int res = query(q);
            if(res == 0)
                unknown.pb(i);
            else {
                ans[i] = res;
                known.pb(i);
                q.pop_back();
            }
        }
        for(int i : unknown) {
            known.pb(i);
            ans[i] = query(known);
            known.pop_back();
        }
        cout << "! ";
        for(int i = 1; i <= 2*n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
}