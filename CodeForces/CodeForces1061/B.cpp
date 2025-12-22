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
        string s;
        cin >> s;
        bool b = false;
        for(char c : s)
            if(c == 'B')
                b = true;
        while(q-->0) {
            int v;
            cin >> v;
            if(b) {
                int pos = 0;
                int steps = 0;
                while(v > 0) {
                    if(s[pos] == 'A')
                        v--;
                    else
                        v /= 2;
                    steps++;
                    pos = (pos+1)%n;
                }
                cout << steps << "\n";
            }
            else {
                cout << v << "\n";
            }
        }
    }
}