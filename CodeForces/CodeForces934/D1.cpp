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
		int n, k;
		ll MOD;
		cin >> n >> k >> MOD;
		//at index i with left, right vals
		auto sufSum = vector(k+1, vector<ll>(k+1));

		for(int right = 0; right <= k; right++) {
			for(int left = k; left >= 0; left--) {
				if(left <= right)
					sufSum[left][right] = 1;
					
				if(left < k) {
					sufSum[left][right] += sufSum[left+1][right];
					sufSum[left][right] %= MOD;
				}
			}
		}
		for(int i = 1; i < n-1; i++) {
			auto newSufSum = vector(k+1, vector<ll>(k+1));
			for(int right = 0; right <= k; right++) {
				for(int left = k; left >= 0; left--) {
					
					newSufSum[left][right] = sufSum[max(0, left-right)][left];
					if(left < k) {
						newSufSum[left][right] += newSufSum[left+1][right];
						newSufSum[left][right] %= MOD;
					}
				}
			}
			sufSum = newSufSum;
		}
		ll sum = 0;
		for(int right = 0; right <= k; right++) {
			sum += sufSum[right][right];
			sum %= MOD;
		}
		cout << sum << "\n";
	}
}