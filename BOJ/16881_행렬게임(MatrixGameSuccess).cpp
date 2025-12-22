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

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	int ans = 0;
	for(int i = 0; i < n; i++) {
		vector<int> nums(m);
		for(int j = 0; j < m; j++) {
			cin >> nums[j];
		}
		int prev = 0;
		for(int j = m-1; j>=0; j--) {
			if(nums[j] > prev)
				prev = nums[j];
			else
				prev = nums[j]-1;
		}
		ans ^= prev;
	}
	if(ans)
		cout << "koosaga\n";
	else
		cout << "cubelover\n";
}