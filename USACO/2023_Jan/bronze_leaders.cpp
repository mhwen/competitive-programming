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
	string types;
	cin >> types;
	vector<int> ranges(n);
	for(int i = 0; i < n; i++) {
		cin >> ranges[i];
		ranges[i]--;
	}
	int rightG = 0, rightH = 0;
	for(int i = 0; i < n; i++) {
		if(types[i] == 'G')
			rightG = i;
		else
			rightH = i;
	}
	int leftG = n+1;
	for(int i = 0; i < n; i++) {
		if(types[i] == 'G') {
			if(ranges[i] >= rightG)
				leftG = i;
			break;
		}
	}
	int leftH = n+1;
	for(int i = 0; i < n; i++) {
		if(types[i] == 'H') {
			if(ranges[i] >= rightH)
				leftH = i;
			break;
		}
	}
	int count = 0;
	for(int i = 0; i < n; i++) {
		if(types[i] == 'G') {
			if(i < leftH && ranges[i] >= leftH)
				count++;
		}
		else {
			if(i < leftG && ranges[i] >= leftG)
				count++;
		}
	}
	if(leftG != n+1 && leftH != n+1)
		count++;
	cout << count << "\n";
	
}