#include <bits/stdc++.h>

using namespace std;
typedef __int128 ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

ll gcd(ll a, ll b) {
    if(b==0)
        return a;
    return gcd(b, a%b);
}

void reduce(ll& a, ll& b) {
    ll g = gcd(a, b);
    a/=g;
    b/=g;
}

pair<ll, ll> solve(ll a, ll b, ll c, ll d) {
    reduce(a, b);
    reduce(c, d);
    ll n = c*b;
    ll m = a*d;
    reduce(n, m);
    ll p = a*n;
    ll q = b;
    reduce(p, q);
    return pair{p, q};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];
    ll ans = n+2;
    ans += accumulate(all(b), 0LL);
    for(int i = 0; i < n-1; i++) {
        ll cap = min(a[i], a[i+1]);
        auto [p,q] = solve(a[i], b[i], a[i+1], b[i+1]);
        ans -= cap*q/p;
    }
    cout << (long long)ans << "\n";
}