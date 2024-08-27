#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>
#include <random>
#include <chrono>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

long long randval() {
	return uniform_int_distribution(-1000, 1000)(rng);
}

void solve(ll ee, ll oo, ll eo, ll oe) {
	vector<ll> x;
	vector<ll> y;
	
	auto check = [&](ll X, ll Y) {
		for(int i = 0; i < sz(x); i++) {
			for(int j = i+1; j < sz(x); j++) {
				ll dx = x[j]-x[i];
				ll dy = y[j]-y[i];
				ll DX = X-x[i];
				ll DY = Y-y[i];
				if(DX*dy==DY*dx)
					return false;
			}
		}
		return true;
	};
	
	auto add = [&](ll X, ll Y) {
		cout << X << " " << Y << "\n";
		x.push_back(X);
		y.push_back(Y);
	};
	
	while(ee+oo+eo+oe > 0) {
		ll X = randval();
		ll Y = randval();
		if(X%2) {
			if(Y%2) {
				if(ee == 0)
					continue;
				if(check(X, Y)) {
					add(X, Y);
					ee--;
				}
			}
			else {
				if(eo == 0)
					continue;
				if(check(X, Y)) {
					add(X, Y);
					eo--;
				}
			}
		}
		else {
			if(Y%2) {
				if(oe == 0)
					continue;
				if(check(X, Y)) {
					add(X, Y);
					oe--;
				}
			}
			else {
				if(oo == 0)
					continue;
				if(check(X, Y)) {
					add(X, Y);
					oo--;
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	//ee oo eo/oe
	//ee eo oe
	//oo eo oe
	
	//ee oo eo oe
	//a  b  c  d
	//abc + abd + acd + bcd == diff
	//a + b + c + d == t
	
	ll t, b;
	cin >> t >> b;
	ll needed = t*(t-1)*(t-2)/6-b;
	for(ll ee = 0; ee <= t; ee++) {
		for(ll oo = 0; oo+ee <= t; oo++) {
			for(ll eo = 0; eo+oo+ee <= t; eo++) {
				ll oe = t-eo-oo-ee;
				ll bad = ee*oo*(eo+oe)+(ee+oo)*eo*oe;
				if(bad == needed) {
					solve(ee, oo, eo, oe);
					return 0;
				}
			}
		}
	}
	cout << "IMPOSSIBLE\n";
	
}