#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<string> needed(n);
	for(int i = 0; i < n; i++) {
		cin >> needed[i];
	}
	map<string, int> degree;
	map<string, vector<string>> edges;
	map<string, ll> costs;
	map<string, ll> buildCost;
	queue<string> q;
	for(int i = 0; i < m; i++) {
		string s;
		ll cost;
		int count;
		cin >> s >> cost >> count;
		degree[s] = count;
		costs[s] = cost;
		if(count == 0)
			q.push(s);
		for(int j = 0; j < count; j++) {
			string ingredient;
			cin >> ingredient;
			edges[ingredient].push_back(s);
		}
	}
	while(!q.empty()) {
		string curr = q.front();
		q.pop();
		for(string next : edges[curr]) {
			buildCost[next] += costs[curr];
			degree[next]--;
			if(degree[next] == 0) {
				costs[next] = min(costs[next], buildCost[next]);
				q.push(next);
			}
		}
	}
	ll ans = 0;
	for(string s : needed)
		ans += costs[s];
	cout << ans << "\n";
	
}