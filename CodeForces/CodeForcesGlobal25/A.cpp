#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
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
		int ones = 0;
		for(char c : s)
			if(c == '1')
				ones++;
		bool adj = false;
		for(int i = 0; i < n-1; i++) {
			if(s[i] == '1' && s[i+1] == '1')
				adj = true;
		}
		if(ones%2==1)
			cout << "NO\n";
		else if(ones == 2 && adj)
			cout << "NO\n";
		else
			cout << "YES\n";
	}
}