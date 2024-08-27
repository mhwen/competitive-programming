#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> con(n);
		vector<int> degree(n);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				char c;
				cin >> c;
				if(c == '1') {
					con[i].push_back(j);
					degree[j]++;
				}
			}
		}
		queue<int> q;
		for(int i = 0; i < n; i++) {
			if(degree[i] == 0)
				q.push(i);
		}
		vector<set<int>> sets(n);
		int counter = 1;
		while(q.size()) {
			int curr = q.front();
			q.pop();
			sets[curr].insert(counter++);
			for(int next : con[curr]) {
				sets[next].insert(sets[curr].begin(), sets[curr].end());
				degree[next]--;
				if(degree[next] == 0)
					q.push(next);	
			}
		}
		for(int i = 0; i < n; i++) {
			cout << sets[i].size();
			for(int num : sets[i])
				cout << " " << num;
			cout << "\n";
		}
	}
}