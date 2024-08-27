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
		ll sum = 0;
		vector<ll> heights(n);
		for(int i = 0; i < n; i++) {
			cin >> heights[i];
		}
		for(int i = 1; i < n-1; i+=2) {
			sum += max(0LL, max(heights[i-1]-heights[i]+1, heights[i+1]-heights[i]+1));
		}
		if(n%2) {
			cout << sum << "\n";
		}
		else {
			ll best = sum;
			for(int i = n-2; i >= 2; i-=2) {
				sum += max(0LL, max(heights[i-1]-heights[i]+1, heights[i+1]-heights[i]+1));
				sum -= max(0LL, max(heights[i-2]-heights[i-1]+1, heights[i]-heights[i-1]+1));
				best = min(best, sum);
			}
			cout << best << "\n";
		}
		
	}
}