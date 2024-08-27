#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;
typedef long double ld;

struct point {
	ll x, y;
	int id;
};

ll dist(point p) {
	return p.x*p.x+p.y*p.y;
}

ll cross(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

bool up (point p) {
  return p.y > 0 || (p.y == 0 && p.x >= 0);
}

void update(int pos, int val, vector<int>& tree) {
	int n = (int)tree.size()/2;
	pos += n;
	while(pos > 0) {
		tree[pos] += val;
		pos >>= 1;
	}
}

int query(int l, int r, vector<int>& tree) {
	int n = (int)tree.size()/2;
	l += n; r += n;
	int sum = 0;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1)
			sum += tree[l++];
		if(r%2==0)
			sum += tree[r--];
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<bool> blue(n);
	string s;
	cin >> s;
	for(int i = 0; i < n; i++) {
		if(s[i] == 'b')
			blue[i] = true;
	}
	vector<point> dots(n);
	for(int i = 0; i < n; i++) {
		cin >> dots[i].x >> dots[i].y;
		dots[i].id = i;
	}
	vector<int> order(n);

	
	sort(dots.begin(), dots.end(), [] (const point& a, const point& b) {
		return up(a) == up(b) ? cross(a, b) > 0 : up(a) < up(b);
	});
	int r = 1;
	for(int i = 0; i < n; i++) {
		if(i > 0 && cross(dots[i], dots[i-1]) != 0)
			r++;
		order[dots[i].id] = r;
	}
	set<int> blocked;
	blocked.insert(0);
	blocked.insert(r+1);
	vector<int> tree(2*(r+1));
	
	sort(dots.begin(), dots.end(), [] (const point& a, const point& b) {
		return dist(a)<dist(b);
	});
	
	int best = 0;
	for(point p : dots) {
		int id = p.id;
		int radialOrder = order[id];
		if(blue[id]) {
			blocked.insert(radialOrder);
		}
		else {
			update(radialOrder, 1, tree);
			auto it = blocked.lower_bound(radialOrder);
			int right = *it;
			it = blocked.upper_bound(radialOrder);
			it--;
			int left = *it;
			if(right-left >= 2) {
				best = max(best, query(left+1, right-1, tree));
			}
		}
	}
	cout << best << "\n";
}