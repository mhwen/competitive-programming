#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

bool half(pair<ll, ll> p) {
    return p.second < 0 || (p.second == 0 && p.first < 0);
}

ll cross(pair<ll, ll> a, pair<ll, ll> b) {
    return a.first*b.second - a.second*b.first;
}

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n", 2e5);
    int q = opt<int>("q", 2e5);
    int abBound = opt<int>("ab-bound", 1e9);
    int cBound = opt<int>("c-bound", 1e9);
    bool sameSlopeQuery = opt<bool>("same-slope-query", false);
	cout << n << " " << q << "\n";
    vector<pair<ll, ll>> slopes;
    set<pair<ll, ll>> p;
    for(int i = 0; i < n/2-100; i++) {
        ll dx = rnd.next(-1000, 1000);
        ll dy = rnd.next(-1000, 1000);
        while(dx == 0 && dy == 0) {
            dx = rnd.next(-1000, 1000);
            dy = rnd.next(-1000, 1000);
        }
        slopes.emplace_back(dx, dy);
        slopes.emplace_back(-dx, -dy);
    }
    sort(all(slopes), [](pair<ll, ll> a, pair<ll, ll> b) {
        return half(a) == half(b) ? cross(a, b) > 0 : half(a) < half(b);
    });
    ll x = rnd.next(-100000, 100000);
    ll y = rnd.next(-100000, 100000);
    for(int i = 0; i < sz(slopes); i++) {
        p.insert({x, y});
        x += slopes[i].first;
        y += slopes[i].second;
    }
    
    while(sz(p) < n) {
        pair<ll, ll> point;
        do {
            point = {rnd.next(-1000, 1000), rnd.next(-1000, 1000)};
        } while(p.count(point));
        p.insert(point);
    }
    vector<pair<ll, ll>> ps;
    for(auto point : p)
        ps.push_back(point);
    shuffle(all(ps));
    for(auto [x, y] : ps)
        cout << x << " " << y << "\n";

    int A = rnd.next(-abBound, abBound);
    int B = rnd.next(-abBound, abBound);
    while(A == 0 && B == 0) {
        A = rnd.next(-abBound, abBound);
        B = rnd.next(-abBound, abBound);
    }
    for(int i = 0; i < q; i++) {
        if(!sameSlopeQuery) {
            A = rnd.next(-abBound, abBound);
            B = rnd.next(-abBound, abBound);
            while(A == 0 && B == 0) {
                A = rnd.next(-abBound, abBound);
                B = rnd.next(-abBound, abBound);
            }
        }
        int C = rnd.next(-cBound, cBound);
        cout << A << " " << B << " " << C << "\n";
    }
}