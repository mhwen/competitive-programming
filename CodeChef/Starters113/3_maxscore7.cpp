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
		int n;
		cin >> n;
		vector<int> evens;
		vector<int> odds;
		for(int i = 0; i < n; i++) {
			int num;
			cin >> num;
			if(i%2==0)
				evens.push_back(num);
			else
				odds.push_back(num);
		}
		sort(evens.begin(), evens.end());
		sort(odds.rbegin(), odds.rend());
		int ans = 0;
		for(int i = 0; i < n/2; i++) {
			ans += abs(evens[i]-odds[i]);
		}
		cout << ans << "\n";
	}
}