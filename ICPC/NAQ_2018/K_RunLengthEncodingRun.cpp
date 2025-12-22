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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	char t;
	string s;
	cin >> t >> s;
	if(t == 'E') {
		string res;
		char curr = s[0];
		int cnt = 0;
		for(char c : s) {
			if(c == curr)
				cnt++;
			else {
				res += curr;
				res += (char)('0'+cnt);
				cnt = 1;
				curr = c;
			}
		}
		res += curr;
		res += (char)('0'+cnt);
		cout << res << "\n";
	}
	else {
		string res;
		for(int i = 0; i < sz(s); i+=2) {
			int amt = s[i+1]-'0';
			for(int j = 0; j < amt; j++)
				res += s[i];
		}
		cout << res << "\n";
	}
}