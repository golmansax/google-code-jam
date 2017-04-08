#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    vector<bool> flipped;

    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++) {
      flipped.push_back(s[i] == '+');
    }

    int k;
    cin >> k;

    int index = 0;
    bool lose = false;
    int flips = 0;
    while (index < flipped.size()) {
      if (!flipped[index]) {
        // Try flipping
        if (index + k > flipped.size()) {
          lose = true;
          break;
        }

        flips++;
        for (int i = 0; i < k; i++) {
          flipped[i + index] = !flipped[i + index];
        }
      }

      index++;
    }

    printf("Case #%d: ", i_case + 1);
    if (lose) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      printf("%d\n", flips);
    }
  }

  return 0;
}
