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
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> p(2*n);
		ll sum = 0;
		for(int i = 0; i < n; i++) {
			cin >> p[i];
			p[i+n] = p[i];
			sum += p[i];
		}
		int r = 1;
		ll left = 0;
		ll right = sum-p[0]-p[1];
		ll best = 0;
		for(int i = 0; i < n; i++) {
			while(r+1 < i+n) {
				ll newLeft = left+p[r];
				ll newRight = right-p[r+1];
				if(max(left, right) >= max(newLeft, newRight)) {
					r++;
					left = newLeft;
					right = newRight;
				}
				else
					break;
			}
			best = max(best, p[i]+max(left, right));
			left -= p[i+1];
			right += p[i];
		}
		cout << best << "\n";
	}
}