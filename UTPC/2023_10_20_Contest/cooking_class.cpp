#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> skills(n);
	for(int i = 0; i < n; i++) {
		cin >> skills[i];
	}
	int alice;
	cin >> alice;
	int best = 0;
	for(int i = 0; i < m; i++) {
		int p;
		cin >> p;
		best = max(best, p);
	}
	alice += best;
	sort(skills.rbegin(), skills.rend());
	int place = n+1;
	for(int i = 0; i < n; i++) {
		if(alice >= skills[i]) {
			place = i+1;
			break;
		}
	}
	cout << place << "\n";
}