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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		string s;
		cin >> s;
		auto palindromes = manacher(s);
		vector<int> evenPal = palindromes[0];
		vector<int> oddPal = palindromes[1];
		vector<vector<int>> counts(n+2, vector<int>(26));
		for(int i = 0; i < n; i++) {
			for(int c = 0; c < 26; c++) {
				counts[i+2][c] = counts[i][c];
			}
			counts[i+2][s[i]-'a']++;
		}
		vector<ll> evenSums(n+2);
		vector<ll> oddSums(n+2);
		for(int i = 2; i <= n; i++) {
			evenSums[i] = evenSums[i-1];
			oddSums[i] = oddSums[i-1];
			if(i%2==0)
				evenSums[i]+=i;
			else
				oddSums[i]+=i;
		}
		while(q-->0) {
			int l, r;
			cin >> l >> r;
			r++;
			int len = r-l;
			set<int> total;
			set<int> odds;
			set<int> evens;
			for(int c = 0; c < 26; c++) {
				int oddL = l;
				if(len%2==1)
					oddL--;
				int oddCount = counts[r][c]-counts[oddL][c];
				if(oddCount > 0) {
					odds.insert(c);
					total.insert(c);
				}
				
				int evenL = l;
				if(len%2==0)
					evenL--;
				int evenCount = counts[r-1][c]-counts[evenL][c];
				if(evenCount > 0) {
					evens.insert(c);
					total.insert(c);
				}
			}
			ll res = 0;
			if((int)total.size() > 1) {
				res += evenSums[len-1];
			}
			if((int)odds.size() > 1 || (int)evens.size() > 1) {
				res += oddSums[len-1];
			}
			int center = l+len/2-1;
			if(len%2==0 && evenPal[center] < len/2)
				res += len;
			if(len%2==1 && oddPal[center] < len/2)
				res += len;
			cout << res << "\n";
		}
		
	}
}