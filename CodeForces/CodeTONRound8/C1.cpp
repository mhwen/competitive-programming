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
	int t;
	cin >> t;
	while(t-->0) {
		int n, x, y;
		cin >> n >> x >> y;
		vector<int> points(x);
		for(int i = 0; i < x; i++)
			cin >> points[i];
		sort(points.begin(), points.end());
		points.push_back(points.front()+n);
		int extra = 0;
		for(int i = 0; i < x; i++) {
			if(points[i+1]-points[i] == 2)
				extra++;
		}
		cout << x-2+extra << "\n";
	}
}