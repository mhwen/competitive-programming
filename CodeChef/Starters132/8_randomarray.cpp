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

constexpr ll MOD = 1e9+7;

struct mint {
	ll val;
	mint() : mint(0) {}
	mint(ll v) : val(v) {
		val %= MOD;
		if(val < 0)
			val += MOD;
	}
	mint operator+(mint m2) const { return mint(val+m2.val); }
	mint operator-(mint m2) const { return mint(val-m2.val); }
	mint operator*(mint m2) const { return mint(val*m2.val); }
	mint operator/(mint m2) const { return mint(val*m2.inv().val); }
	mint operator+=(mint m2) { return *this = *this+m2; }
	mint operator-=(mint m2) { return *this = *this-m2; }
	mint operator*=(mint m2) { return *this = *this*m2; }
	mint operator/=(mint m2) { return *this = *this/m2; }
	mint pow(ll b) const {
		mint res = 1;
		mint p = *this;
		while(b > 0) {
			if(b & 1) res *= p;
			p *= p;
			b >>= 1;
		}
		return res;
	}
	mint inv() const {
		return pow(MOD-2);
	}
	friend ostream& operator<<(ostream& os, mint m) {
		return os << m.val;
	}
};


void update(int l, int r, mint val, vector<mint>& tree) {
	int n = sz(tree)/2;
	l += n;
	r += n;
	for(; l <= r; l>>=1, r>>=1) {
		if(l%2==1) {
			tree[l] += val;
			l++;
		}
		if(r%2==0) {
			tree[r] += val;
			r--;
		}
	}
}

mint query(int p, vector<mint>& tree) {
	int n = sz(tree)/2;
	p += n;
	mint res;
	while(p > 0) {
		res += tree[p];
		p >>= 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<pair<ll, int>>> arr(n);
		vector<mint> cancel(n);
		vector<int> pointer(n);
		vector<pair<ll, int>> overall;
		int id = 0;
		for(int i = 0; i < n; i++) {
			int k;
			cin >> k;
			while(k-->0) {
				ll num;
				cin >> num;
				overall.push_back({num, id});
				arr[i].push_back({num, id++});
			}
		}

		vector<pair<int, int>> arrLoc(id);
		for(int i = 0; i < n; i++) {
			sort(arr[i].begin(), arr[i].end());
			for(int j = 0; j < sz(arr[i]); j++) {
				arrLoc[arr[i][j].second] = {i, j};
			}
		}
		
		sort(overall.begin(), overall.end());
		vector<mint> tree(2*id);
		int gp = 0;
		mint ans;

		for(int i = 0; i < id; i++) {
			ll myVal = overall[i].first;
			int myId = overall[i].second;
			int myArrId = arrLoc[myId].first;
			auto& myArr = arr[myArrId];
			int& p = pointer[myArrId];
			
			while(gp < id && overall[gp].first <= myVal)
				gp++;
			while(p < sz(myArr) && myArr[p].first <= myVal)
				p++;
			
			mint myProb = query(i, tree) + mint(id).inv();
			
			myProb -= cancel[myArrId];
			
			int aboveMe = id-gp-(sz(myArr)-p);
			if(aboveMe > 0) {
				update(gp, id-1, mint(aboveMe).inv()*myProb, tree);
				cancel[myArrId] += mint(aboveMe).inv()*myProb;
			}
			ans += myProb*mint(myVal);
		}
		
		cout << ans << "\n";
		
	}
}