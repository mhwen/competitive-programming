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
		int n;
		cin >> n;
		stack<pair<ll, int>> s;
		ll time = 0;
		for(int i = 0; i < n; i++) {
			ll amt;
			int val;
			cin >> amt >> val;
			pair<ll, int> toAdd = {amt, val};
			ll remAmt = amt;
			while(!s.empty() && remAmt > 0) {
				auto next = s.top();
				s.pop();
				ll nextAmt = next.first;
				int nextVal = next.second;
				time -= nextAmt;
				if(nextVal == val)
					toAdd.first += nextAmt;
				else {
					ll take = min(nextAmt, remAmt);
					remAmt -= take;
					nextAmt -= take;
					if(nextAmt > 0) {
						s.push({nextAmt, nextVal});
						time += nextAmt;
					}
				}
			}
			s.push(toAdd);
			time += toAdd.first;
			cout << time << " ";
		}
		cout << "\n";
	}
}