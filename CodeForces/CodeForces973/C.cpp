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

int query(string val) {
	cout << "? " << val << endl;
	int res;
	cin >> res;
	return res;
}

void answer(string val) {
	cout << "! " << val << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		int res = query("0");
		if(res) {
			string curr = "0";
			bool front = true;
			while(sz(curr) < n) {
				if(front) {
					res = query(curr+"0");
					if(res)
						curr = curr+"0";
					else {
						res = query(curr+"1");
						if(res)
							curr = curr+"1";
						else
							front = false;
					}
				}
				else {
					res = query("0"+curr);
					if(res)
						curr = "0"+curr;
					else
						curr = "1"+curr;
				}
			}
			answer(curr);
		}
		else {
			string s = "";
			for(int i = 0; i < n; i++) {
				s += "1";
			}
			answer(s);
		}
		
	}
}