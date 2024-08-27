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
		vector nums(n, vector<int>(m));
		for(int r = 0; r < n; r++)
			for(int c = 0; c < m; c++)
				cin >> nums[r][c];
		if(n == 1) {
			if(m == 1) {
				cout << "-1\n";
			}
			else {
				for(int r = 0; r < n; r++) {
					for(int c = 0; c < m; c++) {
						cout << nums[r][(c+1)%m] << " ";
					}
					cout << "\n";
				}
			}
		}
		else {
			for(int r = 0; r < n; r++) {
				for(int c = 0; c < m; c++) {
					cout << nums[(r+1)%n][c] << " ";
				}
				cout << "\n";
			}
		}
	}
}