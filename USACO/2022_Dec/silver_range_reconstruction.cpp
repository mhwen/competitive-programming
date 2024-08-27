#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<vector<int>> ranges(n, vector<int>(n));
	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			cin >> ranges[i][j];
		}
	}
	vector<int> ans(n);
	ans[0] = 0;
	for(int i = 1; i < n; i++) {
		int pos1 = ans[i-1]+ranges[i-1][i];
		int pos2 = ans[i-1]-ranges[i-1][i];
		int currMax = pos1;
		int currMin = pos1;
		bool good = true;
		for(int j = i-1; j >= 0; j--) {
			currMax = max(currMax, ans[j]);
			currMin = min(currMin, ans[j]);
			if(currMax-currMin != ranges[j][i])
				good = false;
		}
		if(good)
			ans[i] = pos1;
		else
			ans[i] = pos2;
	}
	for(int i = 0; i < n; i++) {
		cout << ans[i];
		if(i != n-1)
			cout << " ";
	}
	cout << "\n";
}