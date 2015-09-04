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
    int n, p;
    cin >> n >> p;

    long long big = pow(2, n);

    long long best = 0,
    int best_idx = n;

    while (1) {
      long long diff = 0;
      if (best_idx == n) diff = 1;
      else diff = pow(2, best_idx);

      if (best + diff > p) break;
      best_idx--;
    }
    long long best_ans = best + pow(2, best_idx);

    long long worst = 0,
    int worst_idx = n;

    while (1) {
      long long diff = 0;
      if (best_idx == n) diff = 1;
      else diff = pow(2, best_idx);

      if (best + diff > p) break;
      best_idx--;
    }
    long long best_ans = best + pow(2, best_idx);
    

    printf("Case #%d: %lld %lld", i_test+1, best_ans);
  }
}
