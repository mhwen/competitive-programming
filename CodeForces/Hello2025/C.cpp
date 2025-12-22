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
		ll l, r;
		cin >> l >> r;
		ll mask = 0;
		for(int bit = 30; bit >= 0; bit--) {
			if((l&(1LL<<bit)) == (r&(1LL<<bit)))
				mask += (l&(1LL<<bit));
			else {
				ll B = 1LL<<bit;
				if(mask+B==r)
					mask--;
				cout << mask+B-1 << " " << mask+B << " " << r << "\n";
				break;
			}
		}
	}
}