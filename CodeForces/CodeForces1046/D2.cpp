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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int MAX = 1e5;
	int dd = 150;
	int qq = 5424;
	int vv = 19045;
	
	int t;
	cin >> t;
	while(t-->0) {
		cout << "? " << qq;
		for(int i = 0; i < qq; i++)
			cout << " " << dd;
		cout << endl;
		int L;
		cin >> L;
		if(L == 0) {
			cout << "? " << vv;
			for(int i = 0; i < vv; i++)
				cout << " " << 1;
			cout << endl;
			int res;
			cin >> res;
			for(int i = 1; i <= 150; i++) {
				if((vv+i-1)/i == res) {
					cout << "! " << i << endl;
					break;
				}
			}
			continue;
		}
		
		auto check = [&](int w, int D, int cnt) {
			int l = 1, s = 0;
			if(D > w)
				return (int)1e9;
			for(int i = 0; i < cnt; i++) {
				if(D+s > w) {
					l++;
					s = D;
				}
				else
					s += D;
			}
			return l;
		};
		
		auto find1 = [&]() {
			int l = 1, r = MAX;
			while(l <= r) {
				int m = (l+r)/2;
				if(check(m, dd, qq) <= L)
					r = m-1;
				else
					l = m+1;
			}
			return l;
		};
		auto find2 = [&]() {
			int l = 1, r = MAX;
			while(l <= r) {
				int m = (l+r)/2;
				if(check(m, dd, qq) >= L)
					l = m+1;
				else
					r = m-1;
			}
			return r;
		};

		int lowW = find1();
		int hiW = find2();
		if(lowW >= hiW) {
			cout << "! " << lowW << endl;
			continue;
		}
		vector<int> query;
		for(int v = lowW+1; v <= hiW; v++) {
			query.pb(lowW);
			query.pb(v-lowW);
		}
		cout << "? " << sz(query);
		for(int q : query)
			cout << " " << q;
		cout << endl;
		int res;
		cin >> res;
		cout << "! " << hiW-(res-sz(query)/2) << endl;
	}
}