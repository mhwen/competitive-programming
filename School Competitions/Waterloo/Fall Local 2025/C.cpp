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
    int k;
    cin >> k;
    vector<int> R, C;
    for(int i = 0; i < k; i++) {
        int v;
        cin >> v;
        while(v-->0)
            R.pb(i+1);
    }
    for(int i = 0; i < k; i++) {
        int v;
        cin >> v;
        while(v-->0)
            C.pb(i+1);
    }
    int rows = sz(R);
    int cols = sz(C);
    vector grid(rows, vector<int>(cols));
    for(int r = 0; r < sz(grid); r++) {
        for(int c = 0; c < sz(grid[r]); c++) {
            if(R[r] == C[c])
                grid[r][c] = R[r];
            else {
                if((r+c)%2==0)
                    grid[r][c] = R[r];
                else
                    grid[r][c] = C[c];
            }
        }
    }
    bool bad = false;
    for(int r = 0; r < rows; r++) {
        int cnt = 0;
        for(int c = 0; c < cols; c++) {
            if(grid[r][c] == R[r])
                cnt++;
        }
        if(cnt*2 <= cols)
            bad = true;
    }
    for(int c = 0; c < cols; c++) {
        int cnt = 0;
        for(int r = 0; r < rows; r++) {
            if(grid[r][c] == C[c])
                cnt++;
        }
        if(cnt*2 <= rows)
            bad = true;
    }
    if(bad) {
        cout << "NO\n";
        return 0;
    }
    
    cout << "YES\n";
    for(int r = 0; r < sz(grid); r++) {
        for(int c = 0; c < sz(grid[r]); c++) {
            cout << grid[r][c] << " ";
        }
        cout << "\n";
    }
}