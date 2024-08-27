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

ll solve(vector<ll>& heights) {
	int n = (int)heights.size();
	vector<ll> preMax(n);
	vector<ll> sufMax(n);
	preMax[0] = heights[0];
	sufMax[n-1] = heights[n-1];
	for(int i = 1; i < n; i++)
		preMax[i] = max(preMax[i-1], heights[i]);
	for(int i = n-2; i >= 0; i--)
		sufMax[i] = max(sufMax[i+1], heights[i]);
	
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		ans += min(preMax[i], sufMax[i])-heights[i];
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<ll> heights(n);
	for(int i = 0; i < n; i++) {
		cin >> heights[i];
	}
	while(q-->0) {
		int p;
		ll add;
		cin >> p >> add;
		p--;
		heights[p] += add;
		cout << solve(heights) << "\n";
	}
}