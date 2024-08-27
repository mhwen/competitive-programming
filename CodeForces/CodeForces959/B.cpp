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
		string a, b;
		cin >> a >> b;
		int firstDiff = n;
		int firstOne = n;
		for(int i = n-1; i >= 0; i--) {
			if(a[i] == '1')
				firstOne = i;
			if(a[i] != b[i])
				firstDiff = i;
		}
		if(firstOne <= firstDiff)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}