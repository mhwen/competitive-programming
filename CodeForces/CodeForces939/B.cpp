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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> cnt(n);
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			a--;
			cnt[a]++;
		}
		int me = 0;
		int them = 0;
		int single = 0;
		for(int i = 0; i < n; i++) {
			if(cnt[i] == 0)
				them++;
			else if(cnt[i] == 1)
				single++;
			else
				me++;
		}
		if(me > them)
			cout << me+single << "\n";
		else
			cout << me << "\n";
	}
}