#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll solve(ll a, ll p) {
    if(a%2==1) {
        return 1;
    }
    vector<ll> twoPows(40);
    twoPows[0] = 1;
    for(int i = 1; i < sz(twoPows); i++)
        twoPows[i] = twoPows[i-1]*2;
    ll MOD = twoPows[p];
    ll ans = 0;


    function<ll(ll, ll)> pow = [&](ll a, ll b) -> ll {
        if(b==0)
            return 1;
        ll res = pow(a, b/2);
        res = res*res%MOD;
        if(b%2==1)
            res = res*a%MOD;
        return res;
    };
    auto check = [&](ll x) {
        return pow(a, x) == pow(x, a);
    };

    vector<bool> good(100);


    vector<ll> counts(sz(twoPows));
    for(int i = sz(counts)-2; i > 0; i--) {
        ll P = twoPows[i];
        ll count = MOD/P;
        for(int j = i+1; j < sz(counts); j++)
            count -= counts[j];
        counts[i] = count;
    }
    for(int i = sz(counts)-2; i >= 0; i--) {
        ll P = twoPows[i];
        for(int x = 1; x <= min(30LL, MOD); x++) {
            if(x%P == 0 && x%twoPows[i+1] != 0)
                counts[i]--;
        }
        if(i*a >= p) {
            // cout << "contribute 2^i:" << i << " " << counts[i] << endl;
            ans += counts[i];
        }
    }


    // for(int i = 0; i <= p; i++)
        // cout << i << " " << counts[i] << endl;
    for(int x = 1; x <= min(30LL, MOD); x++) {
        bool good = check(x);
        if(good) {
            // cout << x << " good" << endl;
            ans++;
        }
        // cout << x << " " << good << endl;
        // if(!good && x%twoPows[min(max(1LL, p/a), (ll)sz(twoPows)-1)]==0) {
        //     cout << x << " bad" << endl;
        //     ans--;
        // }
        // if(good && x%twoPows[min(max(1LL, p/a), (ll)sz(twoPows)-1)]!=0) {
        //     cout << x << " good " << endl;
        //     ans++;
        // }
    }
    return ans;
}

ll bpow(ll a, ll b, ll m) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    // for (int i = 1; i <= 9; i++) {
    //     for (int j = 1; j <= (1 << i); j++) {
    //         int b = 0;
    //         for (int k = 1; k <= (1 << i); k+=1) {
    //             if (bpow(j, k, (1 << i)) == bpow(k, j, (1 << i))) {
    //                 b++;
    //             }
    //         }
    //         ll myAns = solve(j, i);
    //         if(myAns != b)
    //             cout << "bad " << j << " " << i << " " << b << " " << myAns << endl;
    //     }
    // }

    // cout << solve(2, 2); // should be 2

    int t;
    cin >> t;
    while(t-->0) {

        ll a;
        int p;
        cin >> a >> p;
        cout << solve(a, p) << "\n";
        
    }
}