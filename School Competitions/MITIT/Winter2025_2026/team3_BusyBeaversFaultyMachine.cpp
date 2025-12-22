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
    srand(12345);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n, b;
        cin >> n >> b;
        vector<int> d(n);
        for(int i = 0; i < n; i++)
            cin >> d[i];
        if(accumulate(all(d), 0LL)%(b-1) != 0) {
            cout << "NO\n";
            continue;
        }
        reverse(all(d));
        
        auto go = [&](int curr) {
            vector<int> x, y;
            multiset<int> X, Y;
            int carry = 0;
            for(int i : d) {
                int sum = curr+i+carry;
                x.pb(curr);
                y.pb(sum%b);
                X.insert(curr);
                Y.insert(sum%b);
                curr = sum%b;
                carry = sum/b;
            }
            if(carry != 0) {
                int sum = curr+carry;
                x.pb(curr);
                y.pb(sum%b);
                X.insert(curr);
                Y.insert(sum%b);
            }
            if(X != Y)
                return false;
            if(x.back() == 0 || y.back() == 0) {
                x.pb(1);
                y.pb(1);
            }
            cout << "YES\n";
            reverse(all(x));
            reverse(all(y));
            cout << sz(x) << "\n";
            for(int i = 0; i < sz(x); i++) {
                if(i > 0)
                    cout << " ";
                cout << x[i];
            }
            cout << "\n";
            for(int i = 0; i < sz(y); i++) {
                if(i > 0)
                    cout << " ";
                cout << y[i];
            }
            cout << "\n";
            return true;
        };
        bool found = false;
        for(int i = 0; i < b; i++) {
            if(go(i)) {
                found = true;
                break;
            }
        }
        if(!found)
            cout << "NO\n";
    }
}