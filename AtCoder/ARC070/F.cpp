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

char query(int a, int b) {
	cout << "? " << a << " " << b << endl;
	char res;
	cin >> res;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int a, b;
	cin >> a >> b;
	if(a <= b) {
		cout << "Impossible" << endl;
	}
	else {
		int n = a+b;
		stack<int> chain;
		for(int i = 0; i < n; i++) {
			if(chain.empty())
				chain.push(i);
			else {
				char res = query(chain.top(), i);
				if(res == 'N')
					chain.pop();
				else
					chain.push(i);
			}
		}
		int good = chain.top();
		vector<int> ans(n);
		for(int i = 0; i < n; i++) {
			char res = query(good, i);
			if(res == 'N')
				ans[i] = 0;
			else
				ans[i] = 1;
		}
		cout << "!";
		for(int i : ans)
			cout << i;
		cout << endl;
	}
}