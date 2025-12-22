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

constexpr int MX = 250000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    ll cost = 0;
    int adds = 0;
    int lastMove = MX+5;
    vector<pair<int, int>> ans;
    auto move = [&](int pos, int amt) {
        if(pos > lastMove) {
            adds++;
            cost += 1000;
        }
        cost += amt;
        lastMove = pos;
        ans.pb({pos, amt});
    };
    
    // auto simulate = [&](int v) {
        // for(auto [p, l] : ans) {
            // if(v == p)
                // v += l;
        // }
        // return v >= MX;
    // };
    
    auto compress = [&](int step, int blockSize) {
        int blocks = MX/blockSize/step;
        for(int i = 1; i < blockSize; i++) {
            vector<int> moves;
            for(int j = 0; j < blocks; j++) {
                int coord = (j*blockSize+i)*step;
                moves.pb(coord);
            }
            reverse(all(moves));
            for(auto j : moves)
                move(j, step);
        }
    };
    compress(1, 100);
    compress(100, 50);
    for(int v = 5000; v < MX; v+=5000)
        move(v, 5000);
    // for(int i = 1; i < 500; i++)
        // assert(simulate(rand()%MX+1));
    assert(cost <= 1000000);
    cout << sz(ans) << "\n";
    for(auto [p, l] : ans)
        cout << p << " " << l << "\n";
}