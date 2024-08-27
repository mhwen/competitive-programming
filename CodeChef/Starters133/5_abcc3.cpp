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
		vector<int> nextA(n+1);
		vector<int> nextB(n+1);
		nextB[n] = nextA[n] = n;
		vector<int> cCount(n+1);
		int a = n, b = n, c = 0;
		for(int i = n-1; i >= 0; i--) {
			if(s[i] == 'a')
				a = i;
			if(s[i] == 'b')
				b = i;
			if(s[i] == 'c')
				c++;
			nextA[i] = a;
			nextB[i] = b;
			cCount[i] = c;
		}
		int best = cCount[0];
		int aSeen = 0;
		for(int i = 0; i < n; i++) {
			best = min(best, aSeen+cCount[nextB[nextA[i]]]);
			if(s[i] == 'a')
				aSeen++;
		}
		best = min(best, aSeen);
		cout << best << "\n";
	}
}

//abccabcaaaaabc
//aabaabaabaabccc