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
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		int pow = 1;
		vector<int> ans;
		while(pow*2 <= k) {
			ans.push_back(pow);
			pow *= 2;
		}
		ans.push_back(k-pow);
		ans.push_back(k+1);
		ans.push_back(k+1);
		ans.push_back(k+2);
		ans.push_back(k+2);
		while(pow <= k)
			pow *= 2;
		while(pow <= n) {
			ans.push_back(pow);
			pow *= 2;
		}
		cout << sz(ans) << "\n";
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
}