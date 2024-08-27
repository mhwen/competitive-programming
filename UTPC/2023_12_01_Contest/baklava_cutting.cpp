#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ld l;
	int k;
	cin >> l >> k;
	l = l*l;
	for(int i = 0; i < k; i++) {
		l = l/2;
	}
	cout << fixed << setprecision(20) << l << "\n";
}