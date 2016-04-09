#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <unordered_map>

using namespace std;

#define MAX_TRY 10000000

unsigned long long get_factor(unsigned long long x) {
  for (unsigned long long j = 2; j < sqrt(x); j++) {
    if (x % j == 0) { return j; }
    if (j > MAX_TRY) { return -1; }
  }

  return -1;
}

int main() {
  unordered_map<unsigned long long, unsigned long long> factors;

  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    printf("Case #%d:\n", i_case + 1);

    int n, count;
    cin >> n >> count;

    unsigned long long pows[10 - 2 + 1][n];
    for (int j = 2; j <= 10; j++) {
      unsigned long long temp_pow = 1;

      for (int k = 0; k < n; k++) {
        pows[j - 2][k] = temp_pow;
        temp_pow *= j;
      }
    }

    for (unsigned long long i = 0; i < (int)pow(2, n - 2); i++){
      // cout << "********** NEW NUM **************" << endl;
      // Get binary representation
      bool digits[n];
      digits[0] = true;
      digits[n - 1] = true;
      for (int j = 0; j < n - 2; j++) { digits[j + 1] = false; }

      unsigned long long temp = i;
      int temp_index = 1;
      while (temp > 0) {
        digits[temp_index] = (temp % 2 == 1);
        temp /= 2;
        temp_index++;
      }

      // Check 2->10
      unsigned long long ans[10 - 2 + 1];
      bool works = true;
      for (int j = 2; j <= 10; j++) {
        unsigned long long total = 0;
        for (int k = 0; k < n; k++) {
          if (digits[k]) { total += pows[j - 2][k]; }
        }
        // cout << "  trying base " << j << " and TOTAL " << total << endl;

        if (factors.find(total) == factors.end()) {
          factors[total] = get_factor(total);
        }

        if (factors.at(total) == -1) {
          works = false;
          break;
        }

        ans[j - 2] = factors.at(total);
      }

      if (works) {
        count--;

        for (int j = n - 1; j >= 0; j--) {
          cout << (digits[j] ? '1' : '0');
        }

        for (int j = 2; j <= 10; j++) {
          cout << " " << ans[j - 2];
        }
        cout << endl;
      }

      if (count == 0) { break; }
    }
  }

  return 0;
}
