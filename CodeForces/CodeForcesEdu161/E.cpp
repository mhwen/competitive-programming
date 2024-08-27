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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll x;
		cin >> x;
		vector<int> ans;
		ll used = 1;
		int val = 0;
		while(used*2 <= x) {
			ans.push_back(val++);
			used*=2;
		}
		ll diff = x-used;
		for(int pow = (int)ans.size()-1; pow >= 0; pow--) {
			if(diff&(1LL<<pow))
				ans.push_back(pow);
		}
		cout << ans.size() << "\n";
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
}