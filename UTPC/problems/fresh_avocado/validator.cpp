#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 1e5;
constexpr int MAX = 1e4;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int r = inf.readInt(1, MAX, "r");
    inf.readEoln();
    for(int i = 1; i <= n; i++) {
        int A = inf.readInt(-MAX, MAX, "A");
        inf.readSpace();
        int B = inf.readInt(-MAX, MAX, "B");
        inf.readSpace();
        int C = inf.readInt(-MAX, MAX, "C");
        inf.readEoln();
        ensure(A != 0 || B != 0);
        ensure(C*C < (long long)r*r*(A*A+B*B));
    }
    inf.readEof();
}