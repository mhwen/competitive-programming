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
		string s;
		cin >> s;
		int extra = 0;
		for(char c : s) {
			if(c == '?')
				extra++;
		}
		int res = 1;
		for(int i = 0; i < extra; i++) {
			res *= 10;
		}
		if(s[0] == '?')
			res = res/10*9;
		if(s[0] == '0')
			cout << 0 << "\n";
		else
			cout << res << "\n";
	}
}