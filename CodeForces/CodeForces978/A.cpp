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
		int n, r;
		cin >> n >> r;
		int seats = r*2;
		int extra = 0;
		int happy = 0;
		for(int i = 0; i < n; i++) {
			int num;
			cin >> num;
			int good = num-num%2;
			extra += num-good;
			happy += good;
			seats -= good;
		}
		while(extra > 0 && seats > extra) {
			extra--;
			seats -= 2;
			happy++;
		}
		cout << happy << "\n";
		
	}
}