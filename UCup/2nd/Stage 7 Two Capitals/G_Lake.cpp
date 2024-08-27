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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	auto check = [&](int i) {
		int extra = max(0, n-3*i)+max(0, m-3*i);
		if(extra <= i)
			return true;
		return false;
	};
	
	int i = 1;
	while(!check(i))
		i++;
	cout << 2*i-1 << "\n";
}