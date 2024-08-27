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
	int n;
	cin >> n;
	vector<int> times(n);
	for(int i = 0; i < n; i++) {
		cin >> times[i];
	}
	int direction = 1;
	int pos = 0;
	string ans = "";
	while(true) {
		if(direction == 1) {
			if(pos == n || times[pos] == 0) {
				direction = -1;
				if(pos == 0)
					break;
			}
			else {
				times[pos]--;
				pos++;
				ans += "R";
			}
		}
		else {
			if(pos == 0 || (times[pos-1] == 1 && pos != n && times[pos] > 0)) {
				direction = 1;
			}
			else {
				times[pos-1]--;
				pos--;
				ans += "L";
			}
		}
	}
	cout << ans << "\n";
}