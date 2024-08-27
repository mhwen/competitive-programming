#include <iostream>
#include <vector>

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
		ll nums[2*n];
		ll score = 0;
		for(int i = 0; i < 2*n; i++) {
			cin >> nums[i];
			score += abs(nums[i]);
		}
		if(n == 1) {
			score = min(score, abs(nums[0]-nums[1]));
		}
		if(n == 2) {
			ll newScore = 0;
			for(int i = 0; i < 2*n; i++) {
				newScore += abs(2-nums[i]);
			}
			score = min(score, newScore);
		}
		if(n%2 == 0) {
			ll newScore = 0;
			for(int i = 0; i < 2*n; i++) {
				newScore += abs(-1-nums[i]);
			}
			for(int i = 0; i < 2*n; i++) {
				score = min(score, newScore-abs(-1-nums[i])+abs(n-nums[i]));
			}
		}
		cout << score << "\n";
	}
}