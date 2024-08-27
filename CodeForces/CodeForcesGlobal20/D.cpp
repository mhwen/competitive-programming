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
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		vector<int> b(n);
		for(int i = 0; i < n; i++) {
			cin >> b[i];
		}
		stack<pair<int, int>> segments;
		int count = 0;
		int curr = 0;
		for(int i : b) {
			if(i != curr) {
				if(count > 0)
					segments.push({curr, count});
				curr = i;
				count = 1;
			}
			else {
				count++;
			}
		}
		if(count > 0)
			segments.push({curr, count});
		
		vector<int> used(n+1);
		int index = n-1;
		bool pos = true;
		while(!segments.empty()) {
			auto next = segments.top();
			segments.pop();
			while(nums[index] != next.first && used[nums[index]] > 0) {
				used[nums[index]]--;
				index--;
			}
			if(nums[index] != next.first) {
				pos = false;
				break;
			}
			used[nums[index]] += next.second-1;
			index--;
		}
		while(index >= 0) {
			used[nums[index]]--;
			index--;
		}
		for(int i : used) {
			if(i != 0)
				pos = false;
		}
			
		if(pos)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}