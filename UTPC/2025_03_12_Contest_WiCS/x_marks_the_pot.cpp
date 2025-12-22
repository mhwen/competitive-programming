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
#include <numbers>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ld PI = acos(-1);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<int> k(n);
	vector<ll> a(n);
	vector<vector<int>> 
	for(int i = 0; i < n; i++) {
	    cin >> k[i] >> a[i];
	}
	for(int i = 0; i < n; i++) {
	    angle[i+1] = angle[i];
	    dx[i+1] = dx[i];
	    dy[i+1] = dy[i];
	    if(k[i] == 1) {
	        angle[i+1] += a[i];
	        angle[i+1] %= 360;
	    }
	    else {
	        dx[i+1] += cos((ld)angle[i]/180*PI)*a[i];
	        dy[i+1] += sin((ld)angle[i]/180*PI)*a[i];
	    }
	}
	ld xx = dx.back();
	ld yy = dy.back();
	cout << fixed << setprecision(20);
	while(q-->0) {
	    int l, r;
	    cin >> l >> r;
	    l--;
	    ld DX = dx[r]-dx[l];
	    ld DY = dy[r]-dy[l];
	    
	    ld A = (2-(ld)angle[l]/180)*PI;
	    ld X = cos(A)*DX - sin(A)*DY;
	    ld Y = cos(A)*DY + sin(A)*DX;
	    X = xx-X;
	    Y = yy-Y;

	    cout << sqrt(X*X+Y*Y) << "\n";
	}
	
}