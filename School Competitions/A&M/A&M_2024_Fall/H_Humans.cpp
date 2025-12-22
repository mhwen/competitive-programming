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
	int n;
	cin >> n;
	vector<string> grid(n);
	for(int i = 0; i < n; i++)
		cin >> grid[i];
	int a = 0;
	int b = 0;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			if(grid[r][c] == 'X') {
				if((r+c)%2==0)
					a++;
				else
					b++;
			}
		}
	}
	int cnt = a+b;
	if(cnt%2==0) {
		if(n%2==0)
			cout << "HUMAN\n";
		else {
			if(b%2==0)
				cout << "HUMAN\n";
			else
				cout << "SKINWALKER\n";
		}
	}
	else {
		if(n%2==0) {
			if(a%2 != b%2) cout << "HUMAN\n";
			else cout << "SKINWALKER\n";
		}
		else {
			if(a%2==1 && b%2==0) cout << "HUMAN\n";
			else cout << "SKINWALKER\n";
		}
	}
}