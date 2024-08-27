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
	int n;
	cin >> n;
	string s;
	cin >> s;
	int l = 0, o = 0;
	for(char c : s) {
		if(c=='L')
			l++;
		else
			o++;
	}
	int myL = 0, myO = 0;
	int ans = -1;
	for(int i = 0; i < n-1; i++) {
		if(s[i] == 'L')
			myL++;
		else
			myO++;
		if(myL != l-myL && myO != o-myO)
			ans = i+1;
	}
	cout << ans << "\n";
}