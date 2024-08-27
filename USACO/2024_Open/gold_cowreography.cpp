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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	string s, t;
	cin >> s >> t;
	ll ans = 0;
	map<int, queue<int>> ones;
	map<int, queue<int>> zeros;
	
	auto match = [&](int me, int index, map<int, queue<int>>& them) {
		auto it = them.lower_bound(me);
		if(it == them.end())
			it = them.begin();
		ans += (index-it->second.front()+k-1)/k;
		it->second.pop();
		if(it->second.empty())
			them.erase(it);
	};
	
	
	for(int i = 0; i < n; i++) {
		int me = i%k;
		if(s[i] == '1' && t[i] == '0') {
			if(zeros.empty())
				ones[me].push(i);
			else
				match(me, i, zeros);
		}
		else if(s[i] == '0' && t[i] == '1') {
			if(ones.empty())
				zeros[me].push(i);
			else
				match(me, i, ones);
		}
	}
	cout << ans << "\n";
}