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
        vector<int> p0(n+1), p1(n+1);
        vector<int> d(n+1);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            p0[i+1] = p0[i];
            p1[i+1] = p1[i];
            d[i+1] = d[i];
            if(a[i] == 0)
                p0[i+1]++;
            else
                p1[i+1]++;
            if(i > 0 && a[i] == a[i-1]) {
                d[i+1]++;
            }
        }
        while(q-->0) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            int zeros = p0[r+1]-p0[l];
            int ones = p1[r+1]-p1[l];
            if(zeros%3!=0 || ones%3!=0) {
                cout << -1 << "\n";
                continue;
            }
            int ans = (zeros+ones)/3;
            if(d[r+1]-d[l+1] == 0)
                ans++;
            cout << ans << "\n";
        }
    }
}