#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <random>
#include <chrono>

using namespace std;

typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randval(int n) {
	return uniform_int_distribution(1, n)(rng);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> x(n);
	vector<ll> y(n);
	for(int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	while(true) {
		int i = randval(n)-1;
		int j = randval(n)-1;
		if(i == j)
			continue;
		ll x1 = x[i];
		ll y1 = y[i];
		ll x2 = x[j];
		ll y2 = y[j];
		ll a = y1-y2;
		ll b = x2-x1;
		ll c = y1*(x2-x1)-(y2-y1)*x1;
		int count = 0;
		for(int k = 0; k < n; k++) {
			if(a*x[k]+b*y[k]==c)
				count++;
		}
		if(count >= n/8) {
			cout << a << " " << b << " " << c << "\n";
			return 0;
		}
	}
}