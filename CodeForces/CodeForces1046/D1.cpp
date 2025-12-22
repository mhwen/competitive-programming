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
	int t;
	cin >> t;
	while(t-->0) {
		cout << "? " << MAX;
		for(int i = 0; i < MAX; i++)
			cout << " " << 1;
		cout << endl;
		int L;
		cin >> L;
		
		//2 ->
		//50000
		//99999
		
		//3 ->
		//33334
		//49999
		
		//4 ->
		//25000
		//33333
		auto find1 = [&]() {
			int l = 1, r = MAX;
			while(l <= r) {
				int m = (l+r)/2;
				if((MAX+m-1)/m <= L)
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
				if((MAX+m-1)/m >= L)
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