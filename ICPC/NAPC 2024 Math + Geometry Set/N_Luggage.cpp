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

constexpr ld EPS = 1e-9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, l;
	cin >> n >> l;
	vector<ld> dist(n);
	for(int i = 0; i < n; i++) {
		cin >> dist[i];
	}
	
	vector<pair<ld, ld>> bad;
	set<ld> seen;
	auto compute = [&](ld d) {
		ld D = round(d*100);
		if(seen.count(D))
			return;
		seen.insert(D);
		for(int i = 0; i*l-1 <= 10000; i++) {
			ld tLeft = max(EPS, (ld)i*l-1);
			ld tRight = i*l+1;
			ld maxSpeed = d/tLeft;
			ld minSpeed = d/tRight;
			bad.push_back({minSpeed, maxSpeed});
		}
	};
	
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			compute(abs(dist[j]-dist[i]));
		}
	}
	bad.push_back({10, 11});
	sort(bad.begin(), bad.end());
	ld prevBad = 0.1-EPS;
	ld best = -1;
	for(auto b : bad) {
		if(b.first > prevBad)
			best = min((ld)10, b.first);
		prevBad = max(prevBad, b.second);
		if(prevBad > 10)
			break;
	}
	if(best == -1)
		cout << "no fika\n";
	else
		cout << setprecision(20) << best << "\n";
}