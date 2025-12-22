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
	int n;
	cin >> n;
	vector<ll> s(n);
	vector<ll> c(n);
	for(int i = 0; i < n; i++)
		cin >> s[i];
	for(int i = 0; i < n; i++)
		cin >> c[i];
	
	ll curr = 0;
	int latestBad = -1;
	ll worstBad = 0;
	ll lo = s[0];
	bool good = true;
	for(int i = 0; i < n; i++) {
		if(latestBad == -1)
			lo = min(lo, s[i]);
		curr += s[i]-c[i];
		if(curr < 0) {
			good = false;
			latestBad = i;
			worstBad = min(worstBad, curr);
		}
	}
	for(int i = latestBad+1; i < n; i++) {
		ll gain = s[i]-lo;
		if(gain >= -worstBad)
			good = true;
	}
	if(good)
		cout << "Yes\n";
	else
		cout << "No\n";
}