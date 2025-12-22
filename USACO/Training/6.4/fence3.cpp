/*
ID: markhwe1
TASK: fence3
LANG: C++17
*/

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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

constexpr double EPS = 1e-4;

int main() {
    ifstream cin("fence3.in");
    ofstream cout("fence3.out");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x1(n), y1(n), x2(n), y2(n);
    vector<int> xs, ys;
    for(int i = 0; i < n; i++) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        xs.pb(x1[i]);
        xs.pb(x2[i]);
        ys.pb(y1[i]);
        ys.pb(y2[i]);
    }
    sort(all(xs));
    sort(all(ys));
    xs.pb(100);
    ys.pb(100);
    xs.erase(unique(all(xs)), xs.end());
    ys.erase(unique(all(ys)), ys.end());
    
    auto inside = [&](int a, int b, double v) {
        if(a > b)
            swap(a, b);
        return a <= v && v <= b;
    };
    
    auto dist = [&](int a, int b, double c, double d) {
        double dx = a-c;
        double dy = b-d;
        return sqrt(dx*dx+dy*dy);
    };
    
    auto getDist = [&](int i, double X, double Y) {
        if(inside(x1[i], x2[i], X))
            return (double)abs(y1[i]-Y);
        if(inside(y1[i], y2[i], Y))
            return (double)abs(x1[i]-X);
        return min(dist(x1[i], y1[i], X, Y), dist(x2[i], y2[i], X, Y));
    };
    
    auto sumDists = [&](double X, double Y) {
        double tot = 0;
        for(int i = 0; i < n; i++)
            tot += getDist(i, X, Y);
        return tot;
    };
    
    auto go = [&](double X, double l, double r) {
        for(int it = 0; it < 8; it++) {
            double m = (l+r)/2;
            double base = sumDists(X, m);
            double hi = sumDists(X, m+EPS);
            if(base <= hi)
                r = m;
            else
                l = m;
        }
        return pair{(l+r)/2, sumDists(X, (l+r)/2)};
    };
    
    auto search = [&](double lx, double rx, double ly, double ry) {
        for(int it = 0; it < 8; it++) {
            double mx = (lx+rx)/2;
            auto [_, base] = go(mx, ly, ry);
            auto [__, hix] = go(mx+EPS, ly, ry);
            if(base <= hix)
                rx = mx;
            else
                lx = mx;
        }
        double X = (lx+rx)/2;
        auto [Y, d] = go(X, ly, ry);
        return pair{pair{X, Y}, d};
    };
    
    double ans = 1e9, ansX = 0, ansY = 0;
    
    auto check = [&](double x, double y, double dx, double dy) {
        // cout << "checking " << x << " " << x+dx << " " << y << " " << y+dy << endl;
        auto [XY, d] = search(x, x+dx, y, y+dy);
        auto [X, Y] = XY;
        if(d < ans) {
            ans = d;
            ansX = X;
            ansY = Y;
        }
    };
    
    for(int i = max(0, sz(xs)/2-6); i < min(sz(xs)-1, sz(xs)/2+6); i++) {
        for(int j = max(0, sz(ys)/2-6); j < min(sz(ys)-1, sz(ys)/2+6); j++) {
            double x = xs[i];
            double y = ys[j];
            double dx = xs[i+1]-xs[i];
            double dy = ys[j+1]-ys[j];
            check(x, y, dx, dy);
        }
    }

    cout << fixed << setprecision(1);
    cout << ansX << " " << ansY << " " << ans << "\n";
}