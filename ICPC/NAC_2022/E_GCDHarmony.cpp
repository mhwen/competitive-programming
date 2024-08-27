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
constexpr ll INF = 1e9;

vector<int> nums;
vector<int> sieve(10005, -1);

void precomp() {
	for(int i = 2; i < sz(sieve); i++) {
		if(sieve[i] == -1) {
			for(int j = i; j < sz(sieve); j+=i)
				sieve[j] = i;
		}
	}
	for(int i = 2; i <= 10000; i++) {
		bool good = true;
		for(int j = 2; j < i; j++) {
			if(i%(j*j) == 0) {
				good = false;
				break;
			}
		}
		if(sieve[i] > 100)
			good = false;
		if(good) {
			nums.push_back(i);
		}
	}
}


//11:20
//11:53

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	precomp();
	int n;
	cin >> n;
	vector<int> vals(n);
	for(int i = 0; i < n; i++)
		cin >> vals[i];
	vector<vector<int>> con(n);
	for(int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		con[a].push_back(b);
		con[b].push_back(a);
	}
	vector<vector<ll>> cost(n, vector<ll>(101, INF));
	
	function<void(int, int)> dfs = [&](int curr, int prev) {
		for(int next : con[curr]) {
			if(next != prev)
				dfs(next, curr);
		}
		for(int candidate : nums) {
			ll myCost = (vals[curr]%candidate == 0) ? 0 : candidate;
			for(int child : con[curr]) {
				if(child == prev)
					continue;
				int hold = candidate;
				ll bestChildCost = INF;
				while(hold > 1) {
					bestChildCost = min(bestChildCost, cost[child][sieve[hold]]);
					hold /= sieve[hold];
				}
				myCost += bestChildCost;
			}
			for(int i = 2; i <= 100; i++) {
				if(candidate%i==0)
					cost[curr][i] = min(cost[curr][i], myCost);
			}
		}
	};
	
	dfs(0, 0);
	ll ans = INF;

	for(int i = 2; i <= 100; i++) {
		ans = min(ans, cost[0][i]);
	}
	cout << ans << "\n";
}