#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>


using namespace std;

typedef __int128 ll;
constexpr ll INF = 2e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, q;
		cin >> n >> q;
		vector<vector<int>> ops;
		for(int i = 0; i < n; i++) {
			int b, x;
			cin >> b >> x;
			if(b==1) {
				if(ops.empty() || ops.back()[0] == 2)
					ops.push_back(vector<int>{b, x});
				else
					ops.back().push_back({x});
			}
			else {
				ops.push_back(vector<int>{b, x});
			}
		}
		vector<ll> lens(ops.size()+1);
		for(int i = 1; i < (int)lens.size(); i++) {
			if(ops[i-1][0] == 1) {
				lens[i] = lens[i-1]+ops[i-1].size()-1;
			}
			else {
				ll times = ops[i-1][1]+1;
				lens[i] = lens[i-1]*times;
			}
			if(lens[i] > INF)
				lens[i] = INF;
		}
		while(q-->0) {
			long long k;
			cin >> k;
			int index = 0;
			while(lens[index] < k)
				index++;
			while(true) {
				long long prevSize = (long long)lens[index-1];
				if(ops[index-1][0] == 1) {
					if(k > prevSize) {
						cout << ops[index-1][k-prevSize] << " ";
						break;
					}
				}
				else {
					k %= prevSize;
					if(k == 0)
						k = prevSize;
				}
				index--;
			}
		}
		cout << "\n";
	}
}