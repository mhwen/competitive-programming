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
		string s;
		cin >> s;
		int count = 0;
		for(char c : s) {
			if(c == '.')
				count++;
		}
		bool found = false;
		for(int i = 0; i < n-2; i++) {
			if(s[i] == '.' && s[i+1] == '.' && s[i+2] == '.')
				found = true;
		}
		if(found)
			cout << 2 << "\n";
		else
			cout << count << "\n";
	}
}