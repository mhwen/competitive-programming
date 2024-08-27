#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr int INF = 2e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> a(n);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		multiset<int> b;
		for(int i = 0; i < m; i++) {
			int val;
			cin >> val;
			b.insert(val);
		}
		vector<int> seq;
		seq.push_back(0);
		seq.push_back(INF);
		vector<int> ans;
		for(int num : a) {
			auto it = lower_bound(seq.begin(), seq.end(), num);
			
			while(true) {
				auto bIt = b.upper_bound(*it);
				if(bIt == b.begin() || *--bIt < num)
					break;
				ans.push_back(*bIt);
				b.erase(bIt);
			}
			
			if(*it == INF)
				seq.push_back(INF);
			
			seq[it-seq.begin()] = min(seq[it-seq.begin()], num);
			
			ans.push_back(num);
		}
		auto it = b.rbegin();
		while(it != b.rend()) {
			ans.push_back(*it);
			it++;
		}
			
			
		for(int num : ans)
			cout << num << " ";
		cout << "\n";
	}
}