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
        int n;
        cin >> n;
        vector<int> p(n);
        int a = -1, b = -1;
        for(int i = 0; i < n; i++) {
            cin >> p[i];
            if(p[i] == 1)
                a = i;
            if(p[i] == n)
                b = i;
        }
        string s;
        cin >> s;
        if(s[0] == '1' || s[n-1] == '1' || s[a] == '1' || s[b] == '1') {
            cout << -1 << "\n";
            continue;
        }
        cout << 5 << "\n";
        cout << 1 << " " << a+1 << "\n";
        cout << 1 << " " << b+1 << "\n";
        cout << a+1 << " " << n << "\n";
        cout << b+1 << " " << n << "\n";
        cout << min(a,b)+1 << " " << max(a,b)+1 << "\n";
    }
}