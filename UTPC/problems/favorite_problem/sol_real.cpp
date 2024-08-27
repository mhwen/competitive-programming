#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

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
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int id;
	cin >> id;
    cout << answers[max(0, min((int)answers.size()-1, id-1))] << "\n";
}