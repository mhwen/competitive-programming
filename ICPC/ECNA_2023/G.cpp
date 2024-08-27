
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k; 
    cin >> n >> m >> k;
    vector<pair<int, int>> vp;

    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        vp.push_back({l, r});
    }
    vector<pair<int, int>> rbt;
    vector<vector<int>> grid(2005, vector<int>(2005));
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        rbt.push_back({l, r});
        if(r == 0 && l == 0) {
        	cout << "Impossible\n";
        	return 0;
        }
        grid[l + 1001][r + 1001] = 1;
    }
    vector<pair<int, int>> sols;
    for(int i = 0; i < n; i++) {
    	//north
    	int rx = vp[i].first - rbt[0].first;
        int ry = vp[i].second - rbt[0].second;
        int hit = 0;
        for (int j = 0; j < n; j++) {
            if (abs(vp[j].first - rx) + abs(vp[j].second - ry) <= k) {
                int relax = vp[j].first - rx;
                int relay = vp[j].second - ry;
                if (grid[relax + 1001][relay + 1001]) {
                    hit++;
                }
                else
                	hit = 1e9;
            }
        }
        if (hit == m) {
            sols.push_back({rx, ry});
        }
        
                
        //south
        rx = vp[i].first + rbt[0].first;
        ry = vp[i].second + rbt[0].second;
        hit = 0;
        for (int j = 0; j < n; j++) {
            if (abs(vp[j].first - rx) + abs(vp[j].second - ry) <= k) {
                int relax = rx - vp[j].first;
                int relay = ry - vp[j].second;
                if (grid[relax + 1001][relay + 1001]) {
                    hit++;
                }
                else
                	hit = 1e9;
            }
        }
        if (hit == m) {
            sols.push_back({rx, ry});
        }
        
        
        //east
        rx = vp[i].first - rbt[0].second;
        ry = vp[i].second + rbt[0].first;
        hit = 0;
        for (int j = 0; j < n; j++) {
            if (abs(vp[j].first - rx) + abs(vp[j].second - ry) <= k) {
                int relax = ry - vp[j].second;
                int relay = vp[j].first - rx;
                if (grid[relax + 1001][relay + 1001]) {
                    hit++;
                }
                else
                	hit = 1e9;
            }
        }
        if (hit == m) {
            sols.push_back({rx, ry});
        }
        
        //west
        rx = vp[i].first + rbt[0].second;
        ry = vp[i].second - rbt[0].first;
        hit = 0;
        for (int j = 0; j < n; j++) {
            if (abs(vp[j].first - rx) + abs(vp[j].second - ry) <= k) {
                int relax = vp[j].second - ry;
                int relay = rx - vp[j].first;
                if (grid[relax + 1001][relay + 1001]) {
                    hit++;
                }
                else
                	hit = 1e9;
            }
        }
        if (hit == m) {
            sols.push_back({rx, ry});
        }
        
    }
        
    if (sols.size() == 0) {
        cout << "Impossible\n";
    }
    if (sols.size() >= 2) {
        cout << "Ambiguous\n";
    }
    if (sols.size() == 1) {
        cout << sols[0].first << " " << sols[0].second << endl;
    }
}