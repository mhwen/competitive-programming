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
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<vector<ll>> nums(2500, vector<ll>(n));
	for(int i = 0; i < n; i++)
		cin >> nums[0][i];
	for(int k = 1; k < 2500; k++) {
		for(int i = 0; i < n; i++) {
			if(i == 0)
				nums[k][i] = nums[k-1][i];
			else
				nums[k][i] = nums[k][i-1]*nums[k-1][i]%MOD;
		}
	}
	while(q-->0) {
		int k, x;
		cin >> k >> x;
		k--; x--;
		cout << nums[k][x] << "\n";
	}
}