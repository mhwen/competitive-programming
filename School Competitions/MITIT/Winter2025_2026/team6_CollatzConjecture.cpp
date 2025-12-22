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

constexpr ll INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<ll> A(n);
        int starts = 0;
        for(int i = 0; i < n; i++) {
            cin >> A[i];
            if(A[i]%2==1) {
                starts++;
                A[i] = A[i]*3+1;
            }
        }
        vector<ll> dp(n*4+5, -INF);
        int ZERO = 2*n;
        dp[ZERO+starts] = 0;
        for(int i = 0; i < n; i++) {
            vector<ll> newDp = dp;
            for(int j = 0; j < sz(dp); j++) {
                if(dp[j] == -INF)
                    continue;
                ll a = A[i];
                int len = 0;
                int credits = j;
                while(a > 1) {
                    len++;
                    if(a%2==1) {
                        credits++;
                        a = a*3+1;
                    }
                    else {
                        credits--;
                        a = a/2;   
                    }
                    if(credits < ZERO)
                        break;
                    newDp[credits] = max(newDp[credits], dp[j]+len);
                }
                while(credits >= ZERO) {
                    len++;
                    if(a%2==1) {
                        credits++;
                        a = a*3+1;
                    }
                    else {
                        credits--;
                        a = a/2;   
                    }
                    if(credits < ZERO)
                        break;
                    newDp[credits] = max(newDp[credits], dp[j]+len);
                }
            }
            swap(dp, newDp);
        }
        ll best = 0;
        for(int i = 2*n; i < sz(dp); i++)
            best = max(best, dp[i]);
        cout << best+starts << "\n";
    }
}