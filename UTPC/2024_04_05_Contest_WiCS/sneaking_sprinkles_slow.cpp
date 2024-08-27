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
	vector<ll> vals(n);
	for(int i = 0; i < n; i++) {
		cin >> vals[i];
	}
	for(int i = 0; i < n; i++) {
		ll add;
		cin >> add;
		int maxId = 0;
		for(int j = 0; j < n; j++) {
			vals[j] += add;
			if(vals[j] > vals[maxId])
				maxId = j;
		}
		vals[maxId] -= vals[maxId]/2;
	}
	ll sum = 0;
	for(ll l : vals)
		sum += l;
	cout << sum << "\n";
}