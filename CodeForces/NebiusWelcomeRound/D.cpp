#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	int totalSmall = 0;
	int totalBig = 0;
	while(n-->0) {
		string s;
		cin >> s;

		int ones = 0;
		for(int i = 0; i < m; i++) {
			if(s[i] == '1')
				ones++;
		}
		int pairs = 0;
		for(int i = 0; i < m-1; i++) {
			if(s[i] == '1' && s[i+1] == '1') {
				pairs++;
				i++;
			}
		}
		int small = ones-min(pairs, m/4);
		
		pairs = 0;
		int singles = 0;
		for(int i = 0; i < m-1; i++) {
			if(s[i] == '0' && s[i+1] == '1') {
				singles++;
				i++;
			}
			else if(s[i] == '1' && s[i+1] == '0') {
				singles++;
				i++;
			}
			else if(s[i] == '0' && s[i+1] == '0') {
				pairs++;
				i++;
			}
		}
		int big = ones-max(0, m/4-pairs-singles);
		
		// cout << small << " " << big << "\n";
		totalSmall += small;
		totalBig += big;
	}
	
	cout << totalSmall << " " << totalBig << "\n";
}