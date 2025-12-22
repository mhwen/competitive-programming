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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("art.in");
	ofstream cout("art.out");
	int n;
	cin >> n;
	int colors = n*n+1;
	vector<int> loR(colors, INF), hiR(colors, -INF);
	vector<int> loC(colors, INF), hiC(colors, -INF);
	vector<bool> seen(colors);
	vector grid(n, vector<int>(n));
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			int color;
			cin >> color;
			grid[r][c] = color;
			loR[color] = min(loR[color], r);
			hiR[color] = max(hiR[color], r);
			loC[color] = min(loC[color], c);
			hiC[color] = max(hiC[color], c);
			seen[color] = true;
		}
	}
	vector pSum(n+2, vector<int>(n+2));
	for(int color = 1; color < colors; color++) {
		int r1 = loR[color]+1;
		int c1 = loC[color]+1;
		int r2 = hiR[color]+1;
		int c2 = hiC[color]+1;
		if(seen[color]) {
			pSum[r1][c1]++;
			pSum[r2+1][c1]--;
			pSum[r1][c2+1]--;
			pSum[r2+1][c2+1]++;
		}
	}
	for(int r = 1; r < sz(pSum); r++) {
		for(int c = 1; c < sz(pSum[r]); c++) {
			pSum[r][c] += pSum[r-1][c]+pSum[r][c-1]-pSum[r-1][c-1];
		}
	}
	vector<bool> good(colors, true);
	for(int r = 0; r < n; r++) {
		for(int c = 0; c < n; c++) {
			if(pSum[r+1][c+1] != 1)
				good[grid[r][c]] = false;
		}
	}
	bool onlyOneColor = accumulate(seen.begin()+1, seen.end(), 0) == 1;
	int res = accumulate(good.begin()+1, good.end(), 0);
	if(onlyOneColor)
		res--;
	cout << res << "\n";
}