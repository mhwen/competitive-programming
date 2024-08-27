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
		int best = 0;
		int ones = 0, zeros = 0;
		for(char c : s) {
			if(c=='0')
				zeros++;
			else
				ones++;
		}
		best = max(best, min(ones, zeros));
		if(zeros < ones) {
			for(int i = n-1; i >= 0; i--) {
				if(s[i] == '0') {
					zeros--;
				}
				else {
					ones--;
					zeros++;
				}
				best = max(best, min(ones, zeros));
			}
		}
		else {
			for(int i = 0; i < n; i++) {
				if(s[i] == '1') {
					ones--;
				}
				else {
					zeros--;
					ones++;
				}
				best = max(best, min(ones, zeros));
			}
		}
		cout << best << "\n";
	}
}