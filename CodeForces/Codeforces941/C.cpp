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
		int n;
		cin >> n;
		string s;
		cin >> s;
		stack<int> comps;
		int prev = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == s[i+1]) {
				comps.push(i-prev+1);
				prev = i+1;
			}
		}
		comps.push(n-prev);
		bool didWork = true;
		while(didWork) {
			didWork = false;
			stack<int> ans;
			while(!comps.empty()) {
				int i = comps.top();
				comps.pop();
				if(ans.empty())
					ans.push(i);
				else if(sz(ans) == 1) {
					int T = ans.top();
					if(T <= i) {
						didWork = true;
						ans.pop();
					}
					ans.push(i);
				}
				else {
					int mid = ans.top();
					ans.pop();
					int left = ans.top();
					ans.pop();
					if(left >= mid && i >= mid) {
						didWork = true;
						ans.push(left+i-mid);
					}
					else {
						ans.push(left);
						ans.push(mid);
						ans.push(i);
					}
				}
			}
			
			comps = ans;
			while(!ans.empty())
				ans.pop();
				
			while(!comps.empty()) {
				int i = comps.top();
				comps.pop();
				if(ans.empty())
					ans.push(i);
				else if(sz(ans) == 1) {
					int T = ans.top();
					if(T <= i) {
						didWork = true;
						ans.pop();
					}
					ans.push(i);
				}
				else {
					int mid = ans.top();
					ans.pop();
					int left = ans.top();
					ans.pop();
					if(left >= mid && i >= mid) {
						didWork = true;
						ans.push(left+i-mid);
					}
					else {
						ans.push(left);
						ans.push(mid);
						ans.push(i);
					}
				}
			}
			comps = ans;
		}
		
		int res = 0;
		while(!comps.empty()) {
			res += comps.top();
			comps.pop();
		}
		cout << res << "\n";
	}
}