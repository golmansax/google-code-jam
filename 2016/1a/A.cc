#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <deque>

using namespace std;

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    string s;
    cin >> s;
    deque<char> d;
    d.push_front(s[0]);
    for (int i = 1; i < s.size(); i++) {
      // Compare the two deques
      deque<char> front(d);
      front.push_front(s[i]);
      deque<char> back(d);
      back.push_back(s[i]);

      bool yay_front = true;
      for (int j = 0; j < front.size(); j++) {
        if ((int)back[j] > (int)front[j]) {
          yay_front = false;
          break;
        } else if ((int)back[j] < (int)front[j]) {
          yay_front = true;
          break;
        }
      }

      if (yay_front) { d.push_front(s[i]); }
      else { d.push_back(s[i]); }
    }
    printf("Case #%d: ", i_case + 1);
    for (int i = 0; i < d.size(); i++) {
      cout << d[i];
    }
    cout << endl;
  }

  return 0;
}
