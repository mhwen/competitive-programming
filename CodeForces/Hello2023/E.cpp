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
	int n;
	cin >> n;
	vector<pair<int, int>> counts(n);
	
	function<int(int)> query1 = [&](int p) {
		cout << "? " << p+1 << " ";
		for(int i = 0; i < n; i++) {
			if(i == p)
				cout << 0;
			else
				cout << 1;
		}
		cout << endl;
		int amt;
		cin >> amt;
		return amt;
	};
	
	function<int(int, int)> query2 = [&](int p, int winner) {
		cout << "? " << p+1 << " ";
		vector<int> query(n);
		for(int i = winner; i < n; i++) {
			query[counts[i].second] = 1;
		}
		for(int i : query)
			cout << i;
		cout << endl;
		int amt;
		cin >> amt;
		return amt;
	};
	
	for(int i = 0; i < n; i++) {
		counts[i] = {query1(i), i};
	}
	sort(counts.begin(), counts.end());
	int winner = n-1;
	for(int i = n-2; i >= 0; i--) {
		int res = query2(counts[i].second, winner);
		if(res > 0)
			winner = i;
	}
	vector<int> ans(n);
	for(int i = winner; i < n; i++) {
		ans[counts[i].second] = 1;
	}
	cout << "! ";
	for(int i : ans)
		cout << i;
	cout << endl;
}