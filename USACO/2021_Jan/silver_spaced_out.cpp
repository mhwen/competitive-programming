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
	vector<vector<int>> nums(n, vector<int>(n));
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			cin >> nums[r][c];
		}
	}
	int ans1 = 0;
	for(int r = 0; r < n; r++) {
		int sum = 0;
		int evenSum = 0;
		for(int c = 0; c < n; c++) {
			sum += nums[r][c];
			if(c%2==0)
				evenSum += nums[r][c];
		}
		ans1 += max(sum-evenSum, evenSum);
	}
	int ans2 = 0;
	for(int c = 0; c < n; c++) {
		int sum = 0;
		int evenSum = 0;
		for(int r = 0; r < n; r++) {
			sum += nums[r][c];
			if(r%2==0)
				evenSum += nums[r][c];
		}
		ans2 += max(sum-evenSum, evenSum);
	}
	cout << max(ans1, ans2) << "\n";
}