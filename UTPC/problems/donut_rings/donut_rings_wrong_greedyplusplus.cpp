#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr ll INF = 5e18;
constexpr int SEARCH = 50;
constexpr int START_CHECKS = 50;

ll calcArea(ll inner, ll outer) {
	return outer*outer-inner*inner;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<pair<ll, ll>> donuts(n);
	for(int i = 0; i < n; i++) {
		ll l, r;
		cin >> l >> r;
		donuts[i] = {r, l};
	}
	sort(donuts.begin(), donuts.end());
	
	ll bestAns = -INF;
	
	for(int start = 0; start < min(n, START_CHECKS); start++) {
		ll radius = donuts[start].first;
		ll ans = calcArea(donuts[start].second, donuts[start].first)-calcArea(0, donuts[start].second);
		
		int checked = 0;
		ll bestAdd = 0;
		ll bestR = -1;
		int bestId = -1;
		for(int i = start; i < n; i++) {
			if(radius <= donuts[i].second) {
				checked++;
				ll area = calcArea(donuts[i].second, donuts[i].first);
				ll addAmnt = area-calcArea(radius, donuts[i].second);
				if(addAmnt > bestAdd && (bestId == -1 || bestR > donuts[i].second)) {
					bestAdd = addAmnt;
					bestR = donuts[i].first;
					bestId = i;
				}
			}
			if((checked >= SEARCH || i == n-1) && bestId != -1) {
				ans += bestAdd;
				radius = bestR;
				i = bestId;
				checked = 0;
				bestAdd = 0;
				bestR = -1;
				bestId = -1;
			}
		}
		bestAns = max(bestAns, ans);
	}
	
	cout << bestAns << "\n";
}