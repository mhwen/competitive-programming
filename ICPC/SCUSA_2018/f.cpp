#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        map<string, int> counts;
        for(int i = 0; i < n; i++) {
            string s;
            int amt;
            cin >> s >> amt;
            counts[s] += amt;
        }
        vector<pair<int, string>> sorted;
        for(auto c : counts) {
            sorted.push_back({-c.second, c.first});
        }
        sort(sorted.begin(), sorted.end());
        cout << sorted.size() << "\n";
        for(auto i : sorted) {
            cout << i.second << " " << -i.first << "\n";
        }
    }
}