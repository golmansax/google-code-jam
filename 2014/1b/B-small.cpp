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
    int a, b, k;
    cin >> a >> b >> k;

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
