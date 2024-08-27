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
		vector<int> a(n);
		vector<int> b(n);
		for(int& i : a)
			cin >> i;
		for(int& i :b)
			cin >> i;
		auto aRev = a;
		reverse(all(aRev));
		if(a == b || aRev == b)
			cout << "Bob\n";
		else
			cout << "Alice\n";
	}
}