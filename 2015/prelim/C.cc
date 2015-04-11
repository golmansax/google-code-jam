#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

// int 1 -> 1, 2 -> i, 3 -> j, 4 -> k
int convert(char c) {
  if (c == '1') return 1;
  else if (c == 'i') return 2;
  else if (c == 'j') return 3;
  else return 4;
}

int mult(int a, int b) {
  if (a < 0) return -1 * mult(-1 * a, b);
  if (b < 0) return -1 * mult(a, -1 * b);

  if (a == 1) return b;
  if (b == 1) return a;
  if (a == b) return -1;
  if (a == 2) {
    if (b == 3) return 4;
    else return -3;
  } else if (a == 3) {
    if (b == 2) return -4;
    else return 2;
  } else {
    if (b == 2) return 3;
    else return -2;
  }
}

int main() {
  int n_cases;
  cin >> n_cases;

  int ijk = mult(2, mult(3, 4));

  for (int i_case = 0; i_case < n_cases; i_case++) {
    int l, x;
    cin >> l >> x;

    string str;
    cin >> str;

    int product = 1;
    for (int a = 0; a < str.size() * x; a++) {
      product = mult(product, convert(str[a % l]));
    }

    bool possible = false;
    if (product == ijk) {
      int a_product = 1; // try to get this to be i
      for (int a = 0; a < str.size() * x; a++) {
        a_product = mult(a_product, convert(str[a % l]));
        if (a_product != 2) continue;

        int b_product = 1;
        for (int b = a + 1; b < str.size() * x; b++) {
          b_product = mult(b_product, convert(str[b % l]));
          if (b_product == 3) {
            possible = true;
            break;
          }
        }

        if (possible) break;
      }
    }

    printf("Case #%d: %s\n", i_case + 1, possible ? "YES" : "NO");
  }

  return 0;
}
