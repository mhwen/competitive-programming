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
	int d;
	cin >> d;
	map<vector<int>, vector<int>> sets;
	ll c = 1;
	for(int i = 0; i < d; i++) {
		c = c*10;
	}
	for(int i = 1; i*i < c; i++) {
		vector<int> digits;
		ll val = i*i;
		while(val > 0) {
			int dig = (int)(val%10);
			val = val/10;
			digits.push_back(dig);
		}
		if((int)digits.size() < d)
			continue;
		sort(digits.begin(), digits.end());
		sets[digits].push_back(i);
	}
	for(auto& i : sets) {
		if((int)i.second.size() < d)
			continue;
		for(int f : i.first)
			cout << f << " ";
		cout << endl;
		for(int f : i.second)
			cout << f << ": " << f*f << endl;
	}
}