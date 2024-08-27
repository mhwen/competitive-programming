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
		string s;
		cin >> s;
		int best = 0;
		for(int i = 0; i < n; i++) {
			int up = 0;
			int down = 0;
			for(int j = i; j < n; j++) {
				if(s[j] == 'U')
					up++;
				else
					down++;
				if(up == down)
					best = max(best, j-i+1);
			}
		}
		cout << best << "\n";
	}
}