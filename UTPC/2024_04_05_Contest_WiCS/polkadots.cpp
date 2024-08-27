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
	int ans = n;
	bool found = false;
	while(!found) {
		for(int j = 2; j < ans; j++) {
			if(ans%j == 0)
				found = true;
		}
		ans++;
	}
	cout << ans-1 << "\n";
}