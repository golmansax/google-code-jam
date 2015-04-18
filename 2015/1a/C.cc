#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

double angle(int u1, int u2, int v1, int v2) {
  int d1 = v1 - u1;
  int d2 = v2 - u2;
  double me = atan((double)d2/d1);

  if (d1 < 0) {
    me += M_PI;
  }
  return me;
}

bool is_left(int u1, int u2, int v1, int v2) {
  int dot = u1 * -1 * v2 + u2 * v1;
  return dot > 0;
}

void convex_hull(vector<int> &indexes, vector<int> x, vector<int> y) {
  int left_index = -1;
  int min_x = 0;

  for (int i = 0; i < x.size(); i++) {
    if (left_index == -1 || x[i] < min_x) {
      left_index = i;
      min_x = x[i];
    }
  }

  indexes.clear();
  int index_on_hull = left_index;

  do {
    indexes.push_back(index_on_hull);

    int my_x = x[index_on_hull];
    int my_y = y[index_on_hull];
    int next_index = -1;
    for (int i = 0; i < x.size(); i++) {
      if (i == index_on_hull) {
        continue;
      }
      if (next_index == -1) {
        next_index = i;
      } else {
        bool hm_im_left = is_left(
          x[i] - my_x,
          y[i] - my_y,
          x[next_index] - my_x,
          y[next_index] - my_y
        );

        if (hm_im_left) {
          next_index = i;
        }
      }
    }

    index_on_hull = next_index;
  } while (index_on_hull != indexes[0]);
}

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    int n;
    cin >> n;

    vector<int> x;
    vector<int> y;
    for (int i = 0; i < n; i++) {
      int x_t, y_t;
      cin >> x_t >> y_t;
      x.push_back(x_t);
      y.push_back(y_t);
    }

    printf("Case #%d:\n", i_case + 1);

    /*
    vector<int> hull;
    convex_hull(hull, x, y);
    */

    for (int i = 0; i < n; i++) {
      int ans = 0;

      bool found = false;
      /*
      for (int j = 0; j < hull.size(); j++) {
        if (hull[j] == i) {
          found = true;
          break;
        }
      }
      */

      if (!found) {
        int my_x = x[i];
        int my_y = y[i];

        double angles[n];
        for (int j = 0; j < n; j++) {
          if (i == j) continue;
          angles[j] = angle(my_x, my_y, x[j], y[j]);
        }

        ans = 1000000;
        for (int j = 0; j < n; j++) {
          if (i == j) continue;
          int above_ans = 0;
          int below_ans = 0;

          double my_angle = angles[j];

          for (int k = 0; k < n; k++) {
            if (i == k || k == j) continue;

            double diff = angles[k] - my_angle;
            if (diff < 0) {
              diff += 2 * M_PI;
            }

            if (diff < M_PI) {
              below_ans++;
            } else if (diff > M_PI) {
              above_ans++;
            }
          }
          //printf("%d %d\n", below_ans, above_ans);
          ans = min(ans, min(below_ans, above_ans));
        }
      }

      printf("%d\n", ans);
    }

  }

  return 0;
}
