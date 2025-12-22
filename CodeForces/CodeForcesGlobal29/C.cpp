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
        string s;
        cin >> s;
        vector<bool> a(n+2); //has
        vector<bool> b(n+2); //none
        vector<bool> c(n+2); //needs
        a[0] = true;
        for(int i = 0; i < n; i++) {
            if(s[i] == '0') {
                if(a[i] || c[i+1]) {
                    a[i+1] = true;
                    b[i+1] = true;
                    c[i+2] = true;
                }
                if(b[i]) {
                    c[i+2] = true;
                }
                if(c[i]) {
                    a[i+1] = true;
                    b[i+1] = true;
                }
            }
            else {
                if(a[i] || b[i])
                    b[i+1] = true;
            }
        }
        if(a[n] || b[n] || c[n+1])
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}