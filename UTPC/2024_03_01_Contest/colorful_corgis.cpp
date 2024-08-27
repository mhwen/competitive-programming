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
	vector<string> colors(n);
	for(int i = 0; i < n; i++) {
		cin >> colors[i];
	}
	
	auto solveSegment = [&](int left, int right) -> int {
		int count = 0;
		set<char> curr;
		for(int i = left; i <= right; i++) {
			if(curr.empty())
				count++;
			set<char> newCurr = curr;
			for(char c : colors[i])
				newCurr.insert(c);
			if((int)newCurr.size() > 2) {
				count++;
				curr.clear();
				for(char c : colors[i])
					curr.insert(c);
			}
			else {
				curr = newCurr;
			}
		}
		return count;
	};
	
	auto extendToRight = [&](set<char>& curr, int stop) -> int {
		int left = 1;
		for(char c : colors[0])
			curr.insert(c);
		for(; left <= stop; left++) {
			set<char> newCurr = curr;
			for(char c : colors[left])
				newCurr.insert(c);
			if((int)newCurr.size() > 2) {
				break;
			}
			else {
				curr = newCurr;
			}
		}
		return left;
	};
	
	auto extendToLeft = [&](set<char>& curr, int stop) -> int {
		int right = n-1;
		for(char c : colors[0])
			curr.insert(c);
		for(; right >= stop; right--) {
			set<char> newCurr = curr;
			for(char c : colors[right])
				newCurr.insert(c);
			if((int)newCurr.size() > 2) {
				break;
			}
			else {
				curr = newCurr;
			}
		}
		return right;
	};
	
	set<char> curr;
	int left1 = extendToRight(curr, n-1);
	int right1 = extendToLeft(curr, left1);
	int ans1 = solveSegment(left1, right1);
	
	curr.clear();
	int right2 = extendToLeft(curr, 0);
	int left2 = extendToRight(curr, right2);
	int ans2 = solveSegment(left2, right2);
	
	cout << 1+min(ans1, ans2) << "\n";
	
	
	
}