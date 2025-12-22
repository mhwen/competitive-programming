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

vector<pair<int, int>> solve(int v, int off) {
	if(v == 1)
		return vector<pair<int, int>>{{off, off}};
	vector<pair<int, int>> m;
	for(int r = v-1; r > 0; r--) {
		auto res = solve(r, off);
		for(auto a : res)
			m.push_back(a);
		for(int i = 0; i < r-1; i++)
			m.emplace_back(i+off, i+off);
	}
	m.emplace_back(off, v-1+off);
	return m;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	ll best = 0;
	vector<pair<int, int>> moves;
	for(int mask = 0; mask < (1<<n); mask++) {
		vector<bool> take(n);
		for(int bit = 0; bit < n; bit++) {
			if(mask&(1<<bit))
				take[bit] = true;
		}
		ll sum = 0;
		vector<pair<int, int>> m;
		for(int i = 0; i < n; i++) {
			if(!take[i])
				sum += nums[i];
			else {
				int j = i;
				while(j < n && take[j])
					j++;
				sum += (j-i)*(j-i);
				for(int h = i; h < j; h++)
					if(nums[h] != 0)
						m.emplace_back(h, h);
				auto res = solve(j-i, i);
				for(auto a : res)
					m.push_back(a);
				i = j-1;
			}
		}
		if(sum > best) {
			best = max(best, sum);
			moves = m;
		}
	}
	cout << best << " " << sz(moves) << "\n";
	for(auto [a,b] : moves)
		cout << a+1 << " " << b+1 << "\n";
}