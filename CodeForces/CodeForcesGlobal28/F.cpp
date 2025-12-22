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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); ++i)

constexpr int MAX = 61;
constexpr ll INF = 4e18;

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> a(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		vector<ll> b(n);
		vector<pair<ll, int>> B(n);
		for(int i = 0; i < n; i++) {
			cin >> b[i];
			B[i] = {b[i], i};
		}
		RMQ rmq(B);
			
		auto merge = [&](vector<ll> x, vector<ll> y) {
			vector<ll> res(MAX, INF);
			int xi = 0;
			int yi = 0;
			while(xi < MAX && yi < MAX) {
				if(xi+yi < MAX)
					res[xi+yi] = max(x[xi], y[yi]);
				if(xi == MAX)
					yi++;
				else if(yi == MAX)
					xi++;
				else if(x[xi] < y[yi])
					yi++;
				else
					xi++;
			}
			return res;
		};
		
		function<vector<ll>(int, int)> solve = [&](int l, int r) {
			if(r < l)
				return vector<ll>(MAX, 1);
			auto id = rmq.query(l, r+1).second;
			
			auto left = solve(l, id-1);
			auto right = solve(id+1, r);
			vector<ll> me(MAX);
			me[0] = a[id];
			for(int i = 1; i < MAX; i++) {
				me[i] = (me[i-1]+b[id]-1)/b[id];
			}
			me = merge(me, merge(left, right));
			for(int i = 1; i < MAX; i++) {
				me[i] = min(me[i], (me[i-1]+b[id]-1)/b[id]);
			}
			return me;
		};
		auto res = solve(0, n-1);
		for(int i = 0; i < MAX; i++) {
			if(res[i] == 1) {
				cout << i << "\n";
				break;
			}
		}
	}
}