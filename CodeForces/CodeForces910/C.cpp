#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, k;
		cin >> n >> m >> k;
		if(k < n+m-2 || (n+m)%2!=k%2)
			cout << "NO\n";
		else {
			cout << "YES\n";
			vector<vector<char>> rows(n, vector<char>(m-1));
			
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m-1; j++) {
					if(j%2)
						rows[i][j] = 'B';
					else
						rows[i][j] = 'R';
				}
			}
			
			vector<vector<char>> cols(n-1, vector<char>(m));
			for(int i = 0; i < n-1; i++) {
				for(int j = 0; j < m; j++) {
					if((i+m)%2)
						cols[i][j] = 'R';
					else
						cols[i][j] = 'B';
				}
			}
			rows[1][0] = 'B';
			cols[0][0] = cols[0][1] = 'R';
			
			rows[n-2][m-2] = rows[n-1][m-2] = cols[n-3][m-1];
			cols[n-2][m-2] = cols[n-2][m-1];
			
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m-1; j++) {
					cout << rows[i][j] << " ";
				}
				cout << "\n";
			}
			
			for(int i = 0; i < n-1; i++) {
				for(int j = 0; j < m; j++) {
					cout << cols[i][j] << " ";
				}
				cout << "\n";
			}
			
		}
	}
}