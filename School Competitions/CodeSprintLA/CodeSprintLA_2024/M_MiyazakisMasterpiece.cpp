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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, L;
	cin >> n >> m >> L;
	string s;
	cin >> s;
	vector<string> fans(m);
	for(int i = 0; i < m; i++)
		cin >> fans[i];
	if(L <= 2) {
		cout << m << "\n";
		return 0;
	}
	else if(L == 3) {
		set<char> left;
		set<char> right;
		set<char> mid;
		for(int i = 0; i < n; i++) {
			if(i > 1)
				right.insert(s[i]);
			if(i < n-2)
				left.insert(s[i]);
			if(i > 0 && i < n-1)
				mid.insert(s[i]);
		}
		int ans = 0;
		for(string f : fans) {
			if(left.count(f[0]) || mid.count(f[1]) || right.count(f[2]))
				ans++;
		}
		cout << ans << "\n";
	}
	else {
		vector<map<pair<char, char>, vector<int>>> starts(6);
		vector<pair<int, int>> checks = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
		for(int j = 0; j < 6; j++) {
			int l = checks[j].first;
			int r = checks[j].second;
			for(int i = 0; i+r < n; i++) {
				char a = s[i+l];
				char b = s[i+r];
				starts[j][{a, b}].push_back(i);
				// cout << "added " << "{" << l << "," << r << "}" << " {" << a << "," << b << "}: " << i << endl;
			}
		}
		auto check = [&](int start, string& fan) {
			// cout << "checking " << start << " " << fan << endl;
			if(start+sz(fan) > n)
				return false;
			int bad = 0;
			for(int i = 0; i < sz(fan); i++) {
				if(fan[i] != s[i+start])
					bad++;
				if(bad > 2)
					return false;
			}
			return true;
		};
		
		int ans = 0;
		for(string& f : fans) {
			// cout << "at " << f << endl;
			bool found = false;
			for(int i = 0; i < 6; i++) {
				int l = checks[i].first;
				int r = checks[i].second;
				// cout << "on " << "{" << l << "," << r << "}" << " {" << f[l] << "," << f[r] << "}" << endl;
				for(int start : starts[i][{f[l], f[r]}]) {
					if(check(start, f)) {
						ans++;
						found = true;
						break;
					}
				}
				if(found)
					break;
			}
		}
		cout << ans << "\n";
	}
}