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

constexpr int SQRT = 450;
constexpr ll INF = 1e10;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		vector<ll> a(n);
		
		auto process = [&](vector<ll>& L, vector<ll>& R, int block) {
			ll mxL = -INF;
			ll mxR = -INF;
			ll res = 0;
			for(int i = block*SQRT; i < min((block+1)*SQRT, n); i++) {
				mxL = max(mxL, L[i]);
				mxR = max(mxR, R[i]);
				res = max(res, R[i]+mxL);
			}
			return pair{res, pair{mxL, mxR}};
		};
		
		auto scan = [&](vector<ll>& mL, vector<ll>& mR, vector<ll>& blocks) {
			ll mxL = -INF;
			ll res = 0;
			for(int i = 0; i < sz(mL); i++) {
				res = max(res, max(mR[i]+mxL, blocks[i]));
				mxL = max(mxL, mL[i]);
			}
			return res;
		};
		
		vector<ll> l(n);
		vector<ll> r(n);
		vector<ll> negL(n);
		vector<ll> negR(n);
		int bCnt = (n+SQRT-1)/SQRT;
		vector<ll> blocks(bCnt, -INF);
		vector<ll> mxL(bCnt, -INF);
		vector<ll> mxR(bCnt, -INF);
		vector<ll> negBlocks(bCnt, -INF);
		vector<ll> negMxL(bCnt, -INF);
		vector<ll> negMxR(bCnt, -INF);

		for(int i = 0; i < n; i++) {
			cin >> a[i];
			l[i] = i-a[i];
			r[i] = a[i]-i;
			negL[i] = i+a[i];
			negR[i] = -a[i]-i;
		}
		
		auto updateBlock = [&](vector<ll>& L, vector<ll>& R, vector<ll>& mL, vector<ll>& mR, vector<ll>& bl, int b) {
			auto [res, lr] = process(L, R, b);
			auto [LL, RR] = lr;
			bl[b] = res;
			mL[b] = LL;
			mR[b] = RR;
		};
		
		for(int i = 0; i < bCnt; i++)
			updateBlock(l, r, mxL, mxR, blocks, i);
		for(int i = 0; i < bCnt; i++)
			updateBlock(negL, negR, negMxL, negMxR, negBlocks, i);
		cout << max(scan(mxL, mxR, blocks), scan(negMxL, negMxR, negBlocks)) << "\n";
		
		while(q-->0) {
			int p;
			ll x;
			cin >> p >> x;
			p--;
			l[p] = p-x;
			r[p] = x-p;
			negL[p] = p+x;
			negR[p] = -x-p;
			updateBlock(l, r, mxL, mxR, blocks, p/SQRT);
			updateBlock(negL, negR, negMxL, negMxR, negBlocks, p/SQRT);
			cout << max(scan(mxL, mxR, blocks), scan(negMxL, negMxR, negBlocks)) << "\n";
		}
	}
}