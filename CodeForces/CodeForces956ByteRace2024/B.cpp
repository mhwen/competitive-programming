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
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<string> a(n);
		for(int i = 0; i < n; i++)
			cin >> a[i];
		vector<string> b(n);
		for(int i = 0; i < n; i++)
			cin >> b[i];
		vector grid(n, vector<int>(m));
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < m; c++) {
				grid[r][c] = (b[r][c]-a[r][c]+3)%3;
			}
		}
		bool good = true;
		for(int r = 0; r < n; r++) {
			int sum = 0;
			for(int c = 0; c < m; c++) {
				sum += grid[r][c];
			}
			if(sum%3 != 0)
				good = false;
		}
		for(int c = 0; c < m; c++) {
			int sum = 0;
			for(int r = 0; r < n; r++) {
				sum += grid[r][c];	
			}
			if(sum%3 != 0)
				good = false;
		}
		if(good)
			cout << "YES\n";
		else
			cout << "NO\n";
		
	}
}