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
		bool flipped = false;
		for(char c : s) {
			if(c == '7')
				break;
			if(c == '1'){
				flipped = true;
				break;
			}
		}
		if(flipped)
			cout << 17 << "\n";
		else
			cout << 71 << "\n";
	}
}