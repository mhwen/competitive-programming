#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        bool good = true;
        int n, q, c;
        cin >> n >> q >> c;
        vector<int> a(n);
        vector<int> free;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(a[i] == 0)
                free.push_back(i);
        }
        vector<int> loBound(n, n);
        for(int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            loBound[r] = min(loBound[r], l);
        }
        int prev = -1;
        int pId = -1;
        vector<int> pMax(n+1);
        
        for(int i = 0; i < n; i++) {
            if(loBound[i] < prev) {
                good = false;
                goto done;
            }
            if(loBound[i] != n)
                prev = i;
        }
        for(int i = 0; i < n; i++) {
            if(loBound[i] == n) {
                if(a[i] == 0)
                    a[i] = 1;
            }
            else {
                int L = loBound[i];
                int mx = pMax[L+1];
                for(int j = L; j < i; j++) {
                    mx = max(mx, a[j]);
                }
                if(pMax[L+1] < mx) {
                    while(pId+1 < sz(free) && free[pId+1] <= L)
                        pId++;
                    if(pId == -1) {
                        good = false;
                        goto done;
                    }
                    assert(a[free[pId]] < mx);
                    a[free[pId]] = mx;
                }
                if(a[i] == 0)
                    a[i] = mx+1;
            }
            pMax[i+1] = max(pMax[i], a[i]);
        }
    
        for(int i = 0; i < n; i++) {
            pMax[i+1] = max(pMax[i], a[i]);
            int L = loBound[i];
            if(L != n) {
                if(pMax[L+1] != pMax[i])
                    good = false;
                if(a[i] <= pMax[L+1])
                    good = false;
            }
            if(a[i] > c)
                    good = false;
        }
        done:
        if(good) {
            for(int i = 0; i < n; i++) {
                if(i > 0)
                    cout << " ";
                cout << a[i];
            }
        }
        else
            cout << -1;
        cout << "\n";
    }
}