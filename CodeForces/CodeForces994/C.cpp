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

void check(vector<int> nums, int x, int y) {
	int n = sz(nums);
	for(int i = 0; i < n; i++) {
		set<int> adj;
		adj.insert(nums[(i+1)%n]);
		adj.insert(nums[(i+n-1)%n]);
		if(i == x || i == y)
			adj.insert(nums[x+y-i]);
		for(int j = 0; j < 3; j++) {
			if(!adj.count(j)) {
				assert(nums[i] == j);
				break;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, x, y;
		cin >> n >> x >> y;
		x--; y--;
		vector<int> ans(n);
		ans[x] = 0;
		ans[y] = 1;
		for(int i = 1; x+i < y; i++) {
			ans[x+i] = i%2;
			if(x+i+1 == y && ans[x+i] == ans[y])
				ans[x+i] = 2;
		}
		for(int i = 1; y+i < x+n; i++) {
			ans[(y+i)%n] = (i-1)%2;
			if((y+i+1)%n == x && ans[(y+i)%n] == ans[x])
				ans[(y+i)%n] = 2;
		}
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
		check(ans, x, y);
	}
}