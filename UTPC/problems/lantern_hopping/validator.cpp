#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 2e5;
constexpr int MAX_Q = 2e5;
constexpr int MAX_HEIGHT = 1e9;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int q = inf.readInt(1, MAX_Q, "q");
    inf.readEoln();
    for(int i = 0; i < n; i++) {
        inf.readInt(0, MAX_HEIGHT, "a");
        if(i < n-1)
            inf.readSpace();
        else
            inf.readEoln();
    }
    int typeOneSeen = 0;
    for(int i = 0; i < q; i++) {
        int type = inf.readInt(1, 2, "t");   
        if(type == 1) {
            inf.readSpace();
            inf.readInt(1, n, "p");
            inf.readEoln();
            typeOneSeen++;
        }
        else {
            inf.readSpace();
            inf.readInt(1, n, "p");
            inf.readSpace();
            inf.readInt(0, MAX_HEIGHT, "x");
            inf.readEoln();
        }
    }
    ensure(typeOneSeen > 0);
    inf.readEof();
}