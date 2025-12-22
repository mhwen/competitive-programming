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

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, d;
	cin >> n >> d;
	map<int, ll> x;
	map<int, ll> y;
	vector<int> xx(n);
	vector<int> yy(n);
	for(int i = 0; i < n; i++) {
		int X, Y;
		cin >> X >> Y;
		x[X]++;
		y[Y]++;
		xx[i] = X;
		yy[i] = Y;
	}
	sort(all(xx));
	sort(all(yy));
	
	auto Count = [](vector<int> m) {
		ll ans = 0;
		int prev = m[0];
		ll distSoFar = 0;
		for(int i = 1; i < sz(m); i++) {
			ll dd = m[i]-prev;
			distSoFar += i*dd%MOD;
			ans += distSoFar;
			ans %= MOD;
			prev = m[i];
		}
		return ans%MOD;
	};
	
	auto getGain = [](ll gain, ll cnt) {
		return (gain*cnt%MOD + cnt*(cnt-1)%MOD)%MOD;
	};
	
	auto find = [&](map<int, ll>& m) {
		if(sz(m) == 1) {
			return pair{0LL, true};
		}
		bool low = true;
		auto lo = m.begin();
		auto hi = m.rbegin();
		ll myCnt = lo->second;
		if(lo->second > hi->second) {
			myCnt = hi->second;
			low = false;
		}

		ll gain = n-2*myCnt+1;
		return pair{gain, low};
	};
	
	ll curr = 0;
	auto process = [&](map<int, ll>& m, bool left, ll& steps) {
		if(sz(m) == 1) {
			steps = 0;
			return;
		}
		if(left) {
			auto lo = m.begin();
			int me = lo->first;
			ll myCnt = lo->second;
			m.erase(lo);
			auto next = m.begin();
			int them = next->first;
			ll diff = them-me;
			ll gain = n-2*myCnt+1;
			if(diff*myCnt <= steps) {
				curr += diff*getGain(gain, myCnt)%MOD;
				curr %= MOD;
				steps -= diff*myCnt;
				m[them] += myCnt;
			}
			else {
				ll take = steps/myCnt;
				ll extra = steps%myCnt;
				int N = (int)(me+take);
				int N1 = N+1;
				curr += take*getGain(gain, myCnt)%MOD;
				curr %= MOD;
				curr += getGain(gain, extra);
				curr %= MOD;
				m[N] += myCnt-extra;
				m[N1] += extra;
				steps = 0;
			}
		}
		else {
			auto hi = m.rbegin();
			int me = hi->first;
			ll myCnt = hi->second;
			m.erase(hi->first);
			auto next = m.rbegin();
			int them = next->first;
			ll diff = me-them;
			ll gain = n-2*myCnt+1;
			if(diff*myCnt <= steps) {
				curr += diff*getGain(gain, myCnt)%MOD;
				curr %= MOD;
				steps -= diff*myCnt;
				m[them] += myCnt;
			}
			else {
				ll take = steps/myCnt;
				ll extra = steps%myCnt;
				int N = (int)(me-take);
				int N1 = N-1;
				curr += take*getGain(gain, myCnt)%MOD;
				curr %= MOD;
				curr += getGain(gain, extra);
				curr %= MOD;
				m[N] += myCnt-extra;
				m[N1] += extra;
				steps = 0;
			}
		}
	};
	
	ll ans = 0;

	for(int i = 0; i < d; i++) {
		ll steps;
		cin >> steps;
		while(steps > 0) {
			auto l = find(x);
			auto r = find(y);
			if(l.first >= r.first)
				process(x, l.second, steps);
			else
				process(y, r.second, steps);
		}
		ans = (ans+curr)%MOD;
	}
	ll start = Count(xx)+Count(yy);
	start %= MOD;
	cout << (start*d%MOD-ans+MOD)%MOD << "\n";
}