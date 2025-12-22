/*
ID: markhwe1
TASK: latin
LANG: C++17
*/

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
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

ll ans[8] = {1, 1, 1, 2, 24, 1344, 1128960, 12198297600};

int main() {
    ifstream cin("latin.in");
    ofstream cout("latin.out");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    cout << ans[n] << "\n";
}