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

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX_D 100
#define DEBUG false

int main() {
  int n_tests;
  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; i_test++) {
    int n, m;
    cin >> n >> m;
    int des[n][m];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) cin >> des[i][j];
    }

    int cut_hor[n];
    for (int i = 0; i < n; i++) {
      cut_hor[i] = 0;
      for (int j = 0; j < m; j++) {
        cut_hor[i] = MAX(cut_hor[i], des[i][j]);
        if (DEBUG) cout << "Hor cut " << i << ": " << cut_hor[i] << endl;;
      }
    }
    int cut_ver[m];
    for (int j = 0; j < m; j++) {
      cut_ver[j] = 0;
      for (int i = 0; i < n; i++) {
        cut_ver[j] = MAX(cut_ver[j], des[i][j]);
        if (DEBUG) cout << "Ver cut " << j << ": " << cut_ver[j] << endl;
      }
    }

    // check min
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (des[i][j] != MIN(cut_hor[i], cut_ver[j])) goto lose;
      }
    }

    printf("Case #%d: YES\n", i_test+1);
    continue;

   lose:
    printf("Case #%d: NO\n", i_test+1);
  }
}
