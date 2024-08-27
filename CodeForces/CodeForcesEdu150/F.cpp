#include <iostream>
#include <vector>

using namespace std;

typedef __int128 ll;
// typedef long long ll;
typedef pair<ll, ll> point;

bool up(point p) {
	return p.second > 0 || (p.second == 0 && p.first > 0);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<point> points;
	ll x = 0, y = 0;
	ll totalx = 0, totaly = 0;
	for(int i = 0; i < n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		points.push_back({a-b, c-d});
		if(up(points[i])) {
			x += points[i].first;
			y += points[i].second;
		}
		totalx += points[i].first;
		totaly += points[i].second;
	}
	for(int i = 0; i < n; i++) {
		points.push_back({-points[i].first, -points[i].second});
	}
	sort(points.begin(), points.end(), [] (point a, point b) {
		if(up(a) == up(b)) {
			return a.second*b.first < b.second*a.first;
		}
		else {
			return up(a) < up(b);
		}
	});
	ll best = max(x*x+y*y, (totalx-x)*(totalx-x)+(totaly-y)*(totaly-y));
	for(int i = 0; i < (int)points.size(); i++) {
		x += points[i].first;
		y += points[i].second;
		best = max(best, max(x*x+y*y, (totalx-x)*(totalx-x)+(totaly-y)*(totaly-y)));
	}
	vector<int> digits;
	if(best == 0)
		digits.push_back(0);
	while(best > 0) {
		digits.push_back((int)(best%10));
		best /= 10;
	}
	reverse(digits.begin(), digits.end());
	for(int i : digits)
		cout << i;
	cout << "\n";
	
}