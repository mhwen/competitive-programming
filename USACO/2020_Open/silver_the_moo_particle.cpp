#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>
#include <fstream>

using namespace std;

typedef long long ll;

int main() {
	ifstream cin("moop.in");
	ofstream cout("moop.out");
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> x(n);
	vector<int> y(n);
	for(int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	vector<int> order(n);
	iota(order.begin(), order.end(), 0);
	sort(order.begin(), order.end(), [&](int a, int b) {
		if(y[a] == y[b])
			return x[b] < x[a];
		return y[b] < y[a];
	});
	int count = 0;
	int right = -2e9;
	priority_queue<int> q;
	for(int i : order) {
		if(x[i] > right) {
			count++;
			right = x[i];
			q.push(x[i]);
		}
		else {
			if(!q.empty()) {
				q.pop();
				while(!q.empty() && q.top() >= x[i])
					q.pop();
				q.push(right);
			}
		}
	}
	cout << q.size() << "\n";
}