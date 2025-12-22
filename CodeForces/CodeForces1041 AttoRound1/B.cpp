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
        int n, x;
        cin >> n >> x;
        x--;
        string s;
        cin >> s;
        int left = -1, right = n;
        for(int i = x-1; i >= 0; i--) {
            if(s[i] == '#') {
                left = i;
                break;
            }
        }
        for(int i = x+1; i < n; i++) {
            if(s[i] == '#') {
                right = i;
                break;
            }
        }
        int nL = x-1, nR = x+1;
        cout << max(min(nL, n-right-1), min(left, n-nR-1))+2 << "\n";
    }
}