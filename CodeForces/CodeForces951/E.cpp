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
		int n, d;
		cin >> n >> d;
		map<pair<int, int>, int> seen;
		map<int, set<pair<int, int>>> pos;
		map<int, set<pair<int, int>>> neg;
		for(int i = 1; i <= n; i++) {
			int x, y;
			cin >> x >> y;
			seen[{x, y}] = i;
			pos[y-x].insert({x, i});
			neg[y+x].insert({x, i}); 
		}
		bool found = false;
		for(auto[p, id] : seen) {
			auto [x, y] = p;
			//top left
			if(seen.count({x-d/2, y+d/2})) {
				int id2 = seen[{x-d/2, y+d/2}];
				//bottom left diagonal
				auto it = neg[y+x-d].lower_bound({x-d, 0});
				if(it != neg[y+x-d].end() && it->first <= x-d/2) {
					cout << id << " " << id2 << " " << it->second << "\n";
					found = true;
					break;
				}
				//top right diagonal
				it = neg[y+x+d].lower_bound({x, 0});
				if(it != neg[y+x+d].end() && it->first <= x+d/2) {
					cout << id << " " << id2 << " " << it->second << "\n";
					found = true;
					break;
				}
			}
			//top right
			if(seen.count({x+d/2, y+d/2})) {
				int id2 = seen[{x+d/2, y+d/2}];
				//top left diagonal
				auto it = pos[y+d-x].lower_bound({x-d/2, 0});
				if(it != pos[y+d-x].end() && it->first <= x) {
					cout << id << " " << id2 << " " << it->second << "\n";
					found = true;
					break;
				}
				//bottom right diagonal
				it = pos[y-(x+d)].lower_bound({x+d/2, 0});
				if(it != pos[y-(x+d)].end() && it->first <= x+d) {
					cout << id << " " << id2 << " " << it->second << "\n";
					found = true;
					break;
				}
			}
		}
		if(!found)
			cout << "0 0 0\n";
	}
}