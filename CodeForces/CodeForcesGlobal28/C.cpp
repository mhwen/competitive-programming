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
#include <cassert>

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
	while(t-->0) {
		string S;
		cin >> S;
		vector<int> s;
		for(char c : S)
			if(c == '0')
				s.push_back(0);
			else
				s.push_back(1);
		int n = sz(s);
		int f = n-1;
		for(int i = 0; i < n; i++) {
			if(s[i] == 0) {
				f = i;
				break;
			}
		}
		int best = 0;
		auto check = [&](int c) {
			int i = 0;
			while(f+i < n && (s[f+i]^s[best+i])==(s[f+i]^s[c+i]))
				i++;
			if((s[f+i]^s[best+i]) <= (s[f+i]^s[c+i]))
				best = c;
		};
		
		for(int i = 0; i <= f; i++) {
			check(i);
		}

		cout << 1 << " " << n << " " << best+1 << " " << best+n-f << "\n";
	}
}