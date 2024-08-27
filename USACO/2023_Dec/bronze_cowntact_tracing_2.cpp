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
	string s;
	cin >> s;
	int posMax = n;
	int left = 0;
	while(left < n && s[left] == '1')
		left++;
	int right = 0;
	while(n-1-right >= left && s[n-1-right] == '1')
		right++;
	if(left > 0)
		posMax = min(posMax, left-1);
	if(right > 0)
		posMax = min(posMax, right-1);

	vector<int> segments;
	int curr = 0;
	for(int i = left; i <= n-1-right; i++) {
		if(s[i] == '0' && curr > 0) {
			segments.push_back(curr);
			posMax = min(posMax, (curr-1)/2);
			curr = 0;
		}
		else if(s[i] == '1')
			curr++;
	}
	if(curr > 0) {
		segments.push_back(curr);
		posMax = min(posMax, curr/2);
	}
	int count = 0;
	
	// a/b
	// rounds down to nearest integer
	
	// (a+b-1)/b
	// equivalent to a/b but rounding up to nearest integer
	
	count += (left+posMax*2)/(posMax*2+1);
	count += (right+posMax*2)/(posMax*2+1);
	for(int seg : segments) {
		count += (seg+posMax*2)/(posMax*2+1);
	}
	cout << count << "\n";
		
}