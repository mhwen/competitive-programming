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
typedef double ld;
#define sz(x) (int)(x).size()

//12:41
//12:56

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, t;
	cin >> n >> t;
	vector<int> read(n);
	vector<int> solve(n);
	vector<ld> p(n);
	for(int i = 0; i < n; i++) {
		cin >> read[i] >> solve[i] >> p[i];
	}
	vector<vector<ld>> dp(t+1, vector<ld>(1<<n));
	dp[0][0] = 1;
	vector<vector<ld>> dist(t+1, vector<ld>(n));
	for(int time = 0; time <= t; time++) {
		if(time > 0) {
			for(int i = 0; i < n; i++) {
				dist[time][i] += dist[time-1][i];
			}
		}
		for(int mask = 0; mask < (1<<n); mask++) {
			ld tot = 0;
			ld unsolved = 0;
			for(int bit = 0; bit < n; bit++) {
				//unsolved problem
				if(!(mask&(1<<bit))) {
					tot += dist[time][bit];
					unsolved++;
				}
			}
			for(int bit = 0; bit < n; bit++) {
				if(!(mask&(1<<bit))) {
					ld chooseProb = (tot == 0) ? 1/unsolved : dist[time][bit]/tot;
					int doneRead = time+read[bit];
					int newMask = mask|(1<<bit);
					if(doneRead <= t) {
						dp[doneRead][newMask] += dp[time][mask]*chooseProb*(1-p[bit]);
					}
					int doneSolve = doneRead+solve[bit];
					if(doneSolve <= t) {
						dp[doneSolve][newMask] += dp[time][mask]*chooseProb*p[bit];
						dist[doneSolve][bit] += dp[time][mask]*chooseProb*p[bit];
					}
				}
			}
		}
	}
	cout << setprecision(20);
	for(ld l : dist[t])
		cout << l << "\n";
}