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
	int t;
	cin >> t;
	string s;
	getline(cin, s);
	while(t-->0) {
		getline(cin, s);
		if(s[0] == 'e') {
			int sum = 0;
			string res;
			for(int i = 2; i < sz(s); i++) {
				if(s[i] != ' ')
					sum += s[i]-'a'+1;
				sum %= 27;
				if(sum == 0)
					res += " ";
				else
					res += (char)('a'+sum-1);
			}
			cout << res << "\n";
		}
		else {
			int sum = 0;
			string res;
			for(int i = 2; i < sz(s); i++) {
				int needed = 0;
				if(s[i] != ' ')
					needed = s[i]-'a'+1;
				int diff = (needed-sum+27)%27;
				if(diff == 0)
					res += " ";
				else
					res += (char)('a'+diff-1);
				sum = needed;
			}
			cout << res << "\n";
		}
	}
}