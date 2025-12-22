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
        int n, k, q;
        cin >> n >> k >> q;
        vector<int> mex(n), mn(n);
        while(q-->0) {
            int c, l, r;
            cin >> c >> l >> r;
            l--; r--;
            if(c == 2) {
                for(int i = l; i <= r; i++)
                    mex[i]++;
            }
            else {
                for(int i = l; i <= r; i++)
                    mn[i]++;
            }
        }
        for(int i = 0; i < n; i++) {
            if(mex[i] == 0)
                cout << k << " ";
            else if(mn[i] > 0)
                cout << k+5 << " ";
            else
                cout << i%k << " ";
        }
        cout << "\n";
    }
}