#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;

typedef long long ll;

bool check(vector<pair<int, int>>& ops, int n) {
	map<pair<int, int>, int> f;
	vector<int> vals(n);
	iota(vals.begin(), vals.end(), 1);
	int id = n+1;
	for(auto op : ops) {
		int a = vals[op.first-1];
		int b = vals[op.second-1];
		if(!f.count({a, b}))
			f[{a, b}] = id++;
		vals[op.first-1] = f[{a, b}];
		vals[op.second-1] = f[{a, b}];
	}
	set<int> res;
	for(int i : vals)
		res.insert(i);
	return (int)res.size() <= 2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<int>> pows(20);
	vector<pair<int, int>> ops;
	int highest = 0;
	for(int i = 1; i <= n; i++) {
		int p = 0;
		vector<int> curr = {i};
		while(!pows[p].empty()) {
			int sz = (int)curr.size();
			for(int j = 0; j < sz; j++) {
				ops.emplace_back(pows[p][j], curr[j]);
				curr.push_back(pows[p][j]);
			}
			pows[p].clear();
			p++;
		}
		pows[p] = curr;
		highest = max(highest, p);
	}
	vector<int> prev;
	prev.push_back(pows[highest].back());
	pows[highest].pop_back();
	for(int i = 0; i < highest; i++) {
		int sz = (int)prev.size();
		if(pows[i].empty()) {
			for(int j = 0; j < sz; j++) {
				ops.emplace_back(prev[j], pows[highest].back());
				prev.push_back(pows[highest].back());
				pows[highest].pop_back();
			}
		}
		else {
			for(int j = 0; j < sz; j++) {
				ops.emplace_back(prev[j], pows[i][j]);
				prev.push_back(pows[i][j]);
			}
		}
	}
	cout << ops.size() << "\n";
	for(auto op : ops)
		cout << op.first << " " << op.second << "\n";
	if(!check(ops, n))
		return -1;
}