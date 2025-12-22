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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		
		vector<int> ans(n);
		int curr = 1;
		for(int i = k-1; i < n; i+=k)
			ans[i] = curr++;
		for(int i = 0; i < n; i++)
			if(ans[i] == 0)
				ans[i] = curr++;
				
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
}