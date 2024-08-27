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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> a(n);
		vector<ll> b(n);
		vector<pair<ll, int>> totals(n);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		for(int i = 0; i < n; i++) {
			cin >> b[i];
			totals[i] = {a[i]+b[i], i};
		}
		sort(totals.rbegin(), totals.rend());
		ll score = 0;
		for(int i = 0; i < n; i++) {
			if(i%2==0) {
				score += a[totals[i].second]-1;
			}
			else {
				score -= b[totals[i].second]-1;
			}
		}
		cout << score << "\n";
	}
}