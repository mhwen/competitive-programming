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
	int n, m;
	cin >> n >> m;
	vector<ll> heights(n);
	for(int i = 0; i < n; i++) {
		cin >> heights[i];
	}
	for(int i = 0; i < m; i++) {
		ll cane;
		cin >> cane;
		ll eaten = 0;
		for(int j = 0; j < n; j++) {
			if(eaten == cane)
				break;
			ll eat = max(0LL, min(heights[j], cane) - eaten);
			heights[j] += eat;
			eaten += eat;
		}
	}
	for(int i = 0; i < n; i++) {
		cout << heights[i] << "\n";
	}
}