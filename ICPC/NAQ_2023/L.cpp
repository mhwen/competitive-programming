#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, a, b;
	cin >> n >> a >> b;
	bool maxSeen = false;
	bool minSeen = false;
	for(int i = 0; i < n-1; i++) {
		int w;
		cin >> w;
		if(w == b)
			maxSeen = true;
		if(w == a)
			minSeen = true;
	}
	vector<int> ans;
	for(int i = a; i <= b; i++) {
		bool maxGood = (i==b) || maxSeen;
		bool minGood = (i==a) || minSeen;
		if(maxGood && minGood)
			ans.push_back(i);
	}
	if(ans.size() == 0)
		cout << -1 << "\n";
	else
		for(int i : ans)
			cout << i << "\n";
}