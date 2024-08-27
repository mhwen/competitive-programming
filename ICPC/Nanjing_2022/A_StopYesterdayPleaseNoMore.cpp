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
	int t;
	cin >> t;
	while(t-->0) {
		int n, m, k;
		cin >> n >> m >> k;
		string moves;
		cin >> moves;
		int x = 0, y = 0;
		int xMax = 0, xMin = 0, yMax = 0, yMin = 0;
		for(char c : moves) {
			if(c == 'U') {
				y--;
			}
			else if(c == 'D') {
				y++;
			}
			else if(c == 'L') {
				x--;
			}
			else {
				x++;
			}
			xMax = max(x, xMax);
			xMin = min(x, xMin);
			yMax = max(y, yMax);
			yMin = min(y, yMin);
		}
		int colLoss = xMax-xMin;
		int rowLoss = yMax-yMin;
		int newN = max(0, n-rowLoss);
		int newM = max(0, m-colLoss);
		int remaining = newN*newM;
		if(remaining < k)
			cout << 0 << "\n";
		else {
			if(remaining == 0 && remaining == k) {
				cout << n*m << "\n";
			}
			else {
				int N = max(n, m);
				vector<vector<int>> removed(4*N, vector<int>(4*N));
				x = 2*N, y = 2*N;
				removed[y][x] = 1;
				// cout << "start " << y << " " << x << endl;
				for(char c : moves) {
					// cout << "char " << c << endl; 
					//flipped directions
					if(c == 'D') {
						y--;
					}
					else if(c == 'U') {
						y++;
					}
					else if(c == 'R') {
						x--;
					}
					else {
						x++;
					}
					// cout << y << " " << x << endl;
					if(x > 0 && y > 0 && x < 4*N && y < 4*N && removed[y][x] == 0)
						removed[y][x] = 1;
				}
				// for(int r = 0; r < 4*N; r++) {
					// for(int c = 0; c < 4*N; c++) {
						// cout << removed[r][c];
					// }
					// cout << endl;
				// }
				// cout << endl;
				for(int r = 1; r < 4*N; r++) {
					for(int c = 1; c < 4*N; c++) {
						removed[r][c] += removed[r-1][c]+removed[r][c-1]-removed[r-1][c-1];
					}
				}
				// for(int r = 0; r < 4*N; r++) {
					// for(int c = 0; c < 4*N; c++) {
						// cout << removed[r][c];
					// }
					// cout << endl;
				// }
				int ans = 0;
				int originX = 2*N;
				int originY = 2*N;
				// cout << newN << " " << newM << endl;
				for(int r = 0; r < n; r++) {
					for(int c = 0; c < m; c++) {
						int leftC = originX-c;
						int topR = originY-r;
						int rightC = originX+newM-c-1;
						int bottomR = originY+newN-r-1;
						
						leftC -= xMin;
						rightC -= xMin;
						topR -= yMin;
						bottomR -= yMin;
						
						int removal = removed[bottomR][rightC] -
										removed[topR-1][rightC] -
										removed[bottomR][leftC-1] +
										removed[topR-1][leftC-1];
						// cout << r << " " << c << " remove " << removal << endl;
						if(remaining-removal == k)
							ans++;
					}
				}
				cout << ans << "\n";
			}
		}
	}
}