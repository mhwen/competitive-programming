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
    int n, m;
    while(cin >> n >> m) {
        if(n == 0 && m == 0)
            break;
        priority_queue<ll> a, b;
        for(int i = 0; i < n; i++) {
            ll A;
            cin >> A;
            a.push(-A);
        }
        for(int i = 0; i < m; i++) {
            ll B;
            cin >> B;
            b.push(-B);
        }
        ll ans = 0;
        bool bad = false;
        while(!a.empty()) {
            ll next = -a.top();
            a.pop();
            while(!b.empty() && -b.top() < next)
                b.pop();
            if(b.empty()) {
                bad = true;
                break;
            }
            else {
                ans -= b.top();
                b.pop();
            }
        }
        if(bad)
            cout << "Impossible\n";
        else
            cout << ans << "\n";
        
    }
}