#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 2e5;
constexpr int MAX_Q = 2e5;
constexpr int MAX = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int q = inf.readInt(1, MAX_Q, "q");
    inf.readEoln();
    set<pair<int, int>> p;
    for(int i = 1; i <= n; i++) {
        int x = inf.readInt(-MAX, MAX, "x");
        inf.readSpace();
        int y = inf.readInt(-MAX, MAX, "y");
        inf.readEoln();
        ensure(p.count({x, y}) == 0);
        p.insert({x, y});
    }
    for(int i = 1; i <= q; i++) {
        int A = inf.readInt(-MAX, MAX, "A");
        inf.readSpace();
        int B = inf.readInt(-MAX, MAX, "B");
        inf.readSpace();
        inf.readInt(-MAX, MAX, "C");
        inf.readEoln();
        ensure(A != 0 || B != 0);
    }
    inf.readEof();
}