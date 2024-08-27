#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int a, b, c;
		cin >> a >> b >> c;
		cout << (b+c+1)%2 << " " << (a+c+1)%2 << " " << (a+b+1)%2 << "\n";
	}
}