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
		multiset<int> nums;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			nums.insert(a);
		}
		int moves = 0;
		bool pos = true;
		for(int i = n; i >= 1; i--) {
			if(nums.find(i) != nums.end()) {
				nums.erase(nums.find(i));
			}
			else {
				if(*nums.rbegin() <= i*2) {
					pos = false;
					break;
				}
				else {
					moves++;
					nums.erase(nums.find(*nums.rbegin()));
				}
			}
		}
		if(pos)
			cout << moves << "\n";
		else
			cout << -1 << "\n";
	}
}