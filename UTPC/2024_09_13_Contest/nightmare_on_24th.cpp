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
	int n, m;
	cin >> n >> m;
	vector<ll> guys(n);
	for(int i = 0; i < n; i++) 
		cin >> guys[i];

	vector<ll> q(m);
	for(int i = 0; i < m; i++)
		cin >> q[i];
	vector<int> order(m);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b) {
		return q[a] < q[b];
	});
	
	vector<int> ans(m);
	int left = 0;
	ll sum = 0;
	for(int i : order) {
		ll needed = q[i];
		while(sum < needed && left < n) {
			sum += guys[left];
			left++;
		}
		if(sum >= needed)
			ans[i] = left;
		else
			ans[i] = -1;
	}
	for(int i : ans)
		cout << i << "\n";
}