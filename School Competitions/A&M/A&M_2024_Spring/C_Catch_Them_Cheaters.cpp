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
	if(n == 1) {
		cout << "1\nA\n";
	}
	else {
		cout << n/2 << "\n";
		int id = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n/2; j++) {
				cout << (char)('A'+id);
				id++;
				id %= n;
			}
			cout << "\n";
		}
	}

}