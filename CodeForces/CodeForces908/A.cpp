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
		int n, k;
		cin >> n >> k;
		vector<int> b(n);
		for(int i = 0; i < n; i++) {
			cin >> b[i];
		}
		vector<bool> used(n);
		int index = n-1;
		bool good = true;
		for(int i = 0; i < k; i++) {
			if(b[index] > n) {
				good = false;
				break;
			}
			if(used[index])
				break;
			used[index] = true;
			index -= b[index];
			while(index < 0)
				index += n;
		}
		if(good)
			cout << "Yes\n";
		else
			cout << "No\n";
			
	}
}