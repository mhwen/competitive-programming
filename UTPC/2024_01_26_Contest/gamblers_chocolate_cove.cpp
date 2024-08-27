#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iomanip>


using namespace std;

typedef long long ll;
typedef long double ld;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	ld best = 0;
	for(int j = 0; j < k; j++) {
		int m;
		cin >> m;
		ld val = 0;
		vector<int> rewards(m);
		for(int i = 0; i < m; i++) {
			cin >> rewards[i];
		}
		for(int i = 0; i < m; i++) {
			ld p;
			cin >> p;
			val += rewards[i]*p;
		}
		best = max(best, val);
	}
	cout << setprecision(20) << best*n << "\n";
}