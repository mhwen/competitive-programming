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
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		ll curr = 2;
		while(true) {
			set<ll> seen;
			for(int i = 0; i < n; i++) {
				seen.insert(nums[i]%curr);
			}
			if((int)seen.size() == 2)
				break;
			curr *= 2;
		}
		cout << curr << "\n";
	}
}