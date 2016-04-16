#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> tRow;
typedef vector<bool> tBool;

bool my_sort(const tRow& a, const tRow& b) {
  /*
  for (int i = 0; i < a.size(); i++) {
    cout << "  CMP " << a[i] << " " << b[i] << endl;
    if (a[i] == b[i]) { continue; }
    else if (a[i] < b[i]) { return true; }
    else return false;
  }
  return true;
  */
  return a[0] < b[0];
}

struct tAns {
  bool valid;
  tRow answer;
};

bool debug = false;

tAns dfs(const vector<tRow>& heap, int index, vector<tRow> board, vector<tBool> found) {
  if (index == heap.size()) {
    tAns yay;
    yay.valid = true;

    // Find answer
    tRow woo;
    for (int i = 0; i < 2; i++) {
      bool found_ans = false;
      for (int j = 0; j < board.size(); j++) {
        if (!found[i][j]) {
          if (debug) {
            cout << "ANSWER " << (i == 0 ? "ROW" : "COL") << " " << j << endl;
          }
          for (int k = 0; k < board.size(); k++) {
            if (i == 0) {
              // row
              woo.push_back(board[k][j]);
            } else {
              // col
              woo.push_back(board[j][k]);
            }
          }
          found_ans = true;
          break;
        }
      }
      if (found_ans) { break; }
    }
    yay.answer = woo;

    return yay;
  }

  tRow row = heap[index];

  // Try adding as a row
  if (true) {
    if (debug) {
      cout << "  " << index << " TRY ROW ";
      for (int i = 0; i < row.size(); i++) {
        cout << row[i] << " ";
      }
      cout << endl;
    }

    vector<tRow> board_copy = board;
    vector<tBool> found_copy = found;

    tBool my_found = found_copy[0];
    for (int i = 0; i < my_found.size(); i++) {
      if (!my_found[i]) {
        // Break if previous was also blank
        if (i > 1 && !my_found[i - 1] && !my_found[i - 2]) {
          break;
        }

        // Try to add
        if (board[0][i] != 0 && board[0][i] != row[0]) {
          // Doesn't match... breaking
          continue;
        }

        // Update and board
        bool should_break = false;
        for (int k = 0; k < board.size(); k++) {
          if (debug) { cout << "    compare " << board_copy[k][i] << " and " << row[k] << endl; }
          if (board_copy[k][i] != 0 &&
              board_copy[k][i] != row[k]) {
            should_break = true;
            break;
          }

          // Row
          board_copy[k][i] = row[k];
        }
        if (should_break) { break; }

        if (debug) {
          cout << "    MATCHED ROW " << i << endl;
        }

        // Update found
        found_copy[0][i] = true;

        tAns ans = dfs(heap, index + 1, board_copy, found_copy);
        if (ans.valid) { return ans; }
      } else if (board[0][i] >= row[0]) {
        // Already past our number
        break;
      }
    }
  }

  if (debug) {
    cout << "  " << index << " TRY COL ";
    for (int i = 0; i < row.size(); i++) {
      cout << row[i] << " ";
    }
    cout << endl;
  }

  // Try adding as a column
  tBool my_found = found[1];
  for (int i = 0; i < my_found.size(); i++) {
    if (!my_found[i]) {
      // Break if previous was also blank
      if (i > 1 && !my_found[i - 1] && !my_found[i - 2]) {
        break;
      }

      // Try to add
      if (board[i][0] != 0 && board[i][0] != row[0]) {
        // Doesn't match... breaking
        continue;
      }

      // Update board
      bool should_break = false;
      for (int k = 0; k < board.size(); k++) {
        if (board[i][k] != 0 &&
            board[i][k] != row[k]) {
          should_break = true;
          break;
        }

        // Column
        board[i][k] = row[k];
      }
      if (should_break) { break; }

      if (debug) {
        cout << "    MATCHED COL " << i << endl;
      }

      // Update found
      found[1][i] = true;

      tAns ans = dfs(heap, index + 1, board, found);
      if (ans.valid) { return ans; }
    } else if (board[i][0] >= row[0]) {
        // Already past our number
      break;
    }
  }

  tAns bad;
  bad.valid = false;
  return bad;
}

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    int n;
    cin >> n;

    vector<tRow> rows;
    for (int i = 0; i < 2 * n - 1; i++) {
      vector<int> x;
      for (int j = 0; j < n; j++) {
        int y;
        cin >> y;
        x.push_back(y);
      }
      rows.push_back(x);
    }

    sort(rows.begin(), rows.end(), my_sort);

    vector<tRow> board;
    vector<tBool> found;
    found.push_back(tBool());
    found.push_back(tBool());
    for (int i = 0; i < n; i++) {
      board.push_back(tRow());
      for (int j = 0; j < n; j++) { board[i].push_back(0); }
      found[0].push_back(false);
      found[1].push_back(false);
    }

    if (debug) {
      for (int i = 0; i < rows.size(); i++) {
        const tRow& row = rows[i];
        for (int j = 0; j < row.size(); j++) {
          cout << row[j] << " ";
        }
        cout << endl;
      }
    }

    tAns ans = dfs(rows, 0, board, found);

    printf("Case #%d:", i_case + 1);
    if (!ans.valid) {
      cout << "ANSWER NOT FOUND!" << endl;
      return 1;
    }

    for (int i = 0; i < ans.answer.size(); i++) {
      cout << " " << ans.answer[i];
    }
    cout << endl;
  }

  return 0;
}
