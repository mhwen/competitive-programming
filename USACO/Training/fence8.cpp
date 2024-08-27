/*
ID: markhwe1
TASK: fence8
LANG: C++17
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>
#include <fstream>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ofstream cout("fence8.out");
    ifstream cin("fence8.in");
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> boards(n);
	int bSum = 0;
	for(int i = 0; i < n; i++) {
		cin >> boards[i];
		bSum += boards[i];
	}
	int r;
	cin >> r;
	vector<int> rails(r);
	for(int i = 0; i < r; i++)
		cin >> rails[i];
	sort(boards.rbegin(), boards.rend());
	sort(rails.begin(), rails.end());
	rails.push_back(100000000);
	
	function<bool(int, int, int)> search = [&](int bid, int rid, int rem) {
		if(rid < 0)
			return true;
			
		int usableSum = 0;
		for(int i = 0; i < n; i++) {
			if(boards[i] >= rails[0])
				usableSum += boards[i];
		}
		if(usableSum < rem)
			return false;
			
		int rail = rails[rid];
		int start = 0;
		if(rails[rid] == rails[rid+1])
			start = bid;
		bool found = false;
		for(int i = start; i < n; i++) {
			if(boards[i] == rail) {
				boards[i] -= rail;
				found |= search(0, rid-1, rem-rail);
				boards[i] += rail;
				if(found)
					return true;
				return false;
			}
		}
		for(int i = start; i < n; i++) {
			if(boards[i] >= rail) {
				if(i > 0 && boards[i] == boards[i-1])
					continue;
				boards[i] -= rail;
				found |= search(0, rid-1, rem-rail);
				boards[i] += rail;
				if(found)
					return true;
			}
		}
		return false;
	};
	
	auto check = [&](int R) {
		int sum = 0;
		for(int i = 0; i < R; i++)
			sum += rails[i];
		return search(0, R-1, sum);
	};
	
	
	int left = 1, right = r;
	while(left <= right) {
		int mid = (left+right)/2;
		if(check(mid))
			left = mid+1;
		else
			right = mid-1;
	}
	cout << right << "\n";
}