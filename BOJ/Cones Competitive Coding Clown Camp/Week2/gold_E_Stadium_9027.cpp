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
		int n;
		cin >> n;
		vector<int> coords(n);
		for(int i = 0; i < n; i++) {
			cin >> coords[i];
		}
		ll sum = 0;
		vector<ll> people(n);
		for(int i = 0; i < n; i++) {
			cin >> people[i];
			sum += people[i];
		}
		ll seen = 0;
		for(int i = 0; i < n; i++) {
			seen += people[i];
			if(seen >= (sum+1)/2) {
				cout << coords[i] << "\n";
				break;
			}
		}
	}
}