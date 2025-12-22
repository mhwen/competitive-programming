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
	int n, k;
	cin >> n >> k;
	k--;
	vector<map<int, int>> a(n);
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for(char c : s) {
			if(c == 'D')
				a[i][10]++;
			else if(c == 'Q')
				a[i][11]++;
			else if(c == 'J')
				a[i][12]++;
			else if(c == 'K')
				a[i][13]++;
			else if(c == 'A')
				a[i][1]++;
			else	
				a[i][c-'0']++;
		}
		//starting player has wildcard
		if(i == k)
			a[i][15]++;
		if(sz(a[i]) == 1) {
			cout << i+1 << "\n";
			return 0;
		}
	}
	int t = k;
	int lastJoker = t-1;
	while(true) {
		int i = t%n;
		int next = (t+1)%n;
		//pass wildcard
		if(lastJoker < t-1 && a[i].count(15) > 0) {
			a[i].erase(15);
			a[next][15]++;
			lastJoker = t;
		}
		//pass normal card
		else {
			int mxCnt = 5;
			int id = -1;
			int tot = 0;
			for(auto& [p, cnt] : a[i]) {
				tot += cnt;
				if(p == 15)
					continue;
				if(cnt < mxCnt) {
					mxCnt = cnt;
					id = p;
				}
			}
			assert(tot==5);
			a[i][id]--;
			if(a[i][id] == 0)
				a[i].erase(id);
			a[next][id]++;
		}
		//win
		if(sz(a[i]) == 1) {
			cout << i+1 << "\n";
			break;
		}
		t++;
	}
}