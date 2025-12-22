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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int h, w, n;
	cin >> h >> w >> n;
	vector<set<int>> rows(h);
	vector<set<int>> cols(w);
	for(int i = 0; i < n; i++) {
	    int x, y;
	    cin >> x >> y;
	    x--; y--;
	    rows[x].insert(y);
	    cols[y].insert(x);
	}
	int q;
	cin >> q;
	while(q-->0) {
	    int type, id;
	    cin >> type >> id;
	    id--;
	    if(type == 1) {
	        cout << sz(rows[id]) << "\n";
	        for(auto col : rows[id])
	            cols[col].erase(id);
	        rows[id].clear();
	    }
	    else {
	        cout << sz(cols[id]) << "\n";
	        for(auto row : cols[id])
	            rows[row].erase(id);
	        cols[id].clear();
	    }
	}
}