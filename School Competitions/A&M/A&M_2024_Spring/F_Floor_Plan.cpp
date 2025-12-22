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
	string s;
	cin >> s;
	vector<int> factors;
	for(int i = 1; i <= (int)s.size(); i++) {
		if((int)s.size()%i==0) {
			factors.push_back(i);
		}
	}
	
	auto getSpot = [&](int r, int c, int rows, int cols) -> char {
		return s[r*cols+c];
	};
	
	vector<int> ans;
	for(int rows : factors) {
		int cols = (int)s.size()/rows;
		bool good = true;
		for(int r = 0; r < rows; r++) {
			for(int c = 0; c < cols; c++) {
		 		if(getSpot(r, c, rows, cols) == 'T') {
		 			for(int newR = r-1; newR <= r+1; newR++) {
		 				for(int newC = c-1; newC <= c+1; newC++) {
		 					if(newR == r && newC == c)
		 						continue;
		 					if(newR < 0 || newR >= rows || newC < 0 || newC >= cols)
		 						continue;
		 					if(getSpot(newR, newC, rows, cols) == 'T') {
		 						good = false;
		 						goto A;
		 					}
		 				}
		 			}
		 		}
		 	}
		 }
		 A:
		 if(good)
		 	ans.push_back(rows);
	}
	cout << ans.size() << "\n";
	for(int a : ans) {
		cout << a << "x" << (int)s.size()/a << "\n";
	}
}