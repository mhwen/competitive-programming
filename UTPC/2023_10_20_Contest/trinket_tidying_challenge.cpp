#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	int currBag = 0;
	int count = 0;
	for(int i = 0; i < n; i++) {
		int num;
		cin >> num;
		if(num <= currBag)
			currBag -= num;
		else {
			count++;
			currBag = k-num;
		}
	}
	cout << count << "\n";
}