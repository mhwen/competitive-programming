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

struct ST {
	int n;
	vector<ll> tree;
	ST(int _n) : n(_n), tree(2*n) {}
	ll query(int l, int r) {
		l+=n; r+=n;
		ll res = 0;
		while(l<=r) {
			if(l%2==1)
				res += tree[l++];
			if(r%2==0)
				res += tree[r--];
			l/=2; r/=2;
		}
		return res;
	}
	void update(int p, int amt) {
		p+=n;
		while(p > 0) {
			tree[p]+=amt;
			p/=2;
		}
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
		vector<int> a(n);
		vector<int> b(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		for(int i = 0; i < n; i++)
			cin >> b[i];
		map<int, vector<int>> seen;
		for(int i = 0; i < n; i++)
			seen[b[i]].push_back(a[i]);
		ST st(n+1);
		ll inv = 0;
		for(auto& [B, A] : seen) {
			for(auto val : A)
				inv += st.query(val+1, n);
			for(auto val : A)
				st.update(val, 1);
		}
		ll winner = inv%2;
		auto answer = [&]() {
			if(winner)
				cout << "A";
			else
				cout << "B";
		};
		answer();
		for(int i = 0; i < n-1; i++) {
			char c;
			int l, r, d;
			cin >> c >> l >> r >> d;
			int len = r-l+1;
			d %= len;
			ll rem = len-d;
			if(rem*d%2==1)
				winner ^= 1;
			answer();
		}
		cout << "\n";
	}
}