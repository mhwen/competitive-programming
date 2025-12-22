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
typedef __int128 ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ld INF = 1e18;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    ld dist() { 
        ld X = x.eval();
        ld Y = y.eval();
        return sqrt(X*X+Y*Y);
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

ll gcd(ll a, ll b) {
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

template<class T>
struct F {
    ll p, q;
    F() : p(0), q(1) {}
    F(ll a) : p(a), q(1) {}
    F(ll _p, ll _q) : p(_p), q(_q) {
        assert(q != 0);
        ll g = gcd(p, q);
        p /= g;
        q /= g;
        if(q < 0) {
            p = -p;
            q = -q;
        }
    }
    bool operator<(F f) const { return p*f.q < q*f.p; }
    bool operator==(F f) const { return p*f.q == q*f.p; }
    bool operator<(T d) const { return p < q*d; }
    bool operator>(T d) const { return p > q*d; }
    bool operator==(T d) const { return p == q*d; }
    bool operator<=(T d) const { return p <= q*d; }
    
    F operator+(F f) const { return F(p*f.q+q*f.p, q*f.q); }
    F operator-(F f) const { return F(p*f.q-q*f.p, q*f.q); }
    F operator*(F f) const { return F(p*f.p, q*f.q); }
    F operator/(F f) const { return F(p*f.q, q*f.p); }
    
    ld eval() { return (ld)p/q; }
    friend ostream& operator<<(ostream& os, F f) {
        return os << (long long)f.p << "/" << (long long)f.q; }
};

typedef F<ll> Frac;
typedef Point<Frac> P;

Frac parse() {
    string s;
    cin >> s;
    ll res = 0;
    ll pow = 1;
    bool dec = false;
    bool neg = false;
    for(char c : s) {
        if(c == '-') {
            neg = true;
            continue;
        }
        if(c == '.') {
            dec = true;
            continue;
        }
        res = res*10+c-'0';
        if(dec)
            pow *= 10;
    }
    if(neg)
        res = -res;
    return Frac(res, pow);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<P, P>> w(n);
    for(int i = 0; i < n; i++) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        w[i] = {P(Frac(a), Frac(b)), P(Frac(c), Frac(d))};
    }
    Frac sx, sy;
    sx = parse();
    sy = parse();
    ld mySpeed;
    cin >> mySpeed;
    P me{sx, sy};
    Frac fx, fy, FX, FY;
    fx = parse();
    fy = parse();
    FX = parse();
    FY = parse();
    ld fSpeed;
    cin >> fSpeed;
    pair<P, P> fellow{P(fx, fy), P(FX, FY)};
    
    vector<set<P>> lineToP(n);
    set<P> ends;
    for(int i = 0; i < n; i++) {
        if(onSegment(w[i].first, w[i].second, me))
            lineToP[i].insert(me);
        auto them = segInter(w[i].first, w[i].second, fellow.first, fellow.second);
        assert(sz(them) <= 1);
        for(auto p : them) {
            lineToP[i].insert(p);
            ends.insert(p);
        }
        for(int j = i+1; j < n; j++) {
            auto inter = segInter(w[i].first, w[i].second, w[j].first, w[j].second);
            assert(sz(inter) <= 1);
            for(auto p : inter) {
                lineToP[i].insert(p);
                lineToP[j].insert(p);
            }
        }
    }
    
    map<P, vector<P>> con;
    map<P, ld> dist;
    for(int i = 0; i < n; i++) {
        vector<P> line;
        for(auto a : lineToP[i])
            line.push_back(a);
        for(int j = 0; j < sz(line)-1; j++) {
            P a = line[j];
            P b = line[j+1];
            con[a].push_back(b);
            con[b].push_back(a);
        }
    }
    priority_queue<pair<ld, P>> q;
    q.push({0, me});
    while(!q.empty()) {
        auto C = q.top();
        q.pop();
        ld d = -C.first;
        P curr = C.second;
        if(dist.count(curr))
            continue;
        dist[curr] = d;
        for(auto next : con[curr]) {
            if(!dist.count(next)) {
                P diff = next-curr;
                q.push({-d-diff.dist(), next});
            }
        }
    }
    
    ld ans = INF;
    
    for(auto p : ends) {
        if(dist.count(p)) {
            ld theirTime = (p-fellow.first).dist()/fSpeed;
            ld myTime = dist[p]/mySpeed;
            if(myTime <= theirTime) {
                ans = min(ans, theirTime);
            }
        }
    }
    
    if(ans == INF)
        cout << "Impossible\n";
    else
        cout << fixed << setprecision(20) << ans << "\n";
    
}