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
    int n;
    cin >> n;
    int even = 0, odd = 0;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if(a%2==0)
            even++;
        else
            odd++;
    }
    if(n%2==1)
        cout << "Steven\n";
    else {
        if(even >= odd)
            cout << "Steven\n";
        else
            cout << "Todd\n";
    }
}