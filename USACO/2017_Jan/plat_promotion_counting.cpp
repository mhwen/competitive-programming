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
#include <fstream>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("promote.in");
	ofstream cout("promote.out");
	int n;
	cin >> n;
	vector<ll> P(n);
	for(ll& i : P)
		cin >> i;
	vector<vector<int>> con(n);
	for(int i = 1; i < n; i++) {
		int par;
		cin >> par;
		par--;
		con[par].push_back(i);
	}
	vector<int> pos(n);
	int id = 0;
	vector<int> sizes(n, 1);
	function<void(int)> dfs = [&](int curr) {
		pos[curr] = id++;
		for(int next : con[curr]) {
			dfs(next);
			sizes[curr] += sizes[next];
		}
	};
	dfs(0);
	
	vector<int> tree(2*n);
	auto update = [&](int p) {
		p += n;
		while(p > 0) {
			tree[p]++;
			p /= 2;
		}
	};
	auto query = [&](int l, int r) {
		l += n; r += n;
		int res = 0;
		for(; l <= r; l/=2, r/=2) {
			if(l%2==1) {
				res += tree[l];
				l++;
			}
			if(r%2==0) {
				res += tree[r];
				r--;
			}
		}
		return res;
	};
	
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b){
		return P[a] < P[b];
	});
	reverse(all(order));
	vector<int> ans(n);
	for(int i : order) {
		ans[i] = query(pos[i], pos[i]+sizes[i]-1);
		update(pos[i]);
	}
	for(int i : ans)
		cout << i << "\n";
}