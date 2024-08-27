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
		vector<int> nums(n);
		vector<int> order(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			order[i] = nums[i];
		}
		sort(order.begin(), order.end());
		int id = 0;
		ll steps = 0;
		int nextEat = 0;
		while(nextEat < n) {
			if(nums[id] == order[nextEat]) {
				nextEat++;
				nums[id] = -1;
			}
			id++;
			if(id == n)
				id = 0;
			steps++;
		}
		cout << steps-1 << "\n";
	}
}