#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 2e5;
constexpr int MAX_A = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();
    for(int i = 0; i < n; i++) {
        inf.readInt(1, MAX_A, "a");
        if(i < n-1)
            inf.readSpace();
        else
            inf.readEoln();
    }
    inf.readEof();
}