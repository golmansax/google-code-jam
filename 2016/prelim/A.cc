#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    int n;
    cin >> n;

    if (n == 0) {
      printf("Case #%d: INSOMNIA\n", i_case + 1);
      continue;
    }

    unordered_set<int> digits;
    int ans;
    int curr = n;

    while (true) {
      int temp = curr;

      while (temp > 0) {
        digits.insert(temp % 10);
        temp /= 10;
      }

      if (digits.size() >= 10) {
        ans = curr;
        break;
      }

      curr += n;
    }

    printf("Case #%d: %d\n", i_case + 1, ans);
  }

  return 0;
}
