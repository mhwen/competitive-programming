#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	stack<int> pos;
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		int count = 0;
		while(!pos.empty() && pos.top() < num) {
			pos.pop();
			count++;
		}
		pos.push(num);
		cout << count << "\n";
	}
	
}