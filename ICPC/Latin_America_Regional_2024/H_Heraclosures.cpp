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

constexpr int SQRT = 85;
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> B(n);
	for(int i = 0; i < n; i++)
		cin >> B[i];
	int m;
	cin >> m;
	vector<int> deg(n);
	vector<vector<int>> revAdj(n);
	for(int i = 0; i < m; i++) {
		int f, g;
		cin >> f >> g;
		f--; g--;
		deg[f]++;
		revAdj[g].push_back(f);
	}
	queue<int> bfs;
	vector<int> order;
	vector<vector<ll>> coeff(n, vector<ll>(n));
	for(int i = 0; i < n; i++) {
		if(deg[i] == 0)
			bfs.push(i);
		coeff[i][i] = 1;
	}
	while(!bfs.empty()) {
		int curr = bfs.front();
		bfs.pop();
		order.push_back(curr);
		for(int next : revAdj[curr]) {
			deg[next]--;
			for(int i = 0; i < n; i++) {
				coeff[next][i] += coeff[curr][i];
				coeff[next][i] %= MOD;
			}
			if(deg[next] == 0)
				bfs.push(next);
		}
	}
	int q;
	cin >> q;
	vector<ll> newB = B;
	vector<ll> tot(n);
	ll ans = 0;
	vector<bool> touched(n);
	vector<int> updated;
	
	auto reset = [&]() {
		updated.clear();
		for(int i = 0; i < n; i++) {
			tot[i] = 0;
			touched[i] = false;
		}
		B = newB;
		for(int i : order) {
			tot[i] += B[i];
			tot[i] %= MOD;
			for(int next : revAdj[i]) {
				tot[next] += tot[i];
				tot[next] %= MOD;
			}
		}
	};
	int cnt = SQRT;
	reset();

	int k = 1;
	while(q-->0) {
		cnt--;
		if(cnt == 0) {
			reset();
			cnt = SQRT;
		}
		char t;
		cin >> t;
		if(t == 'U') {
			int j;
			ll v;
			cin >> j >> v;
			j--;
			if(!touched[j]) {
				touched[j] = true;
				updated.push_back(j);
			}
			newB[j] = v;
		}
		else {
			int j;
			cin >> j;
			j--;
			ll val = tot[j];
			for(int i : updated) {
				ll delta = (newB[i]-B[i])%MOD*coeff[j][i]%MOD;
				val += delta;
				while(val < 0)
					val += MOD;
				val %= MOD;
			}
			ans += val*k%MOD;
			ans %= MOD;
			k++;
		}
	}
	cout << ans << "\n";
	
}