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
typedef pair<int, int> pii;
typedef vector<int> vi;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back

struct RollbackUF {
    vi e; vector<pii> st; vector<int> comps;
    RollbackUF(int n) : e(n, -1) {
        comps = vector<int>{n, n};
    }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return sz(st); }
    void rollback(int t) {
    	cout << "rolling back " << t << " " << time() << endl;
        for (int i = time(); i--> t;) {
            e[st[i].first] = st[i].second;
            comps.pop_back();
        }
        st.resize(t);
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        st.pb({a, e[a]});
        st.pb({b, e[b]});
        cout << "old size is " << sz(st) << endl;
        if (a == b) {
			comps.push_back(comps.back()); comps.push_back(comps.back());
            return false;
        }
        if (e[a] > e[b]) swap(a, b);
        st.pb({a, e[a]});
        st.pb({b, e[b]});
        e[a] += e[b]; e[b] = a;
        int s = comps.back();
        comps.push_back(s-1); comps.push_back(s-1);
        cout << "new size is " << sz(st) << endl;
        return true;
    }
    void push(pii E) { join(E.first, E.second); }
    void pop() { rollback(time()-2); }
    int query() { return comps.back(); }
};

template<typename D, typename U, typename Q>
struct offline_deletion : public D {
    int q;
    vector<Q> ans;
    vector<vector<U>> updates;
    offline_deletion(int n, int queries) : D(n), q(queries), ans(q) {
        int lg = 0; while((1 << lg) < q) lg++;
        updates.resize(1 << (lg + 1));
    }
    void update(int i, int l, int r, int L, int R, U u) {
        if (r < L || R < l) return;
        if (L <= l && r <= R) {
            updates[i].pb(u); return;
        }
        int m = (l + r) / 2;
        update(2 * i + 1, l, m, L, R, u);
        update(2 * i + 2, m + 1, r, L, R, u);
    }
    void insert(U u, int l, int r) {
        // cout << "inserting " << l << " " << r << endl; 
    update(0, 0, q - 1, l, r, u); }
    void insert(U u, int l) { insert(u, l, q - 1); }
    void solve(int i, int l, int r) {
        for (auto &u : updates[i]) D::push(u);
        if (l == r) ans[l] = D::query();
        else {
            int m = (l + r) / 2;
            solve(2 * i + 1, l, m);
            solve(2 * i + 2, m + 1, r);
        }
        for (int j = 0; j < (int) updates[i].size(); j++) D::pop();
    }
    void solve() { solve(0, 0, q - 1); }
};

struct Line {
    ll x, y1, y2;
    Line(ll X=0,ll Y1=0,ll Y2=0):x(X),y1(Y1),y2(Y2) {}
    bool operator<(Line l) const { return x<l.x; }
};

struct Slope {
    ll x,y;
    Slope(ll X=1,ll Y=1) {
        ll g = gcd(X,Y);
        x = X/g;
        y = Y/g;
        if(y < 0) {
            y = -y;
            x = -x;
        }
    }
    Slope operator-() const { return Slope(-x,y); }
    bool operator==(Slope s) const { return tie(x,y)==tie(s.x,s.y); }
    bool operator<(Slope s) const { return x*s.y < y*s.x; }
    bool operator>(Slope s) const { return x*s.y > y*s.x; }
    bool operator<=(Slope s) const { return x*s.y <= y*s.x; }
    ld eval() const { return (ld)x/y; }
};

typedef Slope Time;

Time getIntercept(ll x1, ll y1, ll x2, ll y2) {
    // Ax + By + C = 0
    ll C = x1*y2-y1*x2;
    ll A = y1-y2;
    return Time(-C, A);
}

Time INF(4e12, 1);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, w;
    cin >> n >> w;
    vector<Line> L(n);
    for(int i = 0; i < n; i++)
        cin >> L[i].x >> L[i].y1 >> L[i].y2;
    sort(all(L));
    vector<Time> coords{Time(0,1), -INF};
    vector<pair<pii,pair<Time,Time>>> events;
    for(int i = 0; i < n; i++) {
        Line left = L[i];
        for(int j = i+1; j < n; j++) {
            Line right = L[j];
            if(left.x==right.x)
                continue;
            vector<Time> times;
            if((right.y1<=left.y1&&left.y1<=right.y2)||(left.y1<=right.y1&&right.y1<=left.y2))
                times.push_back(-INF);
            Time e1 = getIntercept(left.x, left.y1, right.x, right.y2);
            Time e2 = getIntercept(left.x, left.y2, right.x, right.y1);
            if(e1 <= Time(0,1)) times.push_back(e1);
            if(e2 <= Time(0,1)) times.push_back(e2);
            sort(all(times));
            assert(sz(times) <= 2);
            if(sz(times)) {
                times.push_back(Time(0,1));
                for(auto t : times)
                    coords.push_back(t);
                events.push_back({{i,j},{times[0],times[1]}});
            }
        }
    }
    sort(all(coords));
    coords.erase(unique(all(coords)), coords.end());
    auto comp = [&](Time t) {
        return (int)(lower_bound(all(coords), t)-coords.begin());
    };
    offline_deletion<RollbackUF,pii,int> uf(n,sz(coords));
    for(auto& [e,t] : events) {
        int l = comp(t.first);
        int r = comp(t.second);
        cout << e.first << " " << e.second << " " << t.first.eval() << " " << t.second.eval() << endl;
        if(r-1>=l)
            uf.insert(e, l, r-1);
    }
    uf.solve();
    for(auto u : uf.ans)
    	cout << u << " ";
    cout << endl;
    if(uf.ans.front() == 1)
        cout << -1 << "\n";
    else {
        ld ans = 0;
        for(int i = 1; i < sz(coords); i++) {
            if(uf.ans[i-1] == 1)
                ans += coords[i].eval()-coords[i-1].eval();
        }
        cout << fixed << setprecision(20) << ans << "\n";
    }
}