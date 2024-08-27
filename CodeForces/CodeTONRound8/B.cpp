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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<bool> seen(n+1);
		int mex = 0;
		vector<int> ans;
		for(int i = 0; i < n; i++) {
			while(seen[mex])
				mex++;
			int val;
			cin >> val;
			int x = mex-val;
			if(x < 0 || seen[x]) {
				x = mex;
			}
			seen[x] = true;
			ans.push_back(x);
		}
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
}