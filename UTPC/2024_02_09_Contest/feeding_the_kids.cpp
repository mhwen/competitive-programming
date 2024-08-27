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
	ll n, k;
	cin >> n >> k;
	vector<ll> eat(n);
	for(int i = 0; i < (int)n; i++) {
		cin >> eat[i];
	}
	ll left = 1, right = 1e15;
	function<bool(ll)> check = [&](ll cut) {
		ll rem = k-1;
		ll currSlice = cut;
		for(ll d : eat) {
			if(d > cut)
				return false;
			if(d <= currSlice)
				currSlice -= d;
			else {
				if(rem == 0)
					return false;
				rem--;
				currSlice = cut;
				currSlice -= d;
			}
		}
		return true;
	};
	while(left <= right) {
		ll mid = (left+right)/2;
		if(check(mid))
			right = mid-1;
		else
			left = mid+1;
	}
	cout << left << "\n";
}