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
	int odds = 0;
	int evens = 0;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		if(a%2==0)
			evens++;
		else
			odds++;
	}
	while(evens < odds) {
		odds -= 2;
		evens++;
	}
	cout << odds+min(evens,odds+1) << "\n";
}