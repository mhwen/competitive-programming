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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll INF = 1e18;

typedef vector<vector<vector<ll>>> Info;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int L, n;
	cin >> L >> n;
	string s;
	cin >> s;
	vector<ll> c(n);
	for(int i = 0; i < n; i++)
		cin >> c[i];
	auto convolve = [&](vector<ll>& a, vector<ll>& b, int plus) {
		vector<ll> res(sz(a)+sz(b)+plus-1, INF);
		res[plus] = a[0]+b[0];
		int i = 1, j = 1;
		while(i < sz(a) || j < sz(b)) {
			int nxt = i+j-1+plus;
			if(i == sz(a)) {
				res[nxt] = res[nxt-1]+b[j]-b[j-1];
				j++;
			}
			else if(j == sz(b)) {
				res[nxt] = res[nxt-1]+a[i]-a[i-1];
				i++;
			}
			else {
				ll da = a[i]-a[i-1];
				ll db = b[j]-b[j-1];
				if(da < db) {
					res[nxt] = res[nxt-1]+da;
					i++;
				}
				else {
					res[nxt] = res[nxt-1]+db;
					j++;
				}
			}
		}
		assert(i+j-1+plus == sz(res));
		for(int h = sz(res)-2; h >= 0; h--)
			res[h] = min(res[h+1], res[h]);
		return res;
	};
	auto mooCost = [&](int i, int len) {
		assert(i+len-1 < n);
		ll cost = 0;
		if(s[i] != 'M')
			cost += c[i];
		for(int j = 1; j < len; j++)
			if(s[i+j] != 'O')
				cost += c[i+j];
		return cost;
	};
	//[0][0] = _ _
	//[1][0] = O _
	//[0][1] = _ M
	//[1][1] = O M

	//[0][0] = _ _
	//[1][0] = O _
	//[2][0] = OO _
	//[0][1] = _ M
	//[1][1] = O M
	//[2][1] = OO M
	//[0][2] = _ MO
	//[1][2] = O MO
	//[2][2] = OO MO
	function<Info(int, int, int)> solve = [&](int l, int r, int len) {
		if(r-l+1 <= len*2-1) {
			Info res = vector(len, vector<vector<ll>>(len));
			int rem = r-l+1;
			for(int pre = 0; pre < len; pre++) {
				for(int suf = 0; suf < len; suf++) {
					if(pre+suf > rem)
						continue;
					ll pCost = 0, sCost = 0;
					if(pre > 0 && s[l] != 'O')
						pCost += c[l];
					if(pre > 1 && s[l+1] != 'O')
						pCost += c[l+1];
					if(suf == 1 && s[r] != 'M')
						sCost += c[r];
					if(suf == 2 && s[r] != 'O')
						sCost += c[r];
					if(suf == 2 && s[r-1] != 'M')
						sCost += c[r-1];
					res[pre][suf].push_back(pCost+sCost);
					if(rem-pre-suf >= len) {
						ll one = INF;
						for(int i = l+pre; i+len-1 <= r-suf; i++)
							one = min(one, mooCost(i, len));
						res[pre][suf].push_back(pCost+sCost+one);
					}
				}
			}
			return res;
		}
		int mid = (l+r)/2;
		Info left = solve(l, mid, len);
		Info right = solve(mid+1, r, len);
		Info res = vector(len, vector<vector<ll>>(len));
		for(int pre = 0; pre < len; pre++) {
			for(int suf = 0; suf < len; suf++) {
				for(int lmid = 0; lmid < len; lmid++) {
					for(int rmid = 0; rmid < len; rmid++) {
						auto con = convolve(left[pre][lmid], right[rmid][suf], (lmid+rmid)/len);
						while(sz(con) > sz(res[pre][suf]))
							res[pre][suf].push_back(INF);
						while(sz(con) < sz(res[pre][suf]))
							con.push_back(INF);
						assert(sz(res[pre][suf]) == sz(con));
						for(int i = 0; i < sz(con); i++)
							res[pre][suf][i] = min(res[pre][suf][i], con[i]);
					}
				}
			}
		}
		return res;
	};

	Info ans = solve(0, n-1, L);
	for(int i = 1; i <= n/L; i++) {
		ll res = INF;
		for(int pre = 0; pre < L; pre++) {
			for(int suf = 0; suf < L; suf++) {
				if(sz(ans[pre][suf]) > i)
					res = min(res, ans[pre][suf][i]);
			}
		}
		cout << res << "\n";
	}
	
}