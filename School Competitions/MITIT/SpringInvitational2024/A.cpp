#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		map<tuple<int, int, int>, int> clauses;
		for(int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			a--; b--; c--;
			set<int> d;
			d.insert(a);
			d.insert(b);
			d.insert(c);
			if((int)d.size() == 1) {
				clauses[{a, -1, -1}]++;
			}
			else if((int)d.size() == 2) {
				a = *d.begin();
				b = *d.rbegin();
				clauses[{a, b, -1}]++;
			}
			else {
				clauses[{a, b, c}]++;
			}
		}
		
		bool found = false;
		vector<int> odds;
		vector<int> ans(n);
		for(auto C : clauses) {
			int a = get<0>(C.first);
			int b = get<1>(C.first);
			int c = get<2>(C.first);
			//single
			if(b == -1) {
				if(C.second%2==1) {
					ans[a] = 1;
					found = true;
					break;
				}
			}
			//double
			else if(c == -1) {
				int tot = clauses[{a, -1, -1}]+clauses[{b, -1, -1}]+C.second;
				if(tot%2==1) {
					found = true;
					ans[a] = 1;
					ans[b] = 1;
					break;
				}
			}
			//triple
			else {
				int tot = clauses[{a, -1, -1}]+clauses[{b, -1, -1}]+clauses[{c, -1, -1}];
				tot += clauses[{a, b, -1}]+clauses[{b, c, -1}]+clauses[{a, c, -1}];
				tot += C.second;
				if(tot%2==1) {
					found = true;
					ans[a] = 1;
					ans[b] = 1;
					ans[c] = 1;
					break;
				}
			}
		}
		
		if(!found)
			cout << "NO\n";
		else {
			cout << "YES\n";
			for(int i : ans)
				cout << i << " ";
			cout << "\n";
		}
	}
}