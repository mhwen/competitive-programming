#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll compute(ll a, ll b, ll c, ll d, ll x) {
	return a*x*x*x+b*x*x+c*x+d;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<ll>> coefficients(5, vector<ll>(4));
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 4; j++) {
			cin >> coefficients[i][j];
		}
	}
	ll d;
	cin >> d;
	ll sum = 0;
	for(int i = 0; i <= 2; i++) {
		auto vals = coefficients[i];
		sum += compute(vals[0], vals[1], vals[2], vals[3], d);
	}
	for(int i = 0; i <= 2; i++) {
		auto vals = coefficients[i];
		ll res = compute(vals[0], vals[1], vals[2], vals[3], d);
		if(res*3 < sum)
			cout << "company " << i+1 << " not doing well\n";
		else
			cout << "company " << i+1 << " doing well\n";
	}
}