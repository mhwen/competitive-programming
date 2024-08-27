#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
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
		vector<int> degree(n);
		for(int i = 0; i < n-1; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			degree[a]++;
			degree[b]++;
		}
		int leaves = 0;
		for(int i = 0; i < n; i++) {
			if(degree[i] == 1)
				leaves++;
		}
		cout << (leaves+1)/2 << "\n";
	}
}