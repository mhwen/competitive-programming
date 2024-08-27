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

constexpr ll INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<ll> nums(n);
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	while(q-->0) {
		int l, r;
		cin >> l >> r;
		l--; r--;
		if(r-l > 200)
			cout << "YES\n";
		else {
			vector<ll> vals;
			for(int i = l; i <= r; i++)
				vals.push_back(nums[i]);
			sort(all(vals));
			int good = 0;
			//AAABBB
			for(int i = 0; i < sz(vals)-2; i++) {
				if(vals[i]+vals[i+1] > vals[i+2]) {
					good++;
					i += 2;
				}
			}
			if(good > 1)
				cout << "YES\n";
			else {
				pair<ll, ll> greatest{-INF, -INF};
				//AABB
				bool found = false;
				for(int i = 0; i < sz(vals)-3; i++) {
					if(i > 0) {
						if(vals[i-1] > greatest.second)
							greatest.second = vals[i-1];
						if(greatest.first < greatest.second)
							swap(greatest.first, greatest.second);
					}
					ll N1 = vals[i+1]-vals[i];
					ll N2 = vals[i+3]-vals[i+2];
					if(N1 < N2)
						swap(N1, N2);
					if(greatest.first > N1 && greatest.second > N2) {
						found = true;
						break;
					}
				}
				//AAB
				if(found)
					cout << "YES\n";
				else {
					multiset<ll> seen;
					for(int i = 0; i < sz(vals)-2; i++) {
						if(i > 0)
							seen.insert(vals[i-1]);
						ll aNeeded = vals[i+1]-vals[i];
						ll B = vals[i+2];
						if(sz(seen) >= 3) {
							auto it = seen.upper_bound(aNeeded);
							if(it != seen.end()) {
								ll aTake = *it;
								seen.erase(it);
								ll B1 = *seen.rbegin();
								seen.erase(seen.find(B1));
								ll B2 = *seen.rbegin();
								if(B1+B2 > B) {
									found = true;
									break;
								}
								seen.insert(aTake);
								seen.insert(B1);
							}
						}
					}
					if(found)
						cout << "YES\n";
					else
						cout << "NO\n";
				}
			}
		}
	}
}