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

int query(int i, int x) {
    cout << "? " << i << " " << x << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int x) {
    cout << "! " << x << endl;
}

pair<vector<int>, vector<int>> split(vector<int>& v, int b) {
    vector<int> z, o;
    for(auto a : v) {
        if(a&b)
            o.pb(a);
        else
            z.pb(a);
    }
    return {z, o};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        int bit = 0;
        vector<int> ids(n-1);
        vector<int> p(n);
        iota(all(p), 1);
        iota(all(ids), 1);
        while((1<<bit) <= n && sz(p) > 1) {
            int B = (1<<bit);
            auto [zero, one] = split(p, B);
            vector<int> z, o;
            for(int i : ids)
                if(query(i, B) == 0)
                    z.pb(i);
                else
                    o.pb(i);
            if(sz(z) == sz(zero)) {
                assert(sz(o)+1 == sz(one));
                ids = o;
                p = one;
            }
            else {
                assert(sz(z)+1 == sz(zero));
                ids = z;
                p = zero;
            }
            bit++;
        }
        assert(sz(p) == 1);
        answer(p.front());
    }
}