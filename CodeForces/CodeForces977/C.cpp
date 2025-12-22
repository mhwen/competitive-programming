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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, q;
		cin >> n >> m >> q;
		vector<int> a(n);
		map<int, int> position;
		for(int i = 1; i <= n; i++) {
			cin >> a[i-1];
			position[a[i-1]] = i;
		}
		map<int, set<int>> need;
		vector<int> b(m);
		for(int i = 1; i <= n; i++) {
			need[i].insert(INF);
		}
		for(int i = 0; i < m; i++) {
			cin >> b[i];
			need[b[i]].insert(i);
		}
		vector<int> earliest(n+1);
		earliest[0] = -1;
		int good = 0;
		for(int i = 1; i <= n; i++) {
			earliest[i] = *need[a[i-1]].begin();
			if(earliest[i] >= earliest[i-1])
				good++;
		}
		
		auto output = [&]() {
			if(good == n)
				cout << "YA\n";
			else
				cout << "TIDAK\n";
		};
		
		auto incr = [&](int pos) {
			int amt = 0;
			if(earliest[pos] >= earliest[pos-1])
				amt++;
			if(pos < n && earliest[pos+1] >= earliest[pos])
				amt++;
			return amt;
		};
		
		auto update = [&](int guy) {
			int pos = position[guy];
			good -= incr(pos);
			earliest[pos] = *need[guy].begin();
			good += incr(pos);
		};
		
		output();
		while(q-->0) {
			int pos, guy;
			cin >> pos >> guy;
			pos--;
			need[b[pos]].erase(pos);
			update(b[pos]);
			b[pos] = guy;
			need[b[pos]].insert(pos);
			update(b[pos]);
			output();
		}
	}
}