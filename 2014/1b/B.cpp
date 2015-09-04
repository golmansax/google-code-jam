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

#define MAX_DIGITS 32

void to_bin_array(int x, bool bin[MAX_DIGITS]) {
  int index = 0;
  while (x > 0) {
    bin[index] = (x % 2 == 1);
    x /= 2;
  }
}

int main() {
  int n_tests;
  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; i_test++) {
    int a, b, k;
    cin >> a >> b >> k;

    // Figure out a, b, k in binary
    bool a_bin[MAX_DIGITS], b_bin[MAX_DIGITS], k_bin[MAX_DIGITS];
    for (int i = 0; i < MAX_DIGITS; i++) {
      a_bin[i] = b_bin[i] = k_bin[i] = false;
    }
    to_bin_array(a, a_bin);
    to_bin_array(b, b_bin);
    to_bin_array(k, k_bin);

    int ans = 0;
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < b; j++) {
        if ((i & j) < k) {
          ans++;
        }
      }
    }

    printf("Case #%d: ", i_test+1);
    printf("%d\n", ans);
  }
}
