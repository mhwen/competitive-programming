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
		if(n%2==1) {
			cout << n << "\n";
			for(int i = 1; i <= n; i++) {
				if(i == 1 || i == 3 || i == n-1 || i == n)
					continue;
				cout << i << " ";
			}
			cout << 1 << " " << 3 << " " << n-1 << " " << n << "\n";
		}
		else {
			if(n == 6) {
				cout << "7\n";
				cout << "1 2 4 6 5 3\n";
				continue;
			}
			int mask = 1;
			while(mask*2 <= n)
				mask *= 2;
			cout << mask*2-1 << "\n";
			mask--;
			for(int i = 1; i <= n; i++) {
				if(i == 1 || i == 3 || i == mask-1 || i == mask || i == n)
					continue;
				cout << i << " ";
			}
			cout << 1 << " " << 3 << " " << mask-1 << " " << mask << " " << n << "\n";
		}
	}
}