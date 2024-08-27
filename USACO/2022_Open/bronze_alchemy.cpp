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
	vector<int> amounts(n);
	for(int i = 0; i < n; i++) {
		cin >> amounts[i];
	}
	int k;
	cin >> k;
	vector<vector<int>> recipe(n);
	vector<bool> hasRecipe(n);
	for(int i = 0; i < k; i++) {
		int l, m;
		cin >> l >> m;
		l--;
		for(int j = 0; j < m; j++) {
			int val;
			cin >> val;
			val--;
			recipe[l].push_back(val);
		}
		hasRecipe[l] = true;
	}
	int count = 0;
	vector<int> needed(n);
	while(true) {
		fill(needed.begin(), needed.end(), 0);
		needed[n-1] = 1;
		bool good = true;
		for(int i = n-1; i >= 0; i--) {
			int fulfilled = min(amounts[i], needed[i]);
			amounts[i] -= fulfilled;
			needed[i] -= fulfilled;
			if(needed[i] > 0 ) {
				if(!hasRecipe[i]) {
					good = false;
					break;
				}
				else {
					for(int val : recipe[i]) {
						needed[val] += needed[i];
					}
				}
			}
		}
		if(!good)
			break;
		count++;
	}
	cout << count << "\n";
}