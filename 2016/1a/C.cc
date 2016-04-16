#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unordered_set<int> tCycle;

int main() {
  bool debug = true;
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    int n;
    cin >> n;
    int bff[n];
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      bff[i] = x - 1;
    }

    unordered_map<int, tCycle> cycles;

    // Figure out cycles for each start
    for (int i = 0; i < n; i++) {
      tCycle cycle;
      vector<int> order;
      cycle.insert(i);
      order.push_back(i);

      int next_i = bff[i];
      while (!cycle.count(next_i)) {
        cycle.insert(next_i);
        order.push_back(next_i);
        next_i = bff[next_i];
      }

      // Make sure the last one circles correctly
      if (debug) {
        cout << "  START " << order[0] << " END WITH " << order.back() << " WHO WANTED " << bff[order.back()] << endl;
      }
      int size = order.size();
      if (bff[order.back()] == order[0] ||
          (size > 1 && bff[order.back()] == order[size - 2])) {
        // Eliminate duplicate cycles
        bool add = true;
        for (int j = 0; j < i; j++) {
          if (cycles[j].size() != cycle.size()) {
            continue;
          }

          int asdf = 0;
          for (unordered_set<int>::iterator it = cycles[j].begin();
               it != cycles[j].end(); it++) {
            if (!cycle.count(*it)) {
              break;
            }
            asdf++;
          }
          if (asdf == cycle.size()) {
            add = false;
            break;
          }
        }

        if (add) { cycles[i] = cycle; }
      }
    }

    // DUMB SOLUTION yay...
    int ans = 0;
    for (int i = 0; i < pow(2, n); i++) {
      bool use[n];
      int x = i;
      for (int j = 0; j < n; j++) {
        use[j] = (x % 2 == 1);
        x /= 2;
      }

      /*
      if (debug) {
        for (int j = 0; j < n; j++) {
          cout << (use[j] ? 1 : 0) << " ";
        }
        cout << endl;
      }
      */

      tCycle used;
      bool fail = false;
      for (int j = 0; j < n; j++) {
        if (use[j]) {
          for (unordered_set<int>::iterator it = cycles[j].begin();
               it != cycles[j].end(); it++) {
            // if (debug) { cout << " try to add " << *it << endl; }
            if (used.count(*it)) {
              fail = true;
              break;
            }
            used.insert(*it);
          }
          if (fail) { break; }
        }
      }
      if (fail) { continue; }
      if (debug) {
        cout << "NO FAIL with " << used.size() << endl;
        for (int j = 0; j < n; j++) {
          if (use[j]) {
            cout << "  START WITH " << j << ": ";
            for (unordered_set<int>::iterator it = cycles[j].begin();
                 it != cycles[j].end(); it++) {
              // if (debug) { cout << " try to add " << *it << endl; }
              cout << *it << " ";
            }
            cout << endl;
          }
        }
      }

      int num_stragglers = 0;

      int new_ans = used.size() + num_stragglers;
      if (new_ans > ans) { ans = new_ans; }
    }

    printf("Case #%d: %d\n", i_case + 1, ans);
  }

  return 0;
}
