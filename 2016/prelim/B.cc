#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int get_num_steps(const vector<char>& correct, int size, char outcome) {
  // Find last index with bad outcome
  int last_bad_outcome = size - 1;
  while (true) {
    if (last_bad_outcome < 0) { break; }

    if (correct[last_bad_outcome] == outcome) { last_bad_outcome -= 1; }
    else { break; }
  }

  // All are good outcome
  if (last_bad_outcome < 0) { return 0; }

  return 1 + get_num_steps(correct, last_bad_outcome + 1, outcome == '+' ? '-' : '+');
}

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    string s;
    cin >> s;

    int n = s.size();
    vector<char> correct;
    for (int i = 0; i < n; i++) {
      correct.push_back(s[i]);
    }

    int ans = get_num_steps(correct, n, '+');
    printf("Case #%d: %d\n", i_case + 1, ans);
  }

  return 0;
}
