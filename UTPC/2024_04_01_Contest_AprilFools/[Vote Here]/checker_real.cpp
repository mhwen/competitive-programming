#include "testlib.h"
#include <vector>

using namespace std;

typedef long long ll;

//Remember to update this
vector<string> answers{ "Passcode", 
                        "Are you a Robot?", 
                        "Working Out", 
                        ":wink:", 
                        "Prestige Hunter", 
                        "Find the Bug Week 15", 
                        "Those Who Know",
                        "Something's Fishy",
                        "Gacha Rolling",
                        "Oh It's XOR",
                        "Vote Here!"
                        };

int main(int argc, char* argv[]) {

    registerTestlibCmd(argc, argv);

    string pans = ouf.readString();

    bool found = false;
    for(string s: answers) {
        if(pans == s)
            found = true;
    }

    if (found)
        quitf(_ok, "Thanks for voting!"); // This finishes checker with verdict OK.
    else
        quitf(_wa, "Invalid problem name");
}