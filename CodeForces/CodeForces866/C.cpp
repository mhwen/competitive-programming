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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<set<int>> con(n);
	vector<vector<int>> leaves(n);
	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].insert(b);
		con[b].insert(a);
	}
	vector<bool> dead(n);
	for(int i = 0; i < n; i++) {
		if(sz(con[i]) == 1) {
			for(auto next : con[i]) {
				if(sz(con[next]) > 2) {
					con[next].erase(i);
					leaves[next].push_back(i);
					dead[i] = true;
				}
			}
		}
	}
	bool bad = false;
	for(int i = 0; i < n; i++) {
		if(sz(con[i]) > 2) {
			bad = true;
			break;
		}
	}
	if(bad)
		cout << "NO\n";
	else {
		vector<int> ans;
		int curr = -1;
		for(int i = 0; i < n; i++) {
			if(sz(con[i]) == 1 && !dead[i])
				curr = i;
		}
		vector<int> chain;
		chain.push_back(curr);
		int next = *con[curr].begin();
		chain.push_back(next);
		int prev = curr;
		while(sz(con[next]) > 1) {
			int newNext = -1;
			for(auto nn : con[next]) {
				if(nn != prev) {
					newNext = nn;
				}
			}
			prev = next;
			next = newNext;
			chain.push_back(newNext);
		}
		for(int i = 0; i < sz(chain); i+=2) {
			ans.push_back(chain[i]);
			if(i+1 < sz(chain))
				for(auto l : leaves[chain[i+1]])
					ans.push_back(l);
		}
		for(int i = sz(chain)-1-sz(chain)%2; i >= 1; i-=2) {
			ans.push_back(chain[i]);
			for(auto l : leaves[chain[i-1]])
				ans.push_back(l);
		}
		
		cout << "YES\n";
		for(auto a :ans)
			cout << a+1 << " ";
		cout << "\n";
	}
}