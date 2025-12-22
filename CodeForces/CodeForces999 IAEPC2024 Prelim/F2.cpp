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

constexpr int INF = 1e9;

struct ST {
    int n;
    vector<int> tree;
    ST(int _n) : n(_n), tree(2*n, INF) {}
    void set(int p, int val) {
        p += n;
        tree[p] = val;
        p/=2;
        while(p > 0) {
            tree[p] = min(tree[p*2], tree[p*2+1]);
            p/=2;
        }
    }
    int query(int l, int r) {
        int res = INF;
        l += n;
        r += n;
        while(l <= r) {
            if(l%2==1)
                res = min(res, tree[l++]);
            if(r%2==0)
                res = min(res, tree[r--]);
            l/=2;
            r/=2;
        }
        return res;
    }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
        string a;
        string b;
        cin >> a >> b;
        if(a.front() == '0') {
            a = "1"+a;
            b = "1"+b;
        }
        if(a.back() == '0') {
            a = a+"1";
            b = b+"1";
        }
        vector<int> one(sz(b)+1);
        vector<int> zero(sz(b)+1);
        for(int i = 0; i < sz(b); i++) {
            if(b[i] == '0')
                zero[i+1]++;
            if(b[i] == '1')
                one[i+1]++;
            zero[i+1] += zero[i];
            one[i+1] += one[i];
        }
        
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
        vector<int> aPre(sz(aBlocks)+1);
        for(int i = 0; i < sz(aBlocks); i++)
            aPre[i+1] = aPre[i]+aBlocks[i].second-aBlocks[i].first+1;
        
        // for(int i : aPre)
            // cout << i << " ";
        // cout << endl;
        
        auto getAInfo = [&](int l, int r) {
            int ones = aPre[r+1]-aPre[l];
            int len = aBlocks[r].second-aBlocks[l].first+1;
            return pair{len-ones, ones};  
        };
        
        auto fromRight = [&](int right, int type) {
            auto check = [&](int left) {
                auto [zeros, ones] = getAInfo(left, right);  
                // cout << "fromRight " << left << "-" << right << " zeros: " << zeros << " ones: " << ones << " type: " << type << endl;
                int rId = aBlocks[right].second;
                // cout << "realRange " << rId-ones+1 << "-" << rId+1 << endl;
                if(type == 1)
                    return zero[rId+1]-zero[rId-ones+1] == 0;
                else
                    return one[rId+1]-one[rId-zeros+1] == 0;
            };
            int l = 0, r = right;
            while(l <= r) {
                int mid = (l+r)/2;
                if(check(mid))
                    r = mid-1;
                else
                    l = mid+1;
            }
            return l;
        };
        auto fromLeft = [&](int left, int type) {
            auto check = [&](int right) {
                auto [zeros, ones] = getAInfo(left, right);  
                int lId = aBlocks[left].first;
                if(type == 1)
                    return zero[lId+ones]-zero[lId] == 0;
                else
                    return one[lId+zeros]-one[lId] == 0;
            };
            int l = left, r = sz(aBlocks)-1;
            while(l <= r) {
                int mid = (l+r)/2;
                if(check(mid))
                    l = mid+1;
                else
                    r = mid-1;
            }
            return r;
        };
        
        auto zerosGood = [&](int id) {
            int left = aBlocks[id].second;
            int right = aBlocks[id+1].first;
            return one[right]-one[left+1] == 0;
        };
        
        ST stay(sz(aBlocks)+1);
        ST both(sz(aBlocks)+1);
        vector<vector<int>> killStay(sz(aBlocks)+2);
        vector<vector<int>> killBoth(sz(aBlocks)+2);

        both.set(0, 0);
        for(int i = 0; i < sz(aBlocks); i++) {
            for(auto id : killStay[i])
                stay.set(id, INF);
            for(auto id : killBoth[i])
                both.set(id, INF);
            // cout << "at " << i << "--------" << endl;
            //best stay
            int l = fromRight(i, 1);
            int bestStay = min(INF, both.query(l, i)+i);
            // cout << "stay range: " << l << " " << i << endl;
            //best shift left
            l = fromRight(i, 0);
            // cout << "shift range: " << l << " " << i << endl;
            int bestShift = min(INF, stay.query(l+1, i+1)+i+1);
            // cout << "bestStay: " << bestStay << " bestShift: " << bestShift << endl;
            // cout << "right shift range " << i << " " << max(i, fromLeft(i, 0)) << endl;
            // cout << "right stay range " << i << " " << max(i, fromLeft(i, 1)) << endl;
            //cannot shift right
            killBoth[max(i, fromLeft(i, 0))+1].push_back(i);
            //cannot be shifted into
            killStay[max(i, fromLeft(i, 1))+1].push_back(i+1);
            
            stay.set(i+1, bestStay-i-1);
            
            if(i == sz(aBlocks)-1 || zerosGood(i))
                both.set(i+1, min(bestStay, bestShift)-i-1);
        }
        int res = both.query(sz(aBlocks), sz(aBlocks))+sz(aBlocks);
        if(res > sz(aBlocks)+5)
            res = -1;
        cout << res << "\n";
	}
}