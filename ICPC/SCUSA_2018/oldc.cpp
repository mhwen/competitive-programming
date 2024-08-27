#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t; 
    while (t--) {
        string str1, str2; cin >> str1 >> str2;
        int l = 0; r = str1.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            int arr[26];
            memset(arr, 0, sizeof arr);
            for (int j = 0; j < m; j++) {
                arr[str1[i] - 'a']++;
            }
            bool okok = false;
            for (int i = 0; i < str1.size() - m; i++) {
                int arr2[26];
                memset(arr2, 0, sizeof arr2);
                for (int j = 0; j < m; j++) {
                    arr2[str2[j] - 'a']++;
                }
                bool ok = true; 
                for (int l = 0; l < 26; l++) {
                    if (arr2[l] != arr[l]) {
                        ok = false;
                    }
                }
                if (ok) {
                    okok = true;
                    break;
                }
                for (int k = m; k < n; k++) {
                    arr2[str2[k - m] - 'a']--; 
                    arr2[str2[k] - 'a']++;
                    ok = true;
                    for (int l = 0; l < 26; l++) {
                        if (arr2[l] != arr[l]) {
                            ok = false;
                        }
                    }
                    if (ok) {
                        okok = true;
                        break;
                    }
                }
                arr[str1[j] - 'a']--;
                arr[str1[j + m] - 'a']++;
            }
        }
        if(okok) {
            l = m;
        }
        else {
            r = m - 1;
        }
    }
    int m = r;
            int arr[26];
            memset(arr, 0, sizeof arr);
            for (int j = 0; j < m; j++) {
                arr[str1[i] - 'a']++;
            }
            bool okok = false;
            for (int i = 0; i < str1.size() - m; i++) {
                int arr2[26];
                memset(arr2, 0, sizeof arr2);
                for (int j = 0; j < m; j++) {
                    arr2[str2[j] - 'a']++;
                }
                bool ok = true; 
                for (int l = 0; l < 26; l++) {
                    if (arr2[l] != arr[l]) {
                        ok = false;
                    }
                }
                if (ok) {
                    okok = true;
                    break;
                }
                for (int k = m; k < n; k++) {
                    arr2[str2[k - m] - 'a']--; 
                    arr2[str2[k] - 'a']++;
                    ok = true;
                    for (int l = 0; l < 26; l++) {
                        if (arr2[l] != arr[l]) {
                            ok = false;
                        }
                    }
                    if (ok) {
                        okok = true;
                        break;
                    }
                }
                arr[str1[j] - 'a']--;
                arr[str1[j + m] - 'a']++;
            }
    
}