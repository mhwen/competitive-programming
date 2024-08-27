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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> hay(n);
		for(int i = 0; i < n; i++) {
			cin >> hay[i];
		}
		set<int> pos;
		for(int i = 0; i < n-1; i++) {
			if(hay[i] == hay[i+1])
				pos.insert(hay[i]);
		}
		for(int i = 0; i < n-2; i++) {
			if(hay[i] == hay[i+2])
				pos.insert(hay[i]);
		}
		if(pos.empty())
			cout << -1 << "\n";
		else {
			vector<int> vals;
			for(int i : pos)
				vals.push_back(i);
			for(int i = 0; i < (int)vals.size(); i++) {
				cout << vals[i];
				if(i < (int)vals.size()-1)
					cout << " ";
			}
			cout << "\n";
		}
	}
}