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

bool solve(string s) {
	
	auto alternating = [&](string t) {
		for(int i = 0; i < sz(t)/2; i++) {
			if(i < sz(t)/2-1 && t[i] == t[i+1])
				return false;
			if(t[i] != t[sz(t)-i-1])
				return false;
		}
		return true;
	};
	
	
    for(int i = 0; i < sz(s); i++) {
	    if(s[i] == ')')
	        s[i] = '(';
	    if(s[i] == ']')
	        s[i] = '[';
    }
    for(int i = 0; i < sz(s)-1; i++) {
    	if(s[i] == s[i+1]) {
    		string left = s.substr(0, 2*(i+1));
    		if(alternating(left)) {
    			if(2*(i+1) == sz(s))
    				return true;
    			string right = s.substr(2*(i+1), sz(s)-2*(i+1));
    			if(alternating(right) && left[0] != right[0])
    				return true;
    		}
    		return false;
    	}
    }
    return false;
}

// Better:
// bool solve(string s) {
// 	
// 	
    // for(int i = 0; i < sz(s); i++) {
	    // if(s[i] == ')')
	        // s[i] = '(';
	    // if(s[i] == ']')
	        // s[i] = '[';
    // }
//     
    // for(int i = 0; i < sz(s)-2; i++) {
    	// if(s[i] == s[i+1] && s[i+1] == s[i+2])
    		// return false;
    // }
//     
    // int pairs = 0;
    // for(int i = 0; i < sz(s)-1; i++) {
    	// if(s[i] == s[i+1])
    		// pairs++;
    // }
    // return pairs <= 2;
//     
// }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		if(solve(s))
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}