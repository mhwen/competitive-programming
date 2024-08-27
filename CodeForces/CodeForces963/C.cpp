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
		vector<int> time(2*k+1);
		vector<int> a(n);
		
		function<void(int, int)> mark = [&](int l, int r) {
			if(r >= 2*k) {
				mark(l, 2*k-1);
				mark(0, r%(2*k));
				return;
			}
			time[l]++;
			time[r+1]--;
		};
		
		for(int i = 0; i < n; i++) {
			cin >> a[i];
			int start = a[i]%(2*k);
			int end = start+k-1;
			mark(start, end);
		}
		for(int i = 1; i < sz(time); i++)
			time[i] += time[i-1];
		int m = *max_element(all(a));
		int start = m%(2*k);
		int ans = -1;
		for(int i = 0; i < k; i++) {
			if(time[(start+i)%(2*k)] == n) {
				ans = m+i;
				break;
			}
		}
		cout << ans << "\n";
	}
}