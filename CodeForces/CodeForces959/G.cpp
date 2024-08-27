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
		string want;
		cin >> want;
		reverse(all(want));
		vector<int> wanted(k);
		for(int i = 0; i < k; i++)
			wanted[i] = (want[i] == '0') ? 0 : 1;
		vector<int> a(k);
		for(int i = 0; i < n; i++) {
			string s;
			cin >> s;
			reverse(all(s));
			for(int j = 0; j < k; j++) {
				if(s[j] == '1')
					a[j]++;
			}
		}
		vector<vector<int>> dp(k+1, vector<int>(2*n, -1));
		vector<vector<int>> prevMask(k+1, vector<int>(2*n, -1));
		dp[0][0] = 0;
		prevMask[0][0] = 0;
		for(int i = 0; i < k; i++) {
			for(int mask = 0; mask < 2*n; mask++) {
				if(dp[i][mask] == -1)
					continue;
				int add1 = a[i];
				int add2 = n-add1;
				
				int newMask1 = add1+mask;
				if(newMask1%2==wanted[i]) {
					dp[i+1][newMask1/2] = 0;
					prevMask[i+1][newMask1/2] = mask;
				}
				int newMask2 = add2+mask;
				if(newMask2%2==wanted[i]) {
					dp[i+1][newMask2/2] = 1;
					prevMask[i+1][newMask2/2] = mask;
				}
			}
		}
		if(dp[k][0] == -1)
			cout << -1 << "\n";
		else {
			int currMask = 0;
			int curr = k;
			vector<int> ans;
			while(curr != 0) {
				ans.push_back(dp[curr][currMask]);
				currMask = prevMask[curr][currMask];
				curr--;
			}
			for(int i : ans)
				cout << i;
			cout << "\n";
		}
	}
}