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
	cin >> n;
	vector<ll> pos(n);
	ll least = 0;
	ll greatest = 2e9;
	for(int i = 0; i < n; i++) {
		cin >> pos[i];
		if(i > 0) {
			int b;
			cin >> b;
			ll l = 2*pos[i-1];
			ll r = 2*pos[i];
			if(l > r) {
				swap(l, r);
				b ^= 3;
			}
			ll mid = (l+r)/2;
			if(b == 1)
				least = max(least, mid);
			else 
				greatest = min(greatest, mid);
		}
	}
	if(greatest%2)
		greatest--;
	if(least%2)
		least++;
	greatest/=2;
	least/=2;
	cout << max(0LL, greatest-least+1) << "\n";
}