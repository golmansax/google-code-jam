#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

bool is_desc(vector<int> digits) {
  int len = digits.size();
  if (len <= 1) {
    return true;
  }

  int current = digits[0];
  int index = 1;
  while (index < len) {
    if (digits[index] > current) {
      return false;
    }

    current = digits[index];
    index++;
  }

  return true;
}

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    unsigned long long n;
    cin >> n;

    vector<int> digits;
    while (n > 0) {
      digits.push_back(n % 10);
      n /= 10;
    }

    // Only run if digits not in order
    int index = 0;
    while (!is_desc(digits)) {
      if (digits[index] == 9) {
        index++;
        continue;
      }

      // Iterate through and try to modify digit
      digits[index] = 9;

      while (digits[index + 1] == 0) {
        digits[index + 1] = 9;
        index++;
      }

      digits[index + 1] -= 1;
      index++;
    }

    // Remove leading 0 if that exists
    while (*digits.rbegin() == 0) {
      digits.pop_back();
    }

    printf("Case #%d: ", i_case + 1);

    for (auto rit = digits.rbegin(); rit != digits.rend(); ++rit) {
      printf("%d", *rit);
    }

    printf("\n");
  }

  return 0;
}
