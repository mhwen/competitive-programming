#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MIN_SIZE = 2;
constexpr int MAX_SIZE = 2000;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    inf.readInt(MIN_SIZE, MAX_SIZE, "N");
    inf.readSpace();
    inf.readInt(MIN_SIZE, MAX_SIZE, "M");
    inf.readEoln();
    inf.readEof();
}