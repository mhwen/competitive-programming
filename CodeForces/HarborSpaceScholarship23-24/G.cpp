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

constexpr ll MOD = 998244353;

int main() {
	
	vector<ll> fact(1000);
	fact[0] = 1;
	for(int i = 1; i < sz(fact); i++)
		fact[i] = fact[i-1]*i%MOD;
		
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<vector<int>> A(n, vector<int>(n));
		vector<pair<int, int>> pos(n*n);
		
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < n; c++) {
				cin >> A[r][c];
				A[r][c]--;
			}
		}
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < n; c++) {
				int num;
				cin >> num;
				num--;
				pos[num] = {r, c};
			}
		}
		
		auto dist = [&](int a, int b) {
			return (b-a+n)%n;
		};
		auto assign = [&](vector<int>& shifts, int id, int d) {
			if(shifts[id] == -1 || shifts[id] == d) {
				shifts[id] = d;
				return true;
			}
			else {
				return false;
			}
		};
		
		vector<int> rowShift(n, -1);
		vector<int> colShift(n, -1);
		set<pair<int, int>> offsets;
		bool bad = false;
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < n; c++) {
				int num = A[r][c];
				int rDist = dist(r, pos[num].first);
				int cDist = dist(c, pos[num].second);
				if(rDist != 0 && cDist != 0) {
					if(offsets.count({rDist, cDist}))
						bad = true;
					offsets.insert({rDist, cDist});
				}
				if(rDist == 0)
					if(!assign(rowShift, r, cDist))
						bad = true;
				if(cDist == 0)
					if(!assign(colShift, c, rDist))
						bad = true;
			}
		}
		
		for(int r = 0; r < n; r++)
			if(rowShift[r] == -1)
				rowShift[r] = 0;
		
		for(int c = 0; c < n; c++)
			if(colShift[c] == -1)
				colShift[c] = 0;
		
		vector<vector<int>> con(2*n);
		vector<int> inDegree(2*n);
		
		auto rowToCol = [&](int a, int b) {
			if(rowShift[a] != 0 && colShift[b] != 0) {
				con[a].push_back(b+n);
				inDegree[b+n]++;
			}
		};
		auto colToRow = [&](int a, int b) {
			if(colShift[a] != 0 && rowShift[b] != 0) {
				con[a+n].push_back(b);
				inDegree[b]++;
			}
		};
		
				
		for(int r = 0; r < n; r++) {
			for(int c = 0; c < n; c++) {
				int num = A[r][c];
				int newR = pos[num].first;
				int newC = pos[num].second;
				int rDist = dist(r, newR);
				int cDist = dist(c, newC);
				if(rDist == 0 && cDist == 0)
					continue;
				//move along row only
				else if(rDist == 0) {
					rowToCol(r, c);
					colToRow(newC, r);
				}
				//move along col only
				else if(cDist == 0) {
					colToRow(c, r);
					rowToCol(newR, c);
				}
				else {
					//move along row then col
					if(rowShift[r] == cDist && colShift[newC] == rDist) {
						rowToCol(r, c);
						rowToCol(r, newC);
						rowToCol(newR, newC);
					}
					//move along col then row
					else if(colShift[c] == rDist && rowShift[newR] == cDist) {
						colToRow(c, r);
						colToRow(c, newR);
						colToRow(newC, newR);
					}
					else
						bad = true;
				}
			}
		}
		
		if(bad) {
			cout << 0 << "\n";
			continue;
		}
		
		int needed = 0;
		vector<int> currLayer;
		for(int r = 0; r < n; r++) {
			if(rowShift[r] != 0) {
				needed++;
				if(inDegree[r] == 0)
					currLayer.push_back(r);
			}
		}
		for(int c = 0; c < n; c++) {
			if(colShift[c] != 0) {
				needed++;
				if(inDegree[c+n] == 0)
					currLayer.push_back(c+n);
			}
		}
		
		ll ways = 1;
		while(!currLayer.empty()) {
			ways = ways*fact[sz(currLayer)]%MOD;
			needed -= sz(currLayer);
			vector<int> newLayer;
			for(int curr : currLayer) {
				for(int next : con[curr]) {
					inDegree[next]--;
					if(inDegree[next] == 0)
						newLayer.push_back(next);
				}
			}
			currLayer = newLayer;
		}
		if(needed == 0)
			cout << ways << "\n";
		else
			cout << 0 << "\n";
	}
	
}