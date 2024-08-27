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
		int n;
		cin >> n;
		bool up = false, down = false, left = false, right = false;
		for(int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			if(x < 0)
				left = true;
			if(x > 0)
				right = true;
			if(y < 0)
				down = true;
			if(y > 0)
				up = true;
		}
		if(up && down && left && right)
			cout << "NO\n";
		else
			cout << "YES\n";
	}
}