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
		int n, a, b;
		cin >> n >> a >> b;
		string s;
		cin >> s;
		bool found = false;
		int x = 0, y = 0;
		for(int i = 0; i < (int)2e4; i++) {
			char c = s[i%sz(s)];
			if(c == 'N')
				y++;
			if(c == 'S')
				y--;
			if(c == 'E')
				x++;
			if(c == 'W')
				x--;
			if(x == a && y == b) {
				found = true;
				break;
			}
		}	
		if(found)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}