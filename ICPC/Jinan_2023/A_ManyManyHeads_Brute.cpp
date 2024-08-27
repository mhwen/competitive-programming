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

// bool solve(string s) {
    // for(int i = 0; i < sz(s); i++) {
        // if(s[i] == ')')
            // s[i] = '(';
        // if(s[i] == ']')
            // s[i] = '[';
    // }
// 
    // for(int i = 0; i < sz(s)-2; i++) {
        // if(s[i] == '(' && s[i+1] == '(' && s[i+2] == '(')
            // return false;
        // if(s[i] == '[' && s[i+1] == '[' && s[i+2] == '[')
            // return false;
    // }
    // set<int> a;
    // set<int> b;
    // for(int i = 0; i < sz(s)-1; i++) {
        // if(s[i] == '(' && s[i+1] == '(') {
        	// if(a.count(i%2))
        		// return false;
            // a.insert(i%2);
        // }
        // if(s[i] == '[' && s[i+1] == '[') {
        	// if(b.count(i%2))
        		// return false;
            // b.insert(i%2);
        // }
    // }
    // return true;
// }

// bool solve(string s) {
    // for(int i = 0; i < sz(s); i++) {
	    // if(s[i] == ')')
	        // s[i] = '(';
	    // if(s[i] == ']')
	        // s[i] = '[';
    // }
    // int a = 0, b = 0;
    // int aOdd = 0, aEven = 0, bOdd = 0, bEven = 0;
    // for(int i = 0; i < sz(s); i++) {
    	// if(s[i] == '(') {
    		// if(i%2==0) {
    			// if(aOdd > 1)
    				// return false;
    			// a--;
    			// if(a == -1)
    				// aEven++;
    		// }
    		// else {
    			// if(aEven > 1)
    				// return false;
    			// a++;
    			// if(a == 1)
    				// aOdd++;
    		// }
    	// }
    	// if(s[i] == '[') {
    		// if(i%2==0) {
    			// if(bOdd > 1)
    				// return false;
    			// b--;
    			// if(b == -1)
    				// bEven++;
    		// }
    		// else {
    			// if(bEven > 1)
    				// return false;
    			// b++;
    			// if(b == 1)
    				// bOdd++;
    		// }
    	// }
    // }
    // return true;
// }

// bool solve(string s) {
// 	
	// auto alternating = [&](string t) {
		// for(int i = 0; i < sz(t)/2; i++) {
			// if(i < sz(t)/2-1 && t[i] == t[i+1])
				// return false;
			// if(t[i] != t[sz(t)-i-1])
				// return false;
		// }
		// return true;
	// };
// 	
// 	
    // for(int i = 0; i < sz(s); i++) {
	    // if(s[i] == ')')
	        // s[i] = '(';
	    // if(s[i] == ']')
	        // s[i] = '[';
    // }
    // for(int i = 0; i < sz(s)-1; i++) {
    	// if(s[i] == s[i+1]) {
    		// string left = s.substr(0, 2*(i+1));
    		// if(alternating(left)) {
    			// if(2*(i+1) == sz(s))
    				// return true;
    			// string right = s.substr(2*(i+1), sz(s)-2*(i+1));
    			// if(alternating(right) && left[0] != right[0])
    				// return true;
    		// }
    		// return false;
    	// }
    // }
    // return false;
// }

bool solve(string s) {
	
	
    for(int i = 0; i < sz(s); i++) {
	    if(s[i] == ')')
	        s[i] = '(';
	    if(s[i] == ']')
	        s[i] = '[';
    }
    
    for(int i = 0; i < sz(s)-2; i++) {
    	if(s[i] == s[i+1] && s[i+1] == s[i+2])
    		return false;
    }
    
    int pairs = 0;
    for(int i = 0; i < sz(s)-1; i++) {
    	if(s[i] == s[i+1])
    		pairs++;
    }
    return pairs <= 2;
    
}


bool is_seq(const string &s) {
    vector<int> st;
    for (auto c : s) {
        if (c == '(') st.push_back(0);
        else if (c == '[') st.push_back(1);
        else if (c == ')') {
            if (st.empty() || st.back() != 0) return false;
            st.pop_back();
        } else {
            if (st.empty() || st.back() != 1) return false;
            st.pop_back();
        }
    }
    return st.empty();
}

bool brute(string s) {
    int n = sz(s);
    int cnt = 0;
    for (int i = 0; i < (1 << n); i++) {
        string cur;
        for (int j = 0; j < n; j++) {
            if (s[j] == '(' || s[j] == ')') {
                if (i & (1 << j)) {
                    cur += '(';
                } else {
                    cur += ')';
                }
            } else {
                if (i & (1 << j)) {
                    cur += '[';
                } else {
                    cur += ']';
                }
            }
        }
        if (is_seq(cur)) cnt++;
    }
    return cnt == 1;
}

string gen(int n) {
    if (n == 0) return "";
    if (n == 2) {
        if (rand() % 2 == 0) {
            return "()";
        } else {
            return "[]";
        }
    } else {
        int res = rand();
        if (res % 3 == 0) {
            return "(" + gen(n - 2) + ")";
        } else if (res % 3 == 1) {
            return "[" + gen(n - 2) + "]";
        } else {
            int sp = (rand() % (n / 2 - 1) + 1) * 2;
            return gen(sp) + gen(n - sp);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int seed = 1;
    while (true) {
        cout << seed << endl;
        srand(seed);
        auto s = gen(16);
        if (solve(s) != brute(s)) {
            cout << "broke on " << s << endl;
            cout << solve(s) << ' ' << brute(s) << endl;
            return 0;
        }
        seed++;
    }

    /*
    int t;
    cin >> t;
    while(t-->0) {
        string s;
        cin >> s;
        if (solve(s)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    */
}