#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

void compute_digits(vector<int> &digits, long long n) {
  digits.clear();

  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
}

long long backward(vector<int> digits, long long max) {
  long long x = 0;
  for (int i = 0; i < digits.size(); i++) {
    x += max * digits[i];
    max /= 10;
  }

  return x;
}

void gosh(long long n, long long &start, long long &ans, int my_index) {
  if (start >= n) { return; }

  vector<int> start_digits;
  compute_digits(start_digits, start);

  vector<int> digits;
  compute_digits(digits, n);

  long long max = 1;
  for (int i = 0; i < digits.size() - 1; i++) {
    max *= 10;
  }

  for (; my_index < digits.size() / 2; my_index++) {
    int more_pow = digits[digits.size() - my_index - 1];

    long long compare = 0;
    long long larger_pow = max;
    long long smaller_pow = 1;
    for (int i = 0; i <= my_index - 1; i++) {
      compare += start_digits[start_digits.size() - i - 1] * smaller_pow;
      compare += start_digits[start_digits.size() - i - 1] * larger_pow;
      larger_pow /= 10;
      smaller_pow *= 10;
    }
    compare += more_pow * larger_pow;

    cout << "ORIG COMPARE " << compare << endl;
    //cout << "MORE POW " << more_pow << endl;
    if (n < compare) {
      more_pow--;
      compare -= larger_pow;
    }
    //cout << "NOW COMPARE " << compare << endl;
    //cout << "MORE POW " << more_pow << endl;

    if (more_pow < 1) {
      int largest = start_digits[start_digits.size() - 1];
      long long new_goal = 0;
      long long new_larger_pow = max;

      compute_digits(start_digits, compare);
      for (int i = 0; i < my_index; i++) {
        new_goal += start_digits[start_digits.size() - i - 1] * new_larger_pow;
        new_larger_pow /= 10;
      }
      new_goal += new_larger_pow * 10 - 1;

      if (new_goal < n) {
        printf("NEW START %lld GOAL %lld\n", start, new_goal);
        gosh(new_goal, start, ans, my_index);
      }
      return;
    }
    //cout << "COMPARE " << compare << endl;
    compute_digits(start_digits, compare);
    //cout << start << " AND " << backward(start_digits, max) << " AND " << ans << endl;
    ans += backward(start_digits, max) - start + 1;
    //cout << start << " AND " << ans << endl;
    start = compare;
  }
}

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    long long n;
    cin >> n;
    long long ans = 0;

    if (n <= 20) {
      ans = n;
    } else {
      bool found = false;

      long long start = 10;
      ans = start;
      long long pow = 2;

      while (!found) {
        if (n >= start * 10) {
          long long goal = start * 10 - 1;
          ans += 9 + 1;
          start = 9 * start + 1;
          //cout << "START " << start << endl;
          //cout << "GOAL " << goal << endl;

          gosh(goal, start, ans, 1);
          ans += goal - start + 1;
          start += goal - start + 1;
          //cout << " TWO START " << start << endl;
        } else {
          if (n == start) {
          } else {
            long long my_pow = n / start;
            if (n < my_pow * start + 1) {
              my_pow--;
            }

            if (my_pow <= 1) {
              ans += 1;
              start += 1;
            } else {
              ans += my_pow + 1;
              start = start * my_pow + 1;
            }

            gosh(n, start, ans, 1);
            //printf("LAST START %lld ANS %lld\n", start, ans);
          }

          ans += n - start;

          found = true;
        }
      }
    }

    printf("Case #%d: %lld\n", i_case + 1, ans);
  }

  return 0;
}
