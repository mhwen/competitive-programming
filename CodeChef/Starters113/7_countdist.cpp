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
constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		priority_queue<ll, vector<ll>, greater<ll>> q;
		ll ways = 1;
		ll largest = 0;
		for(int i = 0; i < n; i++) {
			ll num;
			cin >> num;
			while(!q.empty() && q.top() < num) {
				q.pop();
				ways = ways*2%MOD;
			}
			if(num < largest)
				q.push(num);
			largest = max(largest, num);
			cout << ways << " ";
		}
		cout << "\n";
	}
}