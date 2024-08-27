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
	int n, q;
	cin >> n >> q;
	vector<ll> heights(n);
	for(int i = 0; i < n; i++) {
		cin >> heights[i];
	}
	while(q-->0) {
		int i, j;
		cin >> i >> j;
		i--; j--;
		if(i > j)
			swap(i, j);
		string ans = "yes";
		for(int h = i+1; h < j-1; h++) {
			if(heights[h] >= max(heights[i], heights[j])) {
				ans = "no";
				break;
			}
		}
		cout << ans << "\n";
	}
}