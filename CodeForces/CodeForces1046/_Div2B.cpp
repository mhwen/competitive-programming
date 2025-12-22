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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		string s;
		cin >> s;
		int cnt = 0;
		bool bad = false;
		vector<int> ans(n);
		int lo = 1, hi = n;
		for(int i = 0; i < n; i++) {
			if(s[i] == '1') {
				ans[i] = lo++;
				cnt++;
			}
			else
				ans[i] = hi--;
			if(i >= k && s[i-k] == '1')
				cnt--;
			if(cnt == k)
				bad = true;
		}
		if(bad)
			cout << "NO\n";
		else {
			cout << "YES\n";
			for(int a : ans)
				cout << a << " ";
			cout << "\n";
		}
	}
}