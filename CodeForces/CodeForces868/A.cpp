#include <iostream>
#include <vector>

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
		bool found = false;
		for(int i = 0; i <= n; i++) {
			int ones = n-i;
			int negs = i;
			int count = ones*(ones-1)/2+negs*(negs-1)/2;
			if(count == k) {
				found = true;
				cout << "YES\n";
				for(int j = 0; j < ones; j++) {
					cout << 1 << " ";
				}
				for(int j = 0; j < negs; j++) {
					cout << -1 << " ";
				}
				cout << "\n";
				break;
			}
		}
		if(!found)
			cout << "NO\n";
	}
	
}