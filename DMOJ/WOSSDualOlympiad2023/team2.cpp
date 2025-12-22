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
	stack<pair<int, ll>> s;
	ll water = 0;
	for(int i = 0; i < n; i++) {
		ll h;
		cin >> h;
		ll prevHeight = 0;
		while(!s.empty() && s.top().second < h) {
			ll newHeight = s.top().second;
			water += (newHeight-prevHeight)*(i-s.top().first-1);
			s.pop();
			prevHeight = newHeight;
		}
		if(!s.empty())
			water += (h-prevHeight)*(i-s.top().first-1);
		s.push({i, h});
	}
	cout << water << "\n";
}