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
#include <iomanip>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int l, w;
	cin >> l >> w;
	vector<vector<int>> cars(l);
	vector<int> offset(l);
	vector<int> d(l);
	vector<int> s(l);
	vector<int> dir(l); // 0 means left to right
	
	for(int i = 0; i < l; i++) {
		dir[i] = i%2;
		int off;
		cin >> off >> d[i] >> s[i];
		if(dir[i] == 0) {
			d[i] = -d[i];
		}
		else {
			s[i] = -s[i];
			off = w-1-off;
		}
		while(0 <= off-d[i] && off-d[i] < w)
			off -= d[i];
		offset[i] = off;
	}
	
	auto die = [&](int row, int time, int oldPos, int newPos) {
		//right moving cars
		if(dir[row] == 0) {
			for(int car = offset[row]; car+s[row]*time >= min(oldPos, newPos); car+=d[row]) {
				int left = car+s[row]*(time-1);
				int right = car+s[row]*time;
				if(newPos == right)
					return true;
				if(left < max(newPos, oldPos) && newPos <= right)
					return true;
			}
		}
		else {
			for(int car = offset[row]; car+s[row]*time <= max(oldPos, newPos); car+=d[row]) {
				int right = car+s[row]*(time-1);
				int left = car+s[row]*time;
				if(newPos == left)
					return true;
				if(left <= newPos && min(newPos, oldPos) < right)
					return true;
			}
		}
		return false;
	};
	int p;
	cin >> p;
	string sss;
	cin >> sss;
	int r = l, c = p;
	bool died = false;
	int time = 0;
	for(char ss : sss) {
		int newR = r;
		int newC = c;
		if(ss =='U')
			newR--;
		else if(ss == 'D')
			newR++;
		else if(ss == 'R')
			newC++;
		else
			newC--;
		time++;
		if(newR >= 0 && newR < l) {
			if(die(newR, time, c, newC)) {
				died = true;
				break;
			}
		}
		r = newR;
		c = newC;
	}
	if(!died && r == -1)
		cout << "safe\n";
	else
		cout << "squish\n";
}