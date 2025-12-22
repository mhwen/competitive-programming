#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> m >> n >> k;
	vector<int> nums(n);
	for(int i = 0; i < n; i++)
		cin >> nums[i];
	vector<int> diffs;
	diffs.push_back(nums[0]-1);
	for(int i = 0; i < n-1; i++)
		diffs.push_back(nums[i+1]-nums[i]-1);
	reverse(all(diffs));
	int Xor = 0;
	for(int start = 0; start < k; start++) {
		for(int i = start; i < sz(diffs); i+=2*k)
			Xor ^= diffs[i];
	}
	if(Xor)
		cout << "Twinkle\n";
	else
		cout << "Nova\n";
}