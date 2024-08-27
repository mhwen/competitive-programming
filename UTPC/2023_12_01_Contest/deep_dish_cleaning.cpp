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
	int t, n;
	cin >> t >> n;
	vector<bool> wired(t);
	for(int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		for(int j = a; j < b; j++) {
			wired[j] = true;
		}
	}
	int s, p;
	cin >> s >> p;
	s*=2, p*=2;
	
	function<int(int)> check = [&](int start) {
		int used = 0;
		int currS = 0, currP = 0;
		for(int i = 0; i < t; i++) {
			int id = (i+start)%t;
			int neededS = wired[id] ? 1 : 2;
			int neededP = wired[id] ? 1 : 0;
			if(neededS > currS || neededP > currP) {
				currS = s;
				currP = p;
				used++;
			}
			currS -= neededS;
			currP -= neededP;
		}
		return used;
	};
	
	vector<int> ccw(t);
	vector<int> cw(t);
	
	int best = 1e9;
	for(int start = 0; start < t; start++) {
		ccw[start] = check(start);
		best = min(best, ccw[start]);
	}
	reverse(wired.begin(), wired.end());
	for(int start = 0; start < t; start++) {
		cw[start] = check(start);
		best = min(best, cw[start]);
	}

	// for(int i = 0; i < t; i++) {
		// cout << ccw[i] << " ";
	// }
	// cout << endl;
	// for(int i = 0; i < t; i++) {
		// cout << cw[i] << " ";
	// }
	// cout << endl;
	cout << best << "\n";
}