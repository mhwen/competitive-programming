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
        int n, x, y;
        cin >> n >> x >> y;
        x = abs(x); y = abs(y);
        string s;
        cin >> s;
        for(char c : s) {
            if(c == '4') {
                if(x >= y) {
                    x--;
                }
                else {
                    y--;
                }
            }
            else {
                x--; y--;
            }
        }
        if(x <= 0 && y <= 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}