#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> reds(n);
	vector<int> greens(n);
	int red = 0, green = 0;
	int best = 0;
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for(char c : s) {
			if(c == 'R')
				reds[i]++;
			else
				greens[i]++;
		}
				
		best = max(best, red+reds[i]);
		best = max(best, green+greens[i]);
		if(reds[i] == 0)
			green += greens[i];
		else
			green = greens[i];
		if(greens[i] == 0)
			red += reds[i];
		else
			red = reds[i];
		
	}
	cout << best << "\n";
}