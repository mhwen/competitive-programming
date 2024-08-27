#include "testlib.h"
#include <vector>

using namespace std;

typedef long long ll;

constexpr int MIN_N = 1;
constexpr int MAX_N = 51;
constexpr int MIN_VAL = -1e9;
constexpr int MAX_VAL = 1e9;
constexpr ll BAD_MOD = 100000007;
constexpr ll GOOD_MOD = 1e9+7;

ll solve(vector<int> nums, ll MOD) {
    int n = (int)nums.size();
    vector<ll> dp(n);
    vector<int> len(n);
    int mxLen = 0;
    for(int i = 0; i < n; i++) {
        len[i] = 1;
        dp[i] = 1;
        for(int j = 0; j < i; j++) {
            if(nums[j] < nums[i]) {
                if(len[j]+1 > len[i]) {
                    len[i] = len[j]+1;
                    dp[i] = dp[j];
                }
                else if(len[j]+1 == len[i]) {
                    dp[i] += dp[j];
                    dp[i] %= MOD;
                }
            }
        }
        mxLen = max(mxLen, len[i]);
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        if(len[i] == mxLen) {
            ans += dp[i];
            ans %= MOD;
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {

    registerTestlibCmd(argc, argv);

    int n = ouf.readInt(MIN_N, MAX_N, "n");
    ouf.readEoln();
    vector<int> nums(n);

    for(int i = 0; i < n; i++) {
        nums[i] = ouf.readInt(MIN_VAL, MAX_VAL, "a_i");
    }

    int extraInOufCount = 0;
    while (!ouf.seekEof()) {
        ouf.readInt();
        extraInOufCount++;
    }
    if(extraInOufCount > 0) 
        quitf(_wa, "\nExpected n=%d numbers, but output contains %d numbers", n, n + extraInOufCount);

    ll buggedAns = solve(nums, BAD_MOD);
    ll ans = solve(nums, GOOD_MOD);
    
    if (buggedAns != ans)
        quitf(_ok, "\nYour test case exposed the bug!"); // This finishes checker with verdict OK.
    else
        quitf(_wa, "\nYour test case did not expose the bug.");
}