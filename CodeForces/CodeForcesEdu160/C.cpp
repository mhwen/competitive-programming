#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int m;
	cin >> m;
	vector<int> counts(32);
	while(m-->0) {
		int t, v;
		cin >> t >> v;
		if(t==1) {
			counts[v]++;
		}
		else {
			ll extra = 0;
			ll pow = 1;
			bool good = true;
			for(int i = 0; i < (int)counts.size(); i++) {
				extra += pow*counts[i];
				if(v&(1<<i)) {
					if(extra < pow) {
						good = false;
						break;
					}
					extra -= pow;
				}
				pow *= 2;
			}
			if(good)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
}