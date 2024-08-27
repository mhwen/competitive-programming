#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int inputs;
	cin >> inputs;
	while(inputs-->0) {
		int n, m;
		cin >> n >> m;
		int count = 0;
		vector<int> res;
		set<int> seen;
		for(int i = 0; i < m; i++) {
			int a;
			cin >> a;
			seen.insert(a);
			if((int)seen.size() > count) {
				count++;
				res.push_back(i+1);
			}
		}
		while((int)res.size() < n) {
			res.push_back(-1);
		}
		for(int i = n-1; i >= 0; i--) {
			cout << res[i] << " ";
		}
		cout << "\n";
	}
}