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
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

vector<pii> normalize(vector<pii> ranges) {
	sort(all(ranges));
	vector<pii> res;
	for(auto [l, r] : ranges) {
		if(r < l)
			continue;
		if(res.empty() || l > res.back().second+1)
			res.push_back({l, r});
		else
			res.back().second = r;
	}
	return res;
}

bool inRange(pii range, int num) {
	return range.first <= num && num <= range.second;
}

bool inside(vector<pii>& ranges, int num) {
	for(auto range : ranges)
		if(inRange(range, num))
			return true;
	return false;
}

constexpr pii BAD = {-1, -2};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		string s;
		cin >> s;
		auto process = [&](pii range, char type, int add) -> pii {
			if(range.first > range.second)
				return BAD;
			if(type == '>') {
				auto res = pair{(range.first+m+1)/2, (range.second+m)/2};
				if(add == 0)
					res.first = max(res.first, 1);
				if(add == 1)
					res.second = min(res.second, m-2);
				return res;
			}
			else if(type == '=') {
				if(add == 0 && ) {
					if(inRange(range, 0))
						return {0, 0};
					else
						return BAD;
				}
				else {
					if(inRange(range, m-2))
						return {m-1, m-1};
					else
						return BAD;
				}
			}
			else {
				auto res = pair{(range.first+1)/2, range.second/2};
				if(add == 0)
					res.first = max(res.first, 1);
				if(add == 1)
					res.second = min(res.second, m-2);
				return res;
			}
		};
		vector<vector<pii>> zero(n+1);
		vector<vector<pii>> one(n+1);
		
		auto addRanges = [&](int i, vector<pii>& ranges) {
			for(auto range : ranges) {
				zero[i].push_back(process(range, s[i], 0));
				auto rangeMinus = pair{max(0, range.first-1), range.second-1};
				one[i].push_back(process(rangeMinus, s[i], 1));
				if(range.first == 0 && s[i] == '>' && m%2==1)
					one[i].push_back({m/2, m/2});
			}
		};
		
		zero.back().push_back({0, m-1});
		for(int i = n-1; i >= 0; i--) {
			addRanges(i, zero[i+1]);
			addRanges(i, one[i+1]);
			zero[i] = normalize(zero[i]);
			one[i] = normalize(one[i]);
		}
		string ans = "";
		int curr = 0;
		for(int i = 0; i < n; i++) {
			bool z = inside(zero[i], curr);
			bool o = inside(one[i], curr);
			if(z && o) {
				for(int j = i; j < n; j++)
					ans += "?";
				break;
			}
			else if(z) {
				ans += "0";
				curr = curr*2%m;
			}
			else if(o) {
				ans += "1";
				curr = (curr*2+1)%m;
			}
			else {
				ans = "impossible";
				break;
			}
		}
		cout << ans << "\n";
	}

}