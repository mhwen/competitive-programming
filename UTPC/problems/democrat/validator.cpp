#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 2e3;
constexpr int MAX = 1e6;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int r = inf.readInt(1, MAX, "r");
    inf.readEoln();
    set<pair<int, int>> seen;
    for(int i = 1; i <= n; i++) {
        int x = inf.readInt(-MAX, MAX, "x");
        inf.readSpace();
        int y = inf.readInt(-MAX, MAX, "y");
        inf.readEoln();
        ensure(!seen.count({x, y}));
        seen.insert({x, y});
    }
    inf.readEof();
}