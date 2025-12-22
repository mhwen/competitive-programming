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
		vector<vector<int>> con(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			con[a].push_back(b);
			con[b].push_back(a);
		}
		vector<char> node(n);
		for(int i = 0; i < n; i++)
			cin >> node[i];
			
		int one = 0;
		int zero = 0;
		int free = 0;
		int extra = 0;
		for(int i = 1; i < n; i++) {
			if(sz(con[i]) == 1) {
				if(node[i] == '?')
					free++;
				else if(node[i] == '1')
					one++;
				else
					zero++;
			}
			else if(node[i] == '?')
				extra++;
		}
		if(node[0] != '?') {
			if(node[0] == '1')
				cout << zero+(free+1)/2;
			else
				cout << one+(free+1)/2;
		}
		else {
			int moveFirst = max(one, zero)+free/2;
			int moveSecond = min(one, zero)+(free+1)/2;
			if(extra%2==0)
				cout << moveFirst;
			else
				cout << max(moveFirst, moveSecond);
		}
		cout << "\n";
	}
}