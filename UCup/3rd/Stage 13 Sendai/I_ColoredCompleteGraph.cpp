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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

char query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    char res;
    cin >> res;
    return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<pair<int, int>> redAns;
	vector<pair<int, int>> blueAns;
	vector<int> red;
	vector<int> blue;
	for(int i = 2; i <= n; i++) {
	    if(query(1, i) == 'R') {
	        redAns.push_back({1, i});
	        red.push_back(i);
	    }
	    else {
	        blueAns.push_back({1, i});
	        blue.push_back(i);
	    }
	}
	int r = 0, b = 0;
	while(r < sz(red) && b < sz(blue)) {
	    if(query(red[r], blue[b]) == 'R') {
	        redAns.push_back({red[r], blue[b]});
	        b++;
	    }
	    else {
	        blueAns.push_back({blue[b], red[r]});
	        r++;
	    }
	}
	cout << "!" << endl;
	if(b == sz(blue)) {
	    for(auto [x,y] : redAns)
	        cout << x << " " << y << endl;
	}
	else {
	    for(auto [x,y] : blueAns)
	        cout << x << " " << y << endl;
	}
}