#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    int num_d;
    cin >> num_d;

    vector<int> orig_vals;

    for (int i = 0; i < num_d; i++){
      int p;
      cin >> p;
      orig_vals.push_back(p);
    }

    make_heap(orig_vals.begin(), orig_vals.end());

    int ans = -1;

    for (int divisor = 2; divisor <= 3; divisor++) {
      int n_splits = 0;
      vector<int> vals(orig_vals.begin(), orig_vals.end());

      // Keep on trying to split and return if don't want to split
      while (true) {
        int old_max = vals.front();

        if (ans == -1) {
          ans = old_max;
        } else {
          ans = min(ans, old_max + n_splits);
        }

        if (old_max <= 3) {
          break;
        }

        pop_heap(vals.begin(), vals.end());
        vals.pop_back();

        int real_divisor = old_max > 8 ? divisor : 2;
        int new_val = ceil((double) old_max / real_divisor);

        vals.push_back(new_val);
        push_heap(vals.begin(), vals.end());
        vals.push_back(old_max - new_val);
        push_heap(vals.begin(), vals.end());

        n_splits++;
      }
    }

    printf("Case #%d: %d\n", i_case + 1, ans);
  }

  return 0;
}
