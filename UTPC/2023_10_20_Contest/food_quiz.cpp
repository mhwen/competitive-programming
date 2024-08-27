#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> vals(m);
	for(int i = 0; i < m; i++) {
		cin >> vals[i];
	}
	int q;
	cin >> q;
	
	set<int> pos;
	pos.insert(0);
	for(int i = 0; i < n; i++) {
		set<int> newPos;
		for(int p : pos) {
			for(int val : vals)
				newPos.insert(p+val);
		}
		pos = newPos;
	}
	
	for(int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		bool found = false;
		for(int j = l; j <= r; j++) {
			if(pos.count(j))
				found = true;
		}
		if(found)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	
	
}