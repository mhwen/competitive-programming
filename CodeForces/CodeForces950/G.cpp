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

struct Node {
	int count;
	vector<Node*> next;
	Node() : count(0), next(2) {}
	
	Node* get(int id) {
		if(next[id] == nullptr)
			next[id] = new Node();
		return next[id];
	}
};

constexpr int BITS = 30;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		vector<vector<pair<int, int>>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b, w;
			cin >> a >> b >> w;
			a--; b--;
			con[a].push_back({b, w});
			con[b].push_back({a, w});
		}
		vector<Node*> nodes(2);
		nodes[0] = new Node();
		nodes[1] = new Node();
		
		auto update = [&](Node* node, int val, int d) {
			auto curr = node;
			for(int bit = BITS-1; bit >= 0; bit--) {
				int next = ((1<<bit)&val) != 0;
				curr = curr->get(next);
				curr->count += d;
			}
		};
		
		auto query = [&](Node* node, int val) {
			auto curr = node;
			int res = 0;
			for(int bit = BITS-1; bit >= 0; bit--) {
				int next = ((1<<bit)&val) != 0;
				if(curr->get(next^1)->count == 0)
					curr = curr->get(next);
				else {
					res |= (1<<bit);
					curr = curr->get(next^1);
				}
			}
			return res;
		};
		
		vector<int> parities(n);
		vector<int> vals(n);
		
		function<void(int, int, int, int)> dfs = [&](int curr, int prev, int val, int parity) {
			update(nodes[parity], val, 1);
			parities[curr] = parity;
			vals[curr] = val;
			for(auto [next,w]: con[curr]) {
				if(next == prev)
					continue;
				dfs(next, curr, val^w, parity^1);
			}
		};
		dfs(0, -1, 0, 0);
		
		int Xor = 0;
		while(q-->0) {
			char type;
			cin >> type;
			if(type == '^') {
				int y;
				cin >> y;
				Xor ^= y;
			}
			else {
				int v, x;
				cin >> v >> x;
				v--;
				int P = parities[v];
				update(nodes[P], vals[v], -1);
				cout << max(query(nodes[P], vals[v]^x), query(nodes[P^1], vals[v]^x^Xor)) << " ";
				update(nodes[P], vals[v], 1);
			}
		}
		cout << "\n";
		
	}
}