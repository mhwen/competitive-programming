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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> l(n);
		vector<int> r(n);
		vector<int> p(2*n+5);
		map<int, int> cnt;
		for(int i = 0; i < n; i++) {
			cin >> l[i] >> r[i];
			if(l[i] == r[i]) {
				cnt[l[i]]++;
				p[l[i]] = 1;
			}
		}
		for(int i = 1; i < sz(p); i++)
			p[i] += p[i-1];
		for(int i = 0; i < n; i++) {
			if(l[i] == r[i]) {
				if(cnt[l[i]] == 1)
					cout << "1";
				else
					cout << "0";
			}
			else {
				if(p[r[i]]-p[l[i]-1] == r[i]-l[i]+1)
					cout << "0";
				else
					cout << "1";
			}
		}
		cout << "\n";
	}
}