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
	int n, k;
	cin >> n >> k;
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			if(k > 0) {
				cout << "1";
				k--;
			}
			else
				cout << "0";
		}
		cout << "\n";
	}
}