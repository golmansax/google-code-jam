#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main() {
  int n_tests;
  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; i_test++) {
    int n;
    cin >> n;

    string s[n];
    int index[n];
    for (int i = 0; i < n; i++) {
      cin >> s[i];
      index[i] = 0;
    }

    int ans = 0;
    bool fail = false;

    while (true) {
      bool exists_not_at_end = false;
      bool exists_at_end = false;
      for (int i = 0; i < n; i++) {
        if (index[i] != s[i].length()) {
          exists_not_at_end = true;
        } else {
          exists_at_end = true;
        }
      }

      if (exists_not_at_end && exists_at_end) {
        fail = true;
        break;
      }

      if (exists_at_end) {
        break;
      }

      char c = s[0][index[0]];
      for (int i = 1; i < n; i++) {
        if (s[i][index[i]] != c) {
          fail = true;
          break;
        }
      }

      if (fail) {
        break;
      }

      // Else get them to the end of this letter
      //cout << c << endl;

      int length[n];
      int sum = 0;
      for (int i = 0; i < n; i++) {
        length[i] = 0;
        while (s[i][index[i]] == c) {
          index[i]++;
          length[i]++;
        }
        sum += length[i];
      }

      int average = sum / n;
      int choice1 = 0;
      int choice2 = 0;
      for (int i = 0; i < n; i++) {
        choice1 += abs(length[i] - average);
        choice2 += abs(length[i] - (average + 1));
      }

      ans += min(choice1, choice2);
    }

    printf("Case #%d: ", i_test+1);
    if (fail) {
      printf("Fegla Won\n");
    } else {
      printf("%d\n", ans);
    }

  }
}
