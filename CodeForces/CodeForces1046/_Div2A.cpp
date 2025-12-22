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
#define pb push_back

bool check(int A, int B) {
	int D = abs(A-B);
	int need = max(0, D-2);
	return need*3+min(2, D) <= A+B;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if(check(a, b) && check(c-a, d-b))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}