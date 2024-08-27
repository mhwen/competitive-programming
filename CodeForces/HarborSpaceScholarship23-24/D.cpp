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
		int n;
		cin >> n;
		vector<int> starts(n+2);
		vector<int> ends(n+2);
		int moves = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 1; j <= n; j++) {
				starts[j-1] += starts[j];
				starts[j] = 0;
			}
			for(int j = n; j >= 1; j--) {
				ends[j+1] += ends[j];
				ends[j] = 0;
			}
			string s;
			cin >> s;
			vector<int> parities(n);
			int parity = starts[0];
			for(int j = 0; j < n; j++) {
				parity = parity+starts[j+1]-ends[j+1];
				// cout << parity << " ";
				parities[j] = parity%2;
			}
			// cout << endl;
			for(int j = 0; j < n; j++) {
				if(s[j] == '1' && parities[j] == 0) {
					moves++;
					starts[j+1]++;
					ends[j+2]++;
				}
				if(s[j] == '0' && parities[j] == 1) {
					moves++;
					starts[j+1]++;
					ends[j+2]++;
				}
			}
		}
		cout << moves << "\n";
	}
}