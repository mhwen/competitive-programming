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
	map<int, int> freq;
	for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
    }
    int Xor = 0;
    for(auto [a, cnt] : freq) {
        if(a%2==1)
            Xor ^= cnt;
    }
    if(Xor)
        cout << "Ai\n";
    else
        cout << "Bo\n";
}