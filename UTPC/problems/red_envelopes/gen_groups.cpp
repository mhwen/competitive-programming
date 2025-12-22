#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

constexpr int maxN = 2e5;
constexpr int maxA = 1e9;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
    int maxPow = opt<int>("pow", 1);
    bool aiWins = opt<bool>("aiWins", false);
    bool padEvens = opt<bool>("padEvens", false);
    int n = (1<<maxPow)-1;
    if(aiWins)
        n++;
    int oddsUsed = n*(n+1)/2;
    if(padEvens)
        cout << maxN << "\n";
    else
	    cout << oddsUsed << "\n";
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            if(i > 1 || j > 0)
                cout << " ";
            cout << i*2-1;
        }
    }
    if(padEvens)
        for(int i = 0; i < maxN-oddsUsed; i++)
            cout << " " << rnd.next(2, maxA)/2*2;
    cout << "\n";
}