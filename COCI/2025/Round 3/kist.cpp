#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    int R = n/2, C = n/2;
    string s;
    cin >> s;
    for(char ch : s) {
        if(ch == 'U') {
            if(R > 0)
                R--;
        }
        else if(ch == 'D') {
            if(R < n-1)
                R++;
        }
        else if(ch == 'R') {
            if(C < n-1)
                C++;
        }
        else if(ch == 'L') {
            if(C > 0)
                C--;
        }
        else {
            for(int r = 0; r < n; r++) {
                for(int c = 0; c < n; c++) {
                    if(abs(r-R)+abs(c-C) < k)
                        grid[r][c] = ch;
                }
            }
        }
    }
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            cout << grid[r][c];
        }
        cout << "\n";
    }
}