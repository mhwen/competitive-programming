#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>
#include <random>
#include <chrono>

using namespace std;

typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void normalize(int x) {
	cout << "? " << x << endl;
	char res;
	cin >> res;
	if(res != '=')
		normalize(x);
}

bool lessThan(int x, int pivot) {
	cout << "? " << x << endl;
	char res;
	cin >> res;
	cout << "? " << pivot << endl;
	char _;
	cin >> _;
	return res == '<';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> assignment(n);
		vector<int> initial(n);
		iota(initial.begin(), initial.end(), 1);
		
		function<void(vector<int>, int)> solve = [&](vector<int> indices, int leftSz) {
			if((int)indices.size() <= 1) {
				for(int i : indices)
					assignment[leftSz] = i;
				return;
			}
			int pivot = (int)(rng()%indices.size());
			normalize(indices[pivot]);
			vector<int> left, right;
			for(int i = 0; i < (int)indices.size(); i++) {
				if(i == pivot)
					continue;
				if(lessThan(indices[i], indices[pivot]))
					left.push_back(indices[i]);
				else
					right.push_back(indices[i]);
			}
			solve(left, leftSz);
			assignment[leftSz+(int)left.size()] = indices[pivot];
			solve(right, leftSz+(int)left.size()+1);
		};
		
		solve(initial, 0);
		

		vector<int> ans(n);
		for(int i = 0; i < n; i++)
			ans[assignment[i]-1] = i+1;
		
		cout << "! ";
		for(int i : ans)
			cout << i << " ";
		cout << endl;
	}
}