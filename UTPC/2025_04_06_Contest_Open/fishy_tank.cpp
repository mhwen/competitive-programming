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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	cout << "o-----------------------o\n";
	for(int i = 2; i <= 14; i++) {
	    if(n > 0) {
	        cout << "|           ><>         |\n";
	        n--;
	    }
	    else
	        cout << "|                       |\n";
	}
	cout << "o-----------------------o\n";
}