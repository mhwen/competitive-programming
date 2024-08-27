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

constexpr ll MOD = 1e9+7;
constexpr ll P = 78;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q, m, k;
	cin >> n >> q >> m >> k;
	vector<string> s(n);
	for(int i = 0; i < n; i++) {
		cin >> s[i];
	}
	vector<ll> pows(m+1);
	pows[0] = 1;
	for(int i = 0; i < m; i++) {
		pows[i+1] = pows[i]*P%MOD;
	}
	vector<vector<ll>> hashes(n, vector<ll>(m+1));
	for(int i = 0; i < n; i++) {
		hashes[i][0] = 1;
		for(int j = 0; j < m; j++) {
			hashes[i][j+1] = hashes[i][j]*P + (s[i][j]-'a'+1);
			hashes[i][j+1] %= MOD;
		}
	}
	
	//get [a, b), 0-indexed
	function<ll(vector<ll>&, int, int)> getHash = [&](vector<ll>& prefix, int a, int b) {
		return (prefix[b]-(prefix[a]*pows[b-a]%MOD)+MOD)%MOD;
	};
	
	function<int(vector<ll>&, vector<ll>&, int)> getNextDiff = [&](vector<ll>& a, vector<ll>& b, int start) {
		int left = start, right = m-1;
		while(left <= right) {
			int mid = (left+right)/2;
			if(getHash(a, left, mid+1) == getHash(b, left, mid+1))
				left = mid+1;
			else
				right = mid-1;
		}
		return left;
	};
	
	function<bool(vector<ll>&, vector<ll>&)> compare = [&](vector<ll>& a, vector<ll>& b) {
		int id = -1;
		for(int i = 0; i <= k; i++) {
			id = getNextDiff(a, b, id+1);
			if(id == m)
				return true;
		}
		return false;
	};
	
	while(q-->0) {
		string t;
		cin >> t;
		vector<ll> tHash(m+1);
		tHash[0] = 1;
		for(int j = 0; j < m; j++) {
			tHash[j+1] = tHash[j]*P + (t[j]-'a'+1);
			tHash[j+1] %= MOD;
		}
		int count = 0;
		for(int i = 0; i < n; i++) {
			if(compare(hashes[i], tHash))
				count++;
		}
		cout << count << "\n";
	}
}