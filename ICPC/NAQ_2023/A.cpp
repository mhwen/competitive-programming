#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, c;
	cin >> n >> k >> c;
	vector<int> taken(n+1);
	vector<int> remaining;
	vector<int> ans;
	vector<bool> take(n);
	vector<int> ids(n);
	for(int i = 0; i < n; i++) {
		int t, s;
		cin >> t >> s;
		ids[i] = t;
		if(k > 0 && taken[s] < c) {
			taken[s]++;
			k--;
			take[i] = true;
		}
		else
			remaining.push_back(i);
	}
	for(int i = 0; i < k; i++) {
		take[remaining[i]] = true;
	}
	for(int i = 0; i < n; i++)
		if(take[i])
			cout << ids[i] << "\n";
}