#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <stack>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

ll query(int l, int r, vector<ll>& vals) {
	r++; l++;
	if(r < l)
		return 0;
	return (vals[r]-vals[l-1]+MOD)%MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		
		vector<ll> keep(n+1);
		vector<ll> rem(n+1);

		stack<pair<int, int>> seen;
		for(int i = 0; i < n; i++) {
			int p;
			cin >> p;
			keep[i+1] = keep[i];
			rem[i+1] = rem[i];
			
			while(!seen.empty() && seen.top().first > p)
				seen.pop();
			if(!seen.empty()) {
				int id = seen.top().second;

				ll remVal = (query(id, id, keep)+query(id, id, rem))%MOD;
				rem[i+1] += remVal;
				rem[i+1] %= MOD;
				
				ll keepVal = (query(id, i-1, keep)+query(id, id, rem))%MOD;;
				keep[i+1] += keepVal;
				keep[i+1] %= MOD;
				
			}
			else {
				keep[i+1] += (query(0, i-1, keep)+1)%MOD;
				keep[i+1] %= MOD;
			}
			seen.push({p, i});
		}
		
		cout << (query(n-1, n-1, keep)+query(n-1, n-1, rem))%MOD << "\n";
	}
}