#include "testlib.h"
#include <vector>

using namespace std;

typedef long long ll;

//Invalidate all solutions; we don't want anyone to guess this
string answer = "iuh2g98th24og2hg08hf08hgf0e8hgew0o8ghogbhenrfiohewnogebqwougwe";

int main(int argc, char* argv[]) {

    registerTestlibCmd(argc, argv);

    string pans = ouf.readString();

    if (pans == answer)
        quitf(_ok, "How did you guess this"); // This finishes checker with verdict OK.
    else
        quitf(_wa, "This problem isn't open yet!");
}