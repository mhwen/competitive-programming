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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		stack<int> curr;
		std::priority_queue<int, std::vector<int>, std::greater<int>> q;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			while(!curr.empty() && curr.top() > a) {
				q.push(curr.top()+1);
				curr.pop();
			}
			curr.push(a);
		}
		while(!curr.empty() && !q.empty() && curr.top() > q.top()) {
			q.push(curr.top()+1);
			curr.pop();
		}
		vector<int> ans;
		while(!curr.empty()) {
			ans.push_back(curr.top());
			curr.pop();
		}
		reverse(all(ans));
		while(!q.empty()) {
			ans.push_back(q.top());
			q.pop();
		}
		for(auto a : ans)
			cout << a << " ";
		cout << "\n";
	}
}