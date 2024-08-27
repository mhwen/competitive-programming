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
		int n, x, y;
		cin >> n >> x >> y;
		vector<int> points(x);
		for(int i = 0; i < x; i++)
			cin >> points[i];
		sort(points.begin(), points.end());
		points.push_back(points.front()+n);
		vector<int> evenGaps;
		vector<int> oddGaps;
		int extra = 0;
		for(int i = 0; i < x; i++) {
			int gap = points[i+1]-points[i]-1;
			if(gap > 1) {
				if(gap%2==0)
					evenGaps.push_back(gap);
				else
					oddGaps.push_back(gap);
			}		
			else if(gap == 1)
				extra++;
		}
		sort(oddGaps.begin(), oddGaps.end());
		sort(evenGaps.begin(), evenGaps.end());
		for(int gap : oddGaps) {
			int needed = gap/2;
			if(needed <= y) {
				extra += gap;
				y -= needed;
			}
			else {
				extra += y*2;
				y = 0;
				break;
			}
		}
		for(int gap : evenGaps) {
			int needed = gap/2;
			if(needed <= y) {
				extra += gap;
				y -= needed;
			}
			else {
				extra += y*2;
				y = 0;
				break;
			}
		}
		cout << x-2+extra << "\n";
	}
}