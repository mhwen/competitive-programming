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
		vector<ll> nums(n);
		ll sum = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			sum += nums[i];
		}
		if(sum % 2 == 0) {
			cout << "NO\n";
		}
		else {
			vector<int> moves;
			
			queue<int> ones;
			priority_queue<pair<int, int>> others;
			for(int i = 0; i < n; i++) {
				if(nums[i] == 1)
					ones.push(i);
				else if(nums[i] >= 2)
					others.push({nums[i], i});
			}
			bool pos = true;
			while(!ones.empty()) {
				int one = ones.front();
				ones.pop();
				if(others.empty()) {
					if(!ones.empty())
						pos = false;
					break;
				}
				auto other = others.top();
				others.pop();
				moves.push_back(one);
				nums[one]--;
				moves.push_back(other.second);
				nums[other.second]--;
				other.first--;
				if(other.first > 1)
					others.push({other.first, other.second});
				else
					ones.push(other.second);
			}
			
			for(int i = 0; i < n; i++) {
				if(nums[i]%2==1) {
					nums[i]--;
					moves.push_back(i);
				}
			}
			for(int i = 0; i < n; i++) {
				while(nums[i] > 0) {
					nums[i]-=2;
					moves.push_back(i);
					moves.push_back(i);
				}
			}
			
			if(!pos)
				cout << "NO\n";
			else {
				cout << "YES\n";
				for(int i : moves)
					cout << i+1 << " ";
				cout << "\n";
			}
			
		}
	}
	
	// 1 1 1 4

}