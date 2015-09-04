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

#define MAXSTR 10
#define DEBUG false

char GetChar(char board[4][4], int pt[2]) {
  if (DEBUG) {
    cout << "Checking " << pt[0] << "," << pt[1] << ": " << board[pt[0]][pt[1]] << endl;
  }

  return board[pt[0]][pt[1]];
}

char CheckAns(char board[4][4], int pts[4][2]) {
  char me = GetChar(board, pts[0]);

  for (int i = 1; i < 4; i++) {
    char next = GetChar(board, pts[i]);

    if (me == 'T') me = next;
    else if (next == 'T') continue;
    else if (me != next) return '\0';
  }

  if (me == '.') return '\0';

  return me;
}

int main() {
  int n_tests;
  char buf[MAXSTR + 1];
  cin >> n_tests;
  cin.getline(buf, MAXSTR); // flush newline

  for (int i_test = 0; i_test < n_tests; i_test++) {
    char board[4][4];

    for (int i = 0; i < 4; i++) {
      cin.getline(buf, MAXSTR);
      for (int j = 0; j < 4; j++) board[i][j] = buf[j];
    }
    cin.getline(buf, MAXSTR); // empty line

    // check for draw
    bool draw = true;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (board[i][j] == '.') draw = false;
        if (DEBUG) cout << board[i][j] << " ";
      }
      if (DEBUG) cout << endl;
    }

    int hor[4][2];
    int ver[4][2];
    int ld[4][2];
    int rd[4][2];
    for (int i = 0; i < 4; i++) {
      hor[i][0] = i;
      ver[i][1] = i;
      
      ld[i][0] = i;
      ld[i][1] = i;

      rd[i][0] = i;
      rd[i][1] = 3 - i;
    }

    // check diag
    char ans = CheckAns(board, ld);
    if (ans == '\0') ans = CheckAns(board, rd);

    if (ans == '\0') {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          hor[j][1] = i;
          ver[j][0] = i;
        }
        ans = CheckAns(board, hor);
        if (ans != '\0') break;
        ans = CheckAns(board, ver);
        if (ans != '\0') break;
      }
    }

    printf("Case #%d: ", i_test+1);
    if (ans == '\0') {
      if (draw) printf("Draw");
      else printf("Game has not completed");
    }
    else printf("%c won", ans);

    printf("\n");

  }
}
