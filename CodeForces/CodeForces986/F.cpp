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
#include <bitset>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

typedef bitset<10001> state;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		state curr, prefix, zero;
		vector<state> prev(15);
		vector<int> prevNum(15);
		
		int start;
		cin >> start;
		curr[start] = true;
		prefix[0] = prefix[start] = true;
		prev[0][0] = true;
		prevNum[0] = start;
		if(start == 0)
			zero = curr = prefix;
		int id = 1;
		for(int i = 1; i < n; i++) {
			int a;
			cin >> a;
			if(a == 1)
				curr = curr|(curr<<1);
			else {
				prev[id%sz(prev)] = curr;
				prevNum[id%sz(prev)] = a;
				if(a == 0)
					zero = curr = prefix;
				else {
					state newCurr;
					int val = 1;
					int pid = id;
					while(pid >= 0 && val*prevNum[pid%sz(prevNum)] <= m) {
						val *= prevNum[pid%sz(prevNum)];
						newCurr |= prev[pid%sz(prev)]<<val;
						pid--;
						if(val == 0)
							break;
					}
					curr = newCurr;
				}
				id++;
			}
			curr |= zero;
			prefix |= curr;
			// cout << curr << endl;
		}
		if(curr[m])
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	
}