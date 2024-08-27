#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef __int128 ll;
constexpr ll MOD = 3006703054056749LL;
constexpr ll P = 31;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<ll> sPre(s.length()+1);
	for(int i = 1; i <= (int)s.length(); i++) {
		sPre[i] = (sPre[i-1]*P%MOD+(s[i-1]-'a'+1))%MOD;
	}
	vector<ll> pows(2001);
	pows[0] = 1;
	for(int i = 1; i < (int)pows.size(); i++) {
		pows[i] = pows[i-1]*P%MOD;
	}
	
	set<ll> seen;
	for(int i = 1; i <= (int)s.length(); i++) {
		for(int len = 0; len <= i; len++) {
			ll del = sPre[i-len]*pows[len]%MOD;
			ll val = (sPre[i]-del+MOD)%MOD;
			seen.insert(val);
		}
	}
	
	function<bool(vector<ll>&, int)> check = [&](vector<ll>& prefix, int len) {
		for(int i = len; i < (int)prefix.size(); i++) {
			ll del = prefix[i-len]*pows[len]%MOD;
			ll val = (prefix[i]-del+MOD)%MOD;
			if(seen.count(val))
				return true;
		}
		return false;
	};
	
	for(int i = 0; i < n; i++) {
		string t;
		cin >> t;
		vector<ll> prefix(t.length()+1);
		for(int j = 1; j <= (int)t.length(); j++) {
			prefix[j] = (prefix[j-1]*P%MOD+(t[j-1]-'a'+1))%MOD;
		}
		int l = 0, r = (int)t.length(); 
		while(l <= r) {
			int mid = (l+r)/2;
			if(check(prefix, mid)) {
				l = mid+1;
			}
			else {
				r = mid-1;
			}
		}
		cout << (int)s.length()+(int)t.length()-2*r << "\n";
	}
}