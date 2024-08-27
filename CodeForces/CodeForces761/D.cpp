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



int query(int a, int b, int c) {
	cout << "? " << a+1 << " " << b+1 << " " << c+1 << endl;
	int res;
	cin >> res;
	return res;
}

int querySeg(int seg1, int seg2, int offset) {
	vector<int> nums;
	nums.push_back(seg1*3);
	nums.push_back(seg1*3+1);
	nums.push_back(seg1*3+2);
	nums.push_back(seg2*3);
	nums.push_back(seg2*3+1);
	nums.push_back(seg2*3+2);
	return query(nums[offset], nums[offset+1], nums[offset+2]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> segments;
		vector<int> results(n);
		int goodSegment = -1, badSegment = -1;
		for(int i = 0; i < n; i+=3) {
			int res = query(i, i+1, i+2);
			segments.push_back(res);
			if(res == 0)
				badSegment = i/3;
			else
				goodSegment = i/3;
		}
		int good = -1, bad = -1;
		if(querySeg(goodSegment, badSegment, 1) == 0) {
			good = goodSegment*3;
			bad = badSegment*3;
		}
		else if(querySeg(goodSegment, badSegment, 2) == 0) {
			good = goodSegment*3+1;
			bad = badSegment*3+1;
		}
		else {
			good = goodSegment*3+2;
			bad = badSegment*3+2;
		}
		for(int i = 0; i < n/3; i++) {
			int a = i*3;
			int b = i*3+1;
			int c = i*3+2;
			if(segments[i] == 0) {
				results[a] = results[b] = results[c] = 0;
				int val = query(a, b, good)*2+query(b, c, good);
				switch(val) {
					case 1:
						results[c] = 1;
						break;
					case 2:
						results[a] = 1;
						break;
					case 3:
						results[b] = 1;
					default:
						break;
				}
			}
			else {
				results[a] = results[b] = results[c] = 1;
				int val = query(a, b, bad)*2+query(b, c, bad);
				switch(val) {
					case 0:
						results[b] = 0;
						break;
					case 1:
						results[a] = 0;
						break;
					case 2:
						results[c] = 0;
						break;
					default:
						break;
				}
			}
		}
		vector<int> ans;
		for(int i = 0; i < n; i++) {
			if(results[i] == 0)
				ans.push_back(i+1);
		}
		cout << "! " << (int)ans.size();
		for(int i : ans)
			cout << " " << i;
		cout << endl;
		
	}
}