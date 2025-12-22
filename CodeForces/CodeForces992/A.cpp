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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		vector<int> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		bool found = false;
		for(int i = 0; i < n; i++) {
			bool bad = false;
			for(int j = 0; j < n; j++) {
				if(i == j)
					continue;
				if(abs(nums[i]-nums[j])%k==0)
					bad = true;
			}
			if(!bad) {
				found = true;
				cout << "YES\n" << i+1 << "\n";
				break;
			}
		}
		if(!found)
			cout << "NO\n";
	}
}