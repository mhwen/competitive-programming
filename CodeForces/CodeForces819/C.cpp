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
		string s;
		cin >> s;
		int count = 1;
		for(int i = 0; i < 2*n-1; i++) {
			if(s[i] == s[i+1] && s[i] == '(')
				count++;
		}
		cout << count << "\n";
	}
}