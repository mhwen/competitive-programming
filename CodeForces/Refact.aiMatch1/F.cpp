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
		int r = 0, b = 0;
		bool R = false, B = false;
		for(int i = 0; i < n; i++) {
			int nxt = (i+1)%n;
			if(s[i] == 'R') {
				r++;
				if(s[i] == s[nxt])
					R = true;
			}
			else {
				b++;
				if(s[i] == s[nxt])
					B = true;
			}
		}
		if(R&&B)
			cout << "NO\n";
		else if(r <= 1 || b <= 1)
			cout << "YES\n";
		else {
			char target = R ? 'B' : 'R';
			int start = 0;
			for(int i = 0; i < n; i++) {
				if(s[i] == target)
					start = i;
			}
			vector<int> comps;
			int curr = 0;
			for(int i = 1; i <= n; i++) {
				int id = (start+i)%n;
				if(s[id] == target) {
					comps.push_back(curr);
					curr = 0;
				}
				else
					curr++;
			}
			int even = 0;
			for(int i = 0; i < sz(comps); i++) {
				if(comps[i]%2==0)
					even++;
			}
			if(even==1)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
}