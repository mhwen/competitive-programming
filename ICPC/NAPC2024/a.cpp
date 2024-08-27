#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

    for (int i = 1; i <= 9; i++) {
        for (int j = 0; j < (1 << i); j+=2) {
            int b = 0;
            for (int k = 1; k <= (1 << i); k+=1) {
                if (bpow(j, k, (1 << i)) == bpow(k, j, (1 << i))) {
                    b++;
                }
            }
            cout << i << " " << j << " " << b << endl;
        }
    }
}