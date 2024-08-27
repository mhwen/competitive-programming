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
		map<int, vector<int>> remaining;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			remaining[nums[i]].push_back(i);
		}
		int steps = 0;
		int currIndex = 0;
		for(auto l : remaining) {
			auto indices = l.second;
			int next = 0;
			int sz = (int)indices.size();
			for(int i = 0; i < sz; i++) {
				if(indices[i] >= currIndex) {
					next = i;
					break;
				}
			}
			int nextIndex = indices[next];
			steps += (nextIndex-currIndex+n)%n;
			currIndex = nextIndex;
			if(sz > 1) {
				nextIndex = indices[(next-1+sz)%sz];
				steps += (nextIndex-currIndex+n)%n;
				currIndex = nextIndex;
			}
		}
		cout << steps << "\n";
	}
}