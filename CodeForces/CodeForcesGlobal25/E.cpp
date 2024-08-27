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

array<vector<int>, 2> manacher(string& s) {
	int n = (int)s.length();
	array<vector<int>, 2>p = {vector<int>(n+1), vector<int>(n)};
	for(int z = 0; z < 2; z++) {
		for(int i=0,l=0,r=0; i < n; i++) {
			int t = r-i+!z;
			if(i<r) p[z][i] = min(t, p[z][l+t]);
			int L = i-p[z][i], R = i+p[z][i]-!z;
			while (L>=1 && R+1<n && s[L-1] == s[R+1])
				p[z][i]++, L--, R++;
			if(R>r) l=L, r=R;
		}
	}
	return p;
}

bool isPalindrome(int l, int r, array<vector<int>, 2>& p) {
	int len = r-l+1;
	int center = (r+l+1)/2;
	if(len%2==0)
		return p[0][center] == len/2;
	else
		return p[1][center] == len/2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		int n = (int)s.length();
		auto res = manacher(s);
		if(!isPalindrome(0, n-1, res)) {
			cout << "YES\n";
			cout << 1 << "\n";
			cout << s << "\n";
		}
		else {
			bool found = false;
			for(int mid = 0; mid+1 < n; mid++) {
				if(!isPalindrome(0, mid, res) && !isPalindrome(mid+1, n-1, res)) {
					found = true;
					cout << "YES\n";
					cout << 2 << "\n";
					for(int i = 0; i <= mid; i++)
						cout << s[i];
					cout << " ";
					for(int i = mid+1; i < n; i++)
						cout << s[i];
					cout << "\n";
					break;
				}
			}
			if(!found)
				cout << "NO\n";
		}
	}
}