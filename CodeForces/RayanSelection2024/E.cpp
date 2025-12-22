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

ll fact(int n) {
	ll res = 1;
	for(int i = 1; i <= n; i++)
		res *= i;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		int K = k;
		if(n == 1) {
			if(k > 1)
				cout << "NO\n";
			else {
				cout << "YES\n";
				cout << 1 << "\n";
			}
			continue;
		}
		if(k == 1) {
			cout << "NO\n";
			continue;
		}
		if(n%2==0 && k%2==1) {
			cout << "NO\n";
			continue;
		}
		if(n <= 9 && k > fact(n)) {
			cout << "NO\n";
			continue;
		}
		vector<int> base(n);
		iota(all(base), 1);
		set<vector<int>> seen;
		if(k%2==1) {
			assert(n%2==1);
			vector<int> a = base;
			vector<int> b = base;
			rotate(b.begin(), b.begin()+n/2+1, b.end());
			vector<int> c(n);
			int need = 3*(n+1)/2;
			for(int i = 0; i < n; i++) {
				c[i] = need-a[i]-b[i];
			}
			seen.insert(a);
			seen.insert(b);
			seen.insert(c);
			k-=3;
		}
		do {
			vector<int> mirror(n);
			for(int i = 0; i < n; i++) {
				mirror[i] = n+1-base[i];
			}
			if(!seen.count(mirror) && !seen.count(base)) {
				seen.insert(mirror);
				seen.insert(base);
				k-=2;
			}
		} while(next_permutation(all(base)) && k>0);
		if(sz(seen) != K) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		for(auto& v : seen) {
			for(auto a : v)
				cout << a << " ";
			cout << "\n";
		}
	}
}