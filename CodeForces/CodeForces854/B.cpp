#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int inputs;
	cin >> inputs;
	while(inputs-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		vector<int> s(n);
		int ones = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			s[i] = nums[i];
			if(nums[i] == 1) {
				ones++;
			}
		}
		if(1 <= ones && ones < n) {
			cout << "-1\n";
			continue;
		}
		sort(s.begin(), s.end());
		if(s[0] == s[n-1]) {
			cout << "0\n";
			continue;
		}
		vector<pair<int, int>> moves;
		while(true) {
			int largest = 0;
			int index = -1;
			int smallest = 1e9+1;
			for(int i = 0; i < n; i++) {
				// cout << nums[i] << " ";
				if(nums[i] > largest) {
					largest = nums[i];
					index = i;
				}
				if(nums[i] < smallest) {
					smallest = nums[i];
				}
			}
			// cout << "\n";
			if(largest == smallest) {
				break;
			}
			for(int i = 0; i < n; i++) {
				if(nums[i] != largest) {
					nums[index] = (nums[index]+nums[i]-1)/nums[i];
					moves.push_back({index+1, i+1});
					break;
				}
			}
		}
		cout << moves.size() << "\n";
		for(auto m : moves) {
			cout << m.first << " " << m.second << "\n";
		}
		
	}
}