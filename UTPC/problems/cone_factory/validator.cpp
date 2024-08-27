#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 1e5;
constexpr int MAX_M = 1e5;
constexpr int LEN = 1e6;
constexpr int MAX_HEIGHT = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAX_M, "m");
    inf.readEoln();
    for(int i = 0; i < n; i++) {
        inf.readInt(1, LEN, "p_"+to_string(i+1));
        if(i < n-1)
            inf.readSpace();
        else
            inf.readEoln();
    }
    for(int i = 0; i < m; i++) {
        inf.readInt(1, LEN, "l_"+to_string(i+1));
        inf.readSpace();
        inf.readInt(1, LEN, "r_"+to_string(i+1));
        inf.readSpace();
        inf.readInt(1, MAX_HEIGHT, "h_"+to_string(i+1));
        inf.readEoln();
    }
    inf.readEof();
}