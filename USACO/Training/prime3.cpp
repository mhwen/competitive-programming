/*
ID: markhwe1
TASK: prime3
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
#include <cmath>
#include <numeric>
#include <fstream>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

vector<bool> prime(1e6, true);
vector<bool> valid(1e6);

int digSum(int num) {
	int s = 0;
	while(num > 0) {
		s += num%10;
		num /= 10;
	}
	return s;
}

void solve(int sum, int n) {
	
	fill(valid.begin(), valid.end(), false);
	
	for(int i = 2; i < sz(prime); i++) {
		if(prime[i]) {
			if(10000 <= i && i < 100000 && digSum(i) == sum) {
				int hold = i;
				while(hold > 0) {
					valid[hold] = true;
					hold /= 10;
				}
			}	
		}
	}
	
	vector<string> ans;
	vector<int> square(25, -1);
	square[0] = n;
	
	auto id = [&](int r, int c) {
		if(r < 0 || c < 0)
			return 30;
		return c*5+r;
	};
	
	vector<int> rowVals(50);
	vector<int> colVals(50);
	vector<int> d1Val(50);
	vector<int> d2Val(50);
	
	auto check = [&](int row, int col) {
		int ID = id(row, col);
		int a = square[ID]+colVals[id(row, col-1)]*10;
		if(!valid[a])
			return false;
		int b = square[ID]+rowVals[id(row-1, col)]*10;
		if(!valid[b])
			return false;
		int c = -1;
		if(row == col) {
			c = square[ID]+d1Val[id(row-1, col-1)]*10;
			if(!valid[c])
				return false;
		}
		int d = -1;
		if(row+col == 4) {
			d = square[ID]+d2Val[id(row+1, col-1)]*10;
			if(!valid[d])
				return false;
		}
		
		colVals[ID] = a;
		rowVals[ID] = b;
		if(row == col)
			d1Val[ID] = c;
		if(row+col == 4)
			d2Val[ID] = d;
		
		return true;
	};
	
	
	
	auto search = [&](auto& self, int curr) {
		if(curr == 25) {
			string a = "";
			for(int r = 0; r < 5; r++) {
				for(int c = 0; c < 5; c++) {
					a += to_string(square[id(r, c)]);
				}
			}
			ans.push_back(a);
			return;
		}
		for(int digit = 0; digit < 10; digit++) {
			if(curr == 0 && digit != n)
				continue; 
			square[curr] = digit;
			if(check(curr%5, curr/5))
				self(self, curr+1);
		}
	};
	
	search(search, 0);

	if(ans.empty())
		cout << "NONE";
	else {
		sort(ans.begin(), ans.end());
		for(int i = 0; i < sz(ans); i++) {
			cout << ans[i];
		}
	}
}

int main() {

	for(int i = 2; i < sz(prime); i++) {
		if(prime[i]) {
			for(int j = i+i; j < sz(prime); j+=i) {
				prime[j] = false;
			}
		}
	}
	cout << "{\n";
	for(int sum = 0; sum <= 45; sum++) {
		for(int n = 0; n <= 9; n++) {
			cout << "\"" << sum << " " << n << "\": ";
			cout << "\"";
			solve(sum, n);
			cout << "\"," << endl;
		}
	}
	cout << "}";
}