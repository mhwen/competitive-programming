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

constexpr int INF = 1e9;

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	string s, t;
	cin >> s >> t;
	
	vector<int> best(4, INF);
	best[0] = 0;
	
	bool bad = false;
	for(int i = 0; i < n; i++) {
		int a = s[i]-'a';
		int b = t[i]-'a';
		vector<int> newBest(4, INF);
		
		auto tryMask = [&](int mask) {
			for(int prevMask = 0; prevMask < 4; prevMask++) {
				int cost = 0;
				if((prevMask&1) == 0 && (mask&1)==1)
					cost++;
				if((prevMask&2) == 0 && (mask&2)==2)
					cost++;
				newBest[mask] = min(newBest[mask], cost+best[prevMask]);
			}
		};
		
		if(s[i] == 'g' || s[i] == 't') {
			if(b == 25-a) {
				tryMask(1);
				tryMask(2);
			}
			else if(a == b) {
				tryMask(0);
				tryMask(3);
			}
			else
				bad = true;
		}
		else {
			int mask = 0;
			if(b == a)
				mask = 0;
			else if(b == (a+13)%26)
				mask = 1;
			else if(b == 25-a)
				mask = 2;
			else if(b == 25-((a+13)%26))
				mask = 3;
			else
				bad = true;
			tryMask(mask);
		}
		best = newBest;
	}
	if(bad)
		cout << -1 << "\n";
	else
		cout << *min_element(all(best)) << "\n";
	
	
}