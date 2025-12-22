#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

vector<ll> divisors(ll v) {
    vector<ll> d;
    for(ll i = 1; i*i <= v; i++) {
        if(v%i==0) {
            d.push_back(i);
            if(i*i != v)
                d.push_back(v/i);
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    ll cap = *min_element(all(a))/4;
    
    auto check = [&](ll L) {
        if(L > cap)
            return false;
        set<ll> seen;
        for(int i = 0; i < sz(a); i++) {
            seen.insert(a[i]%L);
            if(sz(seen) > 3)
                return false;
        }
        return true;
    };
    
    if(sz(a) <= 3) {
        cout << cap*(cap+1)/2 << "\n";
    }
    else {
        set<ll> good;
        for(int i = 0; i < 4; i++) {
            for(int j = i+1; j < 4; j++) {
                ll v = abs(a[i]-a[j]);
                for(auto d : divisors(v)) {
                    if(check(d))
                        good.insert(d);
                }
            }
        }
        ll ans = 0;
        for(auto g : good)
            ans += g;
        cout << ans << "\n";
    }
}