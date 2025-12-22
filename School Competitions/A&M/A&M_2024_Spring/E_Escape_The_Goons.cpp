#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;
constexpr int INF = 2e9+5;

bool intersect(int a, int b, int c, int d) {
	if(b < c)
		return false;
	if(d < a)
		return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, X, Y;
	cin >> n >> X >> Y;
	map<int, vector<int>> points;
	for(int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		points[x].push_back(y);
	}
	map<int, vector<pair<pair<int, int>, int>>> columns;
	int id = 0;
	vector<bool> escape(1e6);
	for(auto p : points) {
		int x = p.first;
		auto coords = p.second;
		sort(coords.begin(), coords.end());
		
		escape[id] = true;
		columns[x].push_back({{-INF, coords.front()-1}, id++});
		
		for(int i = 0; i+1 < (int)coords.size(); i++) {
			if(coords[i]+1 != coords[i+1])
				columns[x].push_back({{coords[i]+1, coords[i+1]-1}, id++});
		}
		escape[id] = true;
		columns[x].push_back({{coords.back()+1, INF}, id++});
	}
	vector<vector<int>> con(id+5);
	for(auto col : columns) {
		int x = col.first;
		auto cols = col.second;
		// cout << x << endl;
		// for(auto c : cols)
			// cout << c.first.first << " " << c.first.second << " " << c.second << endl;
		
		if(columns.count(x-1) == 0 || columns.count(x+1) == 0) {
			for(auto c : cols) {
				escape[c.second] = true;
			}
		}
		if(columns.count(x+1) != 0) {
			auto nextCols = columns[x+1];
			int me = 0, them = 0;
			while(me < (int)cols.size() && them < (int)nextCols.size()) {
				auto myCol = cols[me];
				auto theirCol = nextCols[them];
				if(intersect(myCol.first.first, myCol.first.second, theirCol.first.first, theirCol.first.second)) {
					con[myCol.second].push_back(theirCol.second);
					con[theirCol.second].push_back(myCol.second);
				}
				if(myCol.first.second < theirCol.first.second)
					me++;
				else
					them++;
			}
		}
	}
	
	if(columns.count(X) == 0) {
		cout << "NOT CONTAINED\n";
	}
	else {
		queue<int> q;
		for(auto col : columns[X]) {
			int bot = col.first.first;
			int top = col.first.second;
			if(bot <= Y && Y <= top)
				q.push(col.second);
		}
		bool found = false;
		vector<int> vis(id+5);
		while(!q.empty()) {
			int curr = q.front();
			// cout << curr << endl;
			q.pop();
			if(vis[curr])
				continue;
			vis[curr] = true;
			if(escape[curr]) {
				found = true;
				break;
			}
			for(int next : con[curr])
				if(!vis[next])
					q.push(next);
		}
		if(found)
			cout << "NOT CONTAINED\n";
		else
			cout << "CONTAINED\n";
	}
	
	
}