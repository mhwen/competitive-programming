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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int rootn = 320;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q, k;
		cin >> n >> q >> k;
		int rootk = 1;
		while(rootk*rootk <= k)
			rootk++;
		vector<int> nums(n);
		vector<int> component(n);
		vector<int> sign(n);
		vector<vector<int>> gBlocks(n/rootn+1, vector<int>(rootk));
		vector<vector<int>> bBlocks(n/rootn+1, vector<int>(rootk));
		
		auto getBlock = [&](int id) {
			return id/rootn;
		};
		for(int i = 0; i < n; i++) {
			cin >> nums[i];
			int block = getBlock(i);
			if(nums[i] >= rootk) {
				component[i] = k/nums[i];
				sign[i] = 1;
			}
			else {
				component[i] = nums[i];
				sign[i] = -1;
			}
			if(sign[i] == 1)
				bBlocks[block][component[i]]++;
			else
				gBlocks[block][component[i]]++;
			if(i > 0 && getBlock(i-1) != block) {
				for(int j = 0; j < rootk; j++) {
					gBlocks[block][j] += gBlocks[block-1][j];
					bBlocks[block][j] += bBlocks[block-1][j];
				}
			}
		}
		auto getCounts = [&](int l, int r) {
			int rightBlock = getBlock(r)-1;
			int leftBlock = getBlock(l)+1;
			vector<int> good(rootk);
			vector<int> bad(rootk);
			auto process = [&](int i) {
				if(sign[i] == 1)
					bad[component[i]]++;
				else
					good[component[i]]++;
			};
			
			if(rightBlock >= leftBlock) {
				for(int i = 0; i < rootk; i++) {
					good[i] += gBlocks[rightBlock][i];
					bad[i] += bBlocks[rightBlock][i];
					if(leftBlock > 0) {
						good[i] -= gBlocks[leftBlock-1][i];
						bad[i] -= bBlocks[leftBlock-1][i];
					}
				}
				for(int i = l; i < leftBlock*rootn; i++)
					process(i);
				for(int i = (rightBlock+1)*rootn; i <= r; i++)
					process(i);
			}
			else {
				for(int i = l; i <= r; i++)
					process(i);
			}
			return make_pair(good, bad);
		};
		while(q-->0) {
			int l, r;
			cin >> l >> r;
			l--; r--;
			auto counts = getCounts(l, r);
			auto good = counts.first;
			auto bad = counts.second;
			int ans = 0;
			int seen = 0;
			int free = 0;
			for(int i = 1; i < rootk; i++) {
				free += bad[i]-good[i];
				seen += good[i]+bad[i];
				while(free > 1 || (free == 1 && seen < r-l+1)) {
					free -= 2;
					ans++;
				}
			}
			cout << ans << " ";
		}
		cout << "\n";
	}
}