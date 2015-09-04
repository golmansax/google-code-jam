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

bool IsPalin(long long x) {
  vector<int> d;

  while (x != 0) {
    d.push_back(x % 10);
    x /= 10;
  }

  for (int i = 0; i < d.size() / 2; i++) {
    if (d[i] != d[d.size() - 1 - i]) return false;
  }
  return true;
}

#define MAX 1000
#define DEBUG false

int main() {
  int n_tests;
  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; i_test++) {
    long long a, b;
    cin >> a >> b;
    
    // find next square
    long long start = a;
    while (true) {
      long long rt = sqrt(start);
      if (rt*rt == start) break;
      start++;
    }

    long long n = sqrt(start);
    long long sq = start;
    int count = 0;
    while (sq <= b) {
      if (DEBUG) cout << n << ": " << sq << endl;
      if (IsPalin(n) && IsPalin(sq)) count++;
      n++;
      sq += (2 * n - 1);
    }

    printf("Case #%d: %d\n", i_test+1, count);
  }
}
