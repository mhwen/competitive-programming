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
	ll n, k;
	int m;
	cin >> n >> m >> k;
	vector<pair<ll, ll>> pos;
	pos.push_back({0, 0});
	int time = 0;
	bool good = true;
	for(int i = 0; i < m; i++) {
		int a, b, t;
		cin >> a >> b >> t;
		int diff = t-time;
		vector<pair<ll, ll>> newPos;
		for(int j = 0; j < (int)pos.size(); j++) {
			pos[j].first -= diff*k;
			pos[j].second += diff*k;
			if(j == 0)
				pos[j].first = max(0LL, pos[j].first);
			else
				pos[j].first = max(pos[j-1].first, pos[j].first);
			pos[j].second = min((ll)n, pos[j].second);
			if(pos[j].first <= pos[j].second)
				newPos.push_back(pos[j]);
		}
		pos = newPos;
		newPos.clear();
		for(auto p : pos) {
			if(a <= p.first && p.second <= b)
				continue;
			if(a > p.second || b < p.first) {
				newPos.push_back(p);
			}
			else if(p.first < a && b < p.second) {
				newPos.push_back({p.first, a-1});
				newPos.push_back({b+1, p.second});
			}
			else if(a <= p.first) {
				newPos.push_back({b+1, p.second});
			}
			else {
				newPos.push_back({p.first, a-1});
			}
		}
		
		pos = newPos;
		time = t;
		if(pos.empty()) {
			good = false;
			break;
		}
		
	}
	if(good)
		cout << "YES\n";
	else
		cout << "NO\n";
}