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

constexpr ld INF = 1e18;
constexpr ld EPS = 1e-9;

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
    ld dist() { return sqrt(x*x+y*y); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P> bool onSegment(P s, P e, P p) {
    return abs(p.cross(s, e)) <= EPS && (s - p).dot(e - p) <= EPS;
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

typedef Point<ld> P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<P, P>> w(n);
    for(int i = 0; i < n; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        w[i] = {P(a, b), P(c, d)};
    }
    ld sx, sy, mySpeed;
    cin >> sx >> sy >> mySpeed;
    P me{sx, sy};
    ld fx, fy, FX, FY, fSpeed;
    cin >> fx >> fy >> FX >> FY >> fSpeed;
    pair<P, P> fellow{P(fx, fy), P(FX, FY)};
    
    vector<set<P>> lineToP(n);
    set<P> ends;
    for(int i = 0; i < n; i++) {
        if(onSegment(w[i].first, w[i].second, me))
            lineToP[i].insert(me);
        auto them = segInter(w[i].first, w[i].second, fellow.first, fellow.second);
        for(auto p : them) {
            lineToP[i].insert(p);
            ends.insert(p);
        }
        for(int j = i+1; j < n; j++) {
            auto inter = segInter(w[i].first, w[i].second, w[j].first, w[j].second);
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