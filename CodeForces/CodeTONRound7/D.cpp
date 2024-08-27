#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		set<int> ones;
		vector<int> nums(n);
		int total = 0;
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			total += nums[i];
			if(nums[i] == 1)
				ones.insert(i);
		}
		while(q-->0) {
			int type;
			cin >> type;
			if(type == 1) {
				int wanted;
				cin >> wanted;
				if(ones.empty()) {
					if(wanted%2==0)
						cout << "YES\n";
					else
						cout << "NO\n";
				}
				else {
					int leftOne = *ones.begin();
					int rightOne = *ones.rbegin();
					int forced = min(leftOne, n-1-rightOne);
					int remaining = total-forced*2;
					// cout << remaining << endl;
					if(wanted <= remaining)
						cout << "YES\n";
					else if(wanted <= total && (wanted-remaining)%2 == 0)
						cout << "YES\n";
					else
						cout << "NO\n";
				}
			}
			else {
				int i, v;
				cin >> i >> v;
				i--;
				if(nums[i] == 1)
					ones.erase(i);
				if(v == 1)
					ones.insert(i);
				total += v-nums[i];
				nums[i] = v;
			}
		}
	}
}