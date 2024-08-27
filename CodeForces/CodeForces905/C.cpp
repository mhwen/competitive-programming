#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		int q;
		cin >> q;
		int index = 0;
		vector<pair<pair<int, int>, ll>> updates(q);
		map<int, ll> vals;
		for(int i = 0; i < q; i++) {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			l--; r--;
			updates[i] = {{l, r}, x};
			vals[l] += x;
			if(vals[l] == 0)
				vals.erase(l);
			vals[r+1] -= x;
			if(vals[r+1] == 0)
				vals.erase(r+1);
			if(!vals.empty() && vals.begin()->second < 0) {
				index = i+1;
				vals.clear();
			}
		}
		vector<ll> added(n+1);
		for(int i = 0; i < index; i++) {
			int l = updates[i].first.first;
			int r = updates[i].first.second;
			ll x = updates[i].second;
			added[l] += x;
			added[r+1] -= x;
		}
		for(int i = 1; i < (int)added.size(); i++) {
			added[i] += added[i-1];
		}
		for(int i = 0; i < n; i++) {
			cout << nums[i]+added[i] << " ";
		}
		cout << "\n";
	}
}