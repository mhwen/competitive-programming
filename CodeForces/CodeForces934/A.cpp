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
		vector<int> counts(n+1);
		for(int i = 0; i < n; i++) {
			int num;
			cin >> num;
			counts[num]++;
		}
		vector<bool> mine(n+1);
		bool singleTaken = false;
		for(int i = 0; i <= n; i++) {
			if(counts[i] >= 2)
				mine[i] = true;
			if(counts[i] == 1 && !singleTaken) {
				mine[i] = true;
				singleTaken = true;
			}
		}
		int ans = 0;
		for(int i = 0; i <= n; i++) {
			if(!mine[i]) {
				ans = i;
				break;
			}
		}
		cout << ans << "\n";
		
	}
}