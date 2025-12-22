#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    set<int> poss;
    rep(i, 0, n) {
        poss.insert(i);
    }

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
        if (nums[i] != -1) {
            nums[i]--;
        }
        poss.erase(nums[i]);
    }

    auto check_adj = [&](int i, int x) {
        if (i > 0 && nums[i - 1] != -1) {
            if (abs(x - nums[i - 1]) == 1) {
                return false;
            }
        }
        if (i < n - 1 && nums[i + 1] != -1) {
            if (abs(x - nums[i + 1]) == 1) {
                return false;
            }
        }

        return true;
    };

    array<int, 10> idx{};
    idx.fill(-1);
    int loc = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] == -1) {
            idx[loc] = i;
            loc++;
            if (loc == 10) break;
        }
    }

    // we have some extra to fill
    if (sz(poss) > 10) {
        rep(i, 0, n) {
            // if we reached the first of the last 10 locations, break
            if (i == idx[9]) break;

            if (nums[i] == -1) {
                auto it = poss.begin();
                while (it != poss.end() && !check_adj(i, *it)) {
                    it++;
                }

                if (it != poss.end()) {
                    nums[i] = *it;
                    poss.erase(it);
                } else {
                    cout << "-1\n";
                    return 0;
                }
            }
        }
    }

    bool solved = false;

    // solve the last i
    vector<int> rem(poss.begin(), poss.end());
    do {
        bool ok = true;

        reverse(all(rem));
        rep(i, 0, loc) {
            nums[idx[i]] = rem[i];
        }

        rep(i, 0, loc) {
            if (!check_adj(idx[i], nums[idx[i]])) {
                ok = false;
                break;
            }
        }

        if (ok) {
            solved = true;
            break;
        }

        rep(i, 0, loc) {
            nums[idx[i]] = -1;
        }
        reverse(all(rem));
    } while (next_permutation(all(rem)));

    if (solved) {
        for (auto x : nums) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}