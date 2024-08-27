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
		int a, b;
		cin >> a >> b;
		if((a+b)%2)
			cout << "Alice\n";
		else
			cout << "Bob\n";
	}
}