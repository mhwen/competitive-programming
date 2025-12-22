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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

struct Time {
	ll x,y;
	Time(ll X=1,ll Y=1) {
		ll g = gcd(X,Y);
		x = X/g;
		y = Y/g;
		if(y < 0) { x=-x; y=-y; }
	}
	bool operator<(Time t) const { return x*t.y < y*t.x; }
	bool operator>(Time t) const { return x*t.y > y*t.x; }
	bool operator<=(Time t) const { return x*t.y <= y*t.x; }
	ld eval() const { return (ld)x/y; }
};

Time intercept(ll x1, ll y1, ll x2, ll y2) {
	// Ax + By + C = 0
	ll C = x1*y2-y1*x2;
	ll A = y1-y2;
	return Time(-C, A);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, w;
	cin >> n >> w;
	vector<pair<ll,ll>> pts(2*n);
	vector<int> type(2*n);
	for(int i = 0; i < 2*n; i+=2) {
		ll x, y1, y2;
		cin >> x >> y1 >> y2;
		pts[i] = {x,y1};
		pts[i+1] = {x,y2};
		type[i] = 1;
		type[i+1] = -1;
	}
	vector<int> order(2*n);
	iota(all(order), 0);
	sort(all(order), [&](int a, int b) {
		return pts[a].second < pts[b].second;
	});
	vector<int> pos(2*n);
	for(int i = 0; i < 2*n; i++)
		pos[order[i]] = i;
	
	vector<int> pSum(2*n);
	int zeros = 0;
	for(int i = 0; i < 2*n; i++) {
		pSum[i] += type[order[i]];
		if(i > 0)
			pSum[i] += pSum[i-1];
		if(i < 2*n-1 && pSum[i] == 0)
			zeros++;
	}
	if(zeros==0) {
		cout << -1 << "\n";
		return 0;
	}
	typedef pair<Time,pair<int,int>> Event;
	priority_queue<Event, vector<Event>, greater<Event>> q;
	Time prev = Time(-4e12,1);
	
	//returns time of event and order {lo,hi} after event
	auto getEvent = [&](int a, int b) {
		Time t = intercept(pts[a].first,pts[a].second,pts[b].first,pts[b].second);
		//the one with greater y value will be lo
		if(pts[a].second < pts[b].second)
			swap(a,b);
		return pair{t,pair{a,b}};
	};
	auto addEvent = [&](int i) {
		if(i < 0 || i+1 >= sz(pos))
			return;
		auto event = getEvent(order[i],order[i+1]);
		if(prev <= event.first && event.first <= Time(0,1))
			q.push(event);
	};
	auto process = [&](int i, int val) {
		if(pSum[i] == 0 && i != sz(pos)-1)
			zeros--;
		pSum[i] += val;
		if(pSum[i] == 0 && i != sz(pos)-1)
			zeros++;
	};
	auto doSwap = [&](int a, int b) {
		//current order must be b,a, so a must be 1 index after b
		if(pos[a]-pos[b] != 1)
			return;
		process(pos[b], type[a]-type[b]);
		swap(order[pos[a]], order[pos[b]]);
		swap(pos[a],pos[b]);
		addEvent(pos[a]-1);
		addEvent(pos[b]);
	};
	for(int i = 0; i < sz(order)-1; i++)
		addEvent(i);
	
	ld ans = 0;
	while(!q.empty()) {
		auto top = q.top();
		q.pop();
		if(zeros==0)
			ans += top.first.eval()-prev.eval();
		doSwap(top.second.first,top.second.second);
		prev = top.first;
	}
	if(zeros==0)
		ans += -prev.eval();
	cout << fixed << setprecision(20) << ans << "\n";
	
}