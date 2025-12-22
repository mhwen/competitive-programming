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
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
			
		int val = *max_element(all(nums));
		while(m-->0) {
			char c;
			int l, r;
			cin >> c >> l >> r;
			if(l <= val && val <= r) {
				if(c == '+')
					val++;
				else
					val--;
			}
			cout << val << " ";
		}
		cout << "\n";
	}
}