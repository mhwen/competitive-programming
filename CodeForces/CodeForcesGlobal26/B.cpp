#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		bool zeroMid = false;
		for(int i = 1; i < sz(s)-1; i++) {
			if(s[i] == '0')
				zeroMid = true;
		}
		if(s[0] != '1' || s.back() == '9' || zeroMid)
			cout << "NO\n";
		else
			cout << "YES\n";
	}
}