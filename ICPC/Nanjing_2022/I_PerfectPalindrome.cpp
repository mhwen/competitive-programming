#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		int best = 1e6;
		for(int c = 'a'; c <= 'z'; c++) {
			int diff = 0;
			for(char cc : s)
				if(cc != c)
					diff++;
			best = min(best, diff);
		}
		cout << best << "\n";
	}
}