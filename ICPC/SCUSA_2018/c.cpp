#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t; 
    while (t-->0) {
        string a, b;
        cin >> a >> b;
        bool found = false;
        for(int len = min((int)a.size(), (int)b.size()); len > 0; len--) {
            set<vector<int>> bSeen;
            vector<int> bFreq(26);
            for(int j = 0; j < len-1; j++) {
                bFreq[b[j]-'a']++;
            }
            for(int j = len-1; j < (int)b.length(); j++) {
                bFreq[b[j]-'a']++;
                if(j >= len) {
                    bFreq[b[j-len]-'a']--;
                }
                bSeen.insert(bFreq);
            }
            vector<int> aFreq(26);
            for(int i = 0; i < len-1; i++) {
                aFreq[a[i]-'a']++;
            }
            for(int i = len-1; i < (int)a.size(); i++) {
                aFreq[a[i]-'a']++;
                if(i >= len) {
                    aFreq[a[i-len]-'a']--;
                }
                if(bSeen.count(aFreq)) {
                    found = true;
                    string s;
                    for(int h = 0; h < len; h++) {
                        s += a[i-len+1+h];
                    }
                    cout << s << "\n";
                    break;
                }
            }
            if(found)
                break;
        }
        if(!found)
            cout << "NONE\n";
    }
    
}