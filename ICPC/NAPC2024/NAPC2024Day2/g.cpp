#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int MOD = 998244353;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : v(_v % MOD) {}

    mi operator+(const mi other) const { return mi(v + other.v); }
    mi operator-(const mi other) const { return mi(v - other.v); }
    mi operator*(const mi other) const { return mi((ll) v * other.v); }
    mi operator/(const mi other) const { return *this * other.inv(); }

#define OP(op) \
    mi &operator op##= (const mi other) { return *this = *this op other; }
    OP(+); OP(-); OP(*); OP(/);
#undef OP

    mi pow(ll e) const {
        mi res = 1;
        mi cur = *this;
        while (e) {
            if (e & 1) res *= cur;
            cur *= cur;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
}

typedef unsigned long long ll;
ull modmull(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
    s = __builtin_clz(n-1), d = n >> s;
    for (ull a : A) {
        ull p = modpow(a%n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n-1 && i != s) return 0;
    }
    return 1;
}

ull pollard(ull n) {
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    auto f = [&](ull x) { return modmul(x, x, n) + i; };
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

map<ull, int> my_factor(ull n) {
    auto primes = factor(n);
    map<ull, int> pf;
    for (auto p : primes) {
        pf[p]++;
    }
    return pf;
}

mi f[3000];
mi inv_f[3000];

void precomp() {
    f[0] = inv_f[0] = 1;
    for (int i = 1; i < 3000; i++) {
        f[i] = f[i - 1] * i;
        inv_f[i] = f[i].inv();
    }
}

mi c(int n, int k) {
    return f[n] * inv_f[k] * inv_f[n - k];
}

mi c2(int n, int k1, int k2) {
    return c(n, k1) * c(n - k1, k2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll m;
    cin >> m;

    precomp();

    auto pf = my_factor(m);
    int num_factors = 1;
    for (auto [_, e] : pf) {
        num_factors *= e + 1;
    }

    vector dp(num_factors+1, vector(num_factors+1, mi(0)));
    dp[0][0] = 1;
    for (int i = 1; i <= num_factors; i++) {
        mi psum = 0;
        for (int j = 0; j <= num_factors; j++) {
            dp[i][j] = psum;
            psum += dp[i-1][j];
        }
    }

    vector<mi> ans(num_factors+1);
    for (int k = 1; k <= num_factors; k++) {
        mi tot;
    }

}