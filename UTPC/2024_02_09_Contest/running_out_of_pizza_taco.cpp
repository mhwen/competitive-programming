#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	int x, y, z;
	cin >> x >> y >> z;
	int extra = min(n, z/2);
	int used = 2*n+extra;
	if(used > x || used > y)
		cout << "yes\n";
	else
		cout << "no\n";
}