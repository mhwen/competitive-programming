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
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> con(n);
		for(int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		vector<int> colors(n);
		bool good = true;
		function<void(int, int)> dfs = [&](int curr, int c) {
			colors[curr] = c;
			for(int next : con[curr]) {
				if(colors[next] == 0)
					dfs(next, c^3);
				else if(colors[next] == c)
					good = false;
			}
		};
		dfs(0, 1);
		if(good) {
			cout << "Bob" << endl;
			vector<vector<int>> rem(3);
			for(int i = 0; i < n; i++) {
				rem[colors[i]].push_back(i+1);
			}
			for(int i = 0; i < n; i++) {
				int A, B;
				cin >> A >> B;
				if(A > B)
					swap(A, B);
				if(rem[2].empty()) {
					cout << rem[1].back() << " ";
					rem[1].pop_back();
					if(A == 1)
						cout << 1 << endl;
					else
						cout << 3 << endl;
				}
				else if(rem[1].empty()) {
					cout << rem[2].back() << " ";
					rem[2].pop_back();
					if(A == 1)
						cout << B << endl;
					else
						cout << 2 << endl;
				}
				else {
					cout << rem[A].back() << " " << A << endl;
					rem[A].pop_back();
				}
			}
		}
		else {
			cout << "Alice" << endl;
			for(int i = 0; i < n; i++) {
				cout << "1 2" << endl;
				int I, C;
				cin >> I >> C;
			}
		}
	}
}