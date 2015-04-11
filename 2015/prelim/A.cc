#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    int max_s;
    cin >> max_s;

    string str;
    cin >> str;
    int ans = 0;
    int total = 0;

    for (int i = 0; i <= max_s; i++){
      int val = str[i] - '0';

      if (val == 0) {
        continue;
      }

      if (total < i) {
        int diff = i - total;
        ans += diff;
        total += diff;
      }

      total += val;
    }

    printf("Case #%d: %d\n", i_case + 1, ans);
  }

  return 0;
}
