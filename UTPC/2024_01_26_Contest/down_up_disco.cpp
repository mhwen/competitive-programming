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
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for(int i = 0; i < n; i++)
		cin >> grid[i];
	vector flips(n, vector<int>(m));
	int used = 0;
	for(int r = n-1; r >= 0; r--) {
		for(int c = m-1; c >= 0; c--) {
			int val = grid[r][c] == '0' ? 0 : 1;
			val = (val+flips[r][c])%2;
			if(val == 1) {
				used++;
				flips[r][c]++;
			}
			flips[r][c] %= 2;
			if(r > 0)
				flips[r-1][c] += flips[r][c];
			if(c > 0)
				flips[r][c-1] += flips[r][c];
			if(r > 0 && c > 0)
				flips[r-1][c-1] += flips[r][c];
		}
	}
	cout << used << "\n";
}