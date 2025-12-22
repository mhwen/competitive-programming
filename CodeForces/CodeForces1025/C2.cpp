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

constexpr ll MAX = 1e18;

int read() {
    int res;
    cin >> res;
    return res;
}

int add(ll y) {
    assert(-MAX <= y && y <= MAX);
    cout << "add " << y << endl;
    return read();
}

int mul(ll y) {
    cout << "mul " << y << endl;
    return read();
}

int div(ll y) {
    cout << "div " << y << endl;
    return read();
}

int digit() {
    cout << "digit" << endl;
    return read();
}

int answer() {
    cout << "!" << endl;
    return read();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    ll n;
	    cin >> n;
	    mul(9);
	    digit();
	    digit();
	    add(n-9);
	    answer();
	}
}