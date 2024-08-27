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
	vector<int> pos(n);
	vector<char> type(n);
	for(int i = 0; i < n; i++) {
		cin >> type[i] >> pos[i];
	}
	int best = n;
	for(int i = 0; i < n; i++) {
		int liars = 0;
		for(int j = 0; j < n; j++) {
			if(pos[j] > pos[i] && type[j] == 'G')
				liars++;
			else if(pos[j] < pos[i] && type[j] == 'L')
				liars++;
		}
		best = min(best, liars);
	}
	cout << best << "\n";
}