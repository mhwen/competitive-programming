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
	int t;
	cin >> t;
	while(t-->0) {
        string a;
        string b;
        cin >> a >> b;
        
        auto getBlocks = [](string s) {
            vector<pair<int, int>> blocks;
            char prev = '0';
            int len = 1;
            for(int i = 0; i < sz(s); i++) {
                if(s[i] != prev) {
                    if(prev == '1')
                        blocks.push_back({i-1-len+1, i-1});
                    prev = s[i];
                    len = 1;
                }
                else
                    len++;
            }  
            if(prev == '1')
                blocks.push_back({sz(s)-1-len+1, sz(s)-1});
            return blocks;
        };
        auto aBlocks = getBlocks(a);
        auto bBlocks = getBlocks(b);
        bool good = true;
        ll ans = 0;
        int aId = 0;
        for(auto [l, r] : bBlocks) {
            int needed = r-l+1;
            int got = 0;
            bool spotFound = false;
            int comps = 0;
            while(aId < sz(aBlocks) && got < needed) {
                auto [aL, aR] = aBlocks[aId];
                if(got+l == aL)
                    spotFound = true;
                got += aR-aL+1;
                comps++;
                aId++;
            }
            if(got != needed) {
                good = false;
                break;
            }
            if(!spotFound) {
                if(l == 0 || r == sz(b)-1)
                    ans += comps;
                else {
                    good = false;
                    break;
                }
            }
            else
                ans += comps-1;
        }
        if(aId != sz(aBlocks))
            good = false;
        if(!good)
            ans = -1;
        cout << ans << "\n";
	}
}