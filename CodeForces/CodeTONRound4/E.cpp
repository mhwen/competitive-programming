#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> nodes(n);
		for(int i = 0; i < n; i++) {
			cin >> nodes[i];
		}
	
		vector<vector<int>> con(n, vector<int>());
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		
		
		vector<int> size(n);
		vector<int> component(n);
		vector<vector<int>> remaining(n, vector<int>());
		for(int i = 0; i < n; i++) {
			component[i] = i;
			size[i] = 1;
		}
		
		function<int(int)> get_component = [&](int a) {
			if(component[a] != a) {
				return component[a] = get_component(component[a]);
			}
			return component[a];
		};
		
		function<void(int, int)> merge = [&](int a, int b) {
			a = get_component(a);
			b = get_component(b);
			if(a != b) {
				// if(size[a] < size[b])
					// swap(a, b);
				component[b] = a;
				size[a] += size[b];
			}
		};
	
		function<void(int)> search = [&](int start) {
			priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
			for(int next : con[start]) {
				queue.push({nodes[next], next});
			}
			while(!queue.empty()) {
				auto node = queue.top();
				queue.pop();
				int weight = node.first;
				int curr = node.second;
				if(get_component(curr) == get_component(start))
					continue;
				
				if(weight <= size[get_component(start)]) {
					int curr_component = get_component(curr);
					for(int next : remaining[curr_component]) {
						if(get_component(next) != get_component(start)) {
							queue.push({nodes[next], next});
						}
					}
					merge(start, curr);
					for(int next : con[curr]) {
						if(get_component(next) != get_component(start)) {
							queue.push({nodes[next], next});
						}
					}
				}
				else {
					remaining[start].push_back(curr);
				}
			}
		};
		
		for(int i = 0; i < n; i++) {
			if(nodes[i] == 0 && component[i] == i) {
				search(i);
			}
		}
		bool good = false;
		for(int i : size) {
			if(i == n)
				good = true;
		}
		cout << (good ? "YES" : "NO") << "\n";
	}
	
}