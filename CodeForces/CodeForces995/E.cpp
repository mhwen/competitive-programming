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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		map<int, vector<int>> events;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			events[a].push_back(0);
			events[a+1].push_back(-1);
		}
		for(int i = 0; i < n; i++) {
			int b;
			cin >> b;
			events[b].push_back(0);
			events[b+1].push_back(1);
		}
		ll best = 0;
		ll curr = n;
		int bad = 0;
		for(auto& [e,v] : events) {
			for(auto type : v) {
				if(type == -1) {
					bad++;	
				}
				if(type == 1){
					bad--;
					curr--;
				}
			}
			if(bad <= k)
				best = max(best, curr*e);
		}
		cout << best << "\n";
	}
}