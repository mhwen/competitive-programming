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
		int n, q;
		cin >> n >> q;
		vector<int> sums(n+1);
		for(int i = 0; i < n; i++) {
			int num;
			cin >> num;
			sums[num]++;
		}
		for(int i = 1; i < sz(sums); i++)
			sums[i] += sums[i-1];
		
		vector<int> ans(n+1);
		
		for(int i = 1; i <= n; i++) {
			auto check = [&](int val) {
				int count = 0;
				for(int j = 0; j <= n; j+=i) {
					count += sums[min(n, j+val)];
					if(j > 0)
						count -= sums[j-1];
				}
				return count;
			};
			int left = 0, right = i-1;
			while(left <= right) {
				int mid = (left+right)/2;
				if(check(mid) > n/2)
					right = mid-1;
				else
					left = mid+1;
			}
			ans[i] = left;
		}
		while(q-->0) {
			int x;
			cin >> x;
			cout << ans[x] << " ";
		}
		cout << "\n";
	}
}