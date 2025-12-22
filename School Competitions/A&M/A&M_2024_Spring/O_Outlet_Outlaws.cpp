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

int gcd(int a, int b) {
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, myX, myY;
	cin >> n >> myX >> myY;
	set<pair<int, int>> lines;
	for(int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		if(x == myX) {
			if(y < myY)
				lines.insert({0, -1});
			else
				lines.insert({0, 1});
		}
		else {
			int xDiff = abs(myX-x);
			int yDiff = abs(myY-y);
			int g = gcd(xDiff, yDiff);
			pair<int, int> line = {xDiff/g, yDiff/g};
			
			if(x < myX)
				line.first *= -1;
			if(y < myY)
				line.second *= -1;
			lines.insert(line);
		}
	}
	cout << lines.size() << "\n";
}