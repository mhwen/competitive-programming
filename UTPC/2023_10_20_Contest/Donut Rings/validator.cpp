#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 1e5;
constexpr int MAX_RADIUS = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();
    for(int i = 0; i < n; i++) {
        int innerRadius = inf.readInt(1, MAX_RADIUS, "r_"+to_string(i+1));
        inf.readSpace();
        int outerRadius = inf.readInt(1, MAX_RADIUS, "R_"+to_string(i+1));
        inf.readEoln();
        ensure(innerRadius < outerRadius);
    }
    inf.readEof();
}