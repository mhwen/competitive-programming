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
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	string s;
	cin >> n >> s;
	ll ans = 0;
	vector<int> nums(n);
	function<void(int)> recur = [&](int curr) {
		if(curr == n) {
			for(int i = 0; i < n; i++) {
				for(int j = i; j < n; j++) {
					bool good = false;
					for(int num = 1; num <= 3; num++) {
						int count = 0;
						for(int k = i; k <= j; k++) {
							if(nums[k] == num)
								count++;
						}
						if(count >= j-i+1-count)
							good = true;
					}
					if(!good)
						return;
				}
			}
			// for(int i : nums)
				// cout << i << " ";
			// cout << endl;
			ans++;
			return;
		}
		for(int i = 1; i <= 3; i++) {
			nums[curr] = i;
			recur(curr+1);
		}
	};
	recur(0);
	cout << ans << "\n";
}