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
		int n, q;
		cin >> n >> q;
		vector<ll> nums(n);
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
		}
		vector<ll> ans(n);
		multiset<ll> below;
		multiset<ll> above;
		ll curr = 0;
		
		auto fix = [&](ll val) {
			curr += val;
			above.insert(val);
			while(sz(above) > sz(below)+1) {
				curr -= 2*(*above.begin());
				below.insert(*above.begin());
				above.erase(above.begin());
			}
			// cout << sz(above) << " " << sz(below) << endl;
			while(sz(below) > 0 && (*below.rbegin()) > (*above.begin())) {
				ll b = *below.rbegin();
				ll a = *above.begin();
				curr -= 2*a;
				curr += 2*b;
				above.erase(above.begin());
				below.erase(--below.end());
				above.insert(b);
				below.insert(a);
			}
			// cout << "added " << val << " answer is " << curr << endl;
		};
		
		fix(nums[0]);
		ans[0] = curr;
		
		for(int i = 1; i < n; i+=2) {
			fix(nums[i]);
			fix(nums[i+1]);
			ans[i+1] = curr;
		}
		while(q-->0) {
			int id;
			cin >> id;
			id--;
			cout << ans[id] << " ";
		}
		cout << "\n";
	}
}