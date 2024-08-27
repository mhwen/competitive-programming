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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	ll a, b;
	cin >> n >> a >> b;
	vector<ll> s(n);
	for(int i = 0; i < n; i++) {
		cin >> s[i];
	}
	sort(s.begin(), s.end());
	if(a < 0)
		reverse(s.begin(), s.end());
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		ans += (i+1)*(a*s[i] + b);
	}
	cout << ans << "\n";
}