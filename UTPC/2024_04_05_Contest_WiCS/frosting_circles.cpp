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

int dist2(int x, int y, int x2, int y2) {
	int dx = x-x2;
	int dy = y-y2;
	return dx*dx+dy*dy;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, R;
	cin >> n >> R;
	vector<int> x(n);
	vector<int> y(n);
	vector<int> r(n);
	for(int i = 0; i < n; i++) {
		cin >> r[i] >> x[i] >> y[i];
	}
	int count = 0;
	for(int X = -100; X <= 100; X++) {
		for(int Y = -100; Y <= 100; Y++) {
			if(dist2(X, Y, 0, 0) > R*R)
				continue;
			for(int i = 0; i < n; i++) {
				if(dist2(X, Y, x[i], y[i]) <= r[i]*r[i]) {
					count++;
					break;
				}
			}
		}
	}
	cout << count << "\n";
}