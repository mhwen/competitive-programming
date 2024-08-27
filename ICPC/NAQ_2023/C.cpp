#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;
constexpr ld EPS = 1e-9;

bool possible(vector<ll>& f, vector<ll>& s, ld lose, int n) {
	priority_queue<pair<int, ld>> avail;
	for(int i = 0; i < n; i++) {
		avail.push({-s[i], f[i]});
		while(!avail.empty() && -avail.top().first <= i) {
			avail.pop();
		}
		ld remaining = lose;
		while(!avail.empty() && remaining > 0) {
			if(avail.top().second <= remaining) {
				remaining -= avail.top().second;
				avail.pop();
			}
			else {
				auto val = avail.top();
				val.second -= remaining;
				avail.pop();
				avail.push(val);
				// avail.top().second -= remaining;
				remaining = 0;
			}
		}
		if(remaining > 0)
			return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<ll> food(n);
	vector<ll> spoil(n);
	for(int i = 0; i < n; i++) {
		cin >> food[i] >> spoil[i];
	}
	ld left = 0, right = 1e9;
	for(int i = 0; i < 69; i++) {
		ld mid = (left+right)/2;
		if(possible(food, spoil, mid*k, n))
			left = mid;
		else
			right = mid;
	}
	ld ans = (left+right)/2;
	if(ans < EPS)
		cout << -1 << "\n";
	else
		cout << setprecision(20) << (left+right)/2 << "\n";
}