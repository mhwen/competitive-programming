#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <fstream>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("triangles.in");
	ofstream cout("triangles.out");
	int n;
	cin >> n;
	vector<pair<ll, ll>> points(n);
	for(int i = 0; i < n; i++) {
		cin >> points[i].first >> points[i].second;
	}
	vector<vector<int>> under(n, vector<int>(n));
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			pair<ll, ll> a = points[i];
			pair<ll, ll> b = points[j];
			if(a.first > b.first)
				swap(a, b);
			ll xDiff = b.first-a.first;
			ll yDiff = b.second-a.second;
			if(xDiff == 0)
				continue;
			
			for(int h = 0; h < n; h++) {
				pair<ll, ll> c = points[h];
				if(c.first <= a.first || c.first > b.first)
					continue;
				ll X = c.first-a.first;
				ll Y = c.second-a.second;
				if(Y*xDiff <= yDiff*X) {
					under[i][j]++;
					under[j][i]++;
				}	
			}
		}
	}
	vector<int> amounts(n);
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			for(int h = j+1; h < n; h++) {
				int a = i;
				int b = j;
				int c = h;
				if(points[a].first > points[b].first)
					swap(a, b);
				if(points[b].first > points[c].first)
					swap(b, c);
				if(points[b].first < points[a].first)
					swap(a, b);
					
				if(points[a].first == points[b].first) {
					if(points[a].second < points[b].second)
						swap(a, b);
					int amt = under[a][c]-under[b][c];
					amounts[amt]++;
					continue;
				}
				
				if(points[b].first == points[c].first) {
					if(points[c].second < points[b].second)
						swap(b, c);
					int amt = under[a][c]-under[a][b]-1;
					amounts[amt]++;
					continue;
				}
					
					
				ll xDiff = points[c].first-points[a].first;
				ll yDiff = points[c].second-points[a].second;
				ll X = points[b].first-points[a].first;
				ll Y = points[b].second-points[a].second;
				int amt;
				if(Y*xDiff < yDiff*X) {
					amt = under[a][c]-(under[a][b]+under[b][c]);
				}	
				else {
					amt = under[a][b]+under[b][c]-under[a][c]-1;
				}
				amounts[amt]++;
			}
		}
	}
	for(int i = 0; i <= n-3; i++) {
		cout << amounts[i] << "\n";
	}
}