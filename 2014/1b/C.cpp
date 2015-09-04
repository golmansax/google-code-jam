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

#define MAX_CITIES 50

bool better(vector<int> other, vector<int> now, int zips[MAX_CITIES], int n) {
  for (int i = 0; i < n; i++) {
    if (other[i] > now[i]) {
      return false;
    }
  }

  return true;
}

bool in_vector(vector<int> v, int x) {
  for (int i = 0; i < v.size(); i++) {
    if (x == v[i]) {
      return true;
    }
  }

  return false;
}

vector<int> ans;
bool found_path = false;

void print_vec(vector<int> v, int current) {
  for (int i = 0; i < v.size(); i++) {
    cout << (v[i] + 1) << ", ";
  }
  cout << "WITH CURRENT " << (current + 1) << endl;
}

void dfs(int current,
    vector<int> path, int zips[MAX_CITIES], 
    bool flights[MAX_CITIES][MAX_CITIES], 
    map<int, set<int> > returns,
    int n) {

  //print_vec(path, current);

  if (path.size() == n) {
    if (!found_path || better(path, ans, zips, n)) {
      found_path = true;
      ans = path;
      return;
    }
  }
  if (found_path && !better(path, ans, zips, path.size())) {
    return;
  }

  for (int i = 0; i < n; i++) {
    vector<int> other;

    if (found_path) {
      if (zips[ans[path.size()]] < zips[i]) {
        continue;
      }
    }

    if (flights[current][i] && !in_vector(path, i)) {
      // Try to take it
      vector<int> new_path = path;
      new_path.push_back(i);

      returns[i].insert(current);

      dfs(
        i,
        new_path,
        zips,
        flights,
        returns,
        n
      );
    }
  }

  for (int i = 0; i < n; i++) {
    vector<int> other;

    if (returns[current].count(i)) {
      returns[current].erase(i);

      dfs(
        i,
        path,
        zips,
        flights,
        returns,
        n
      );
    }
  }
}

int main() {
  int n_tests;
  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; i_test++) {
    int n, m;
    cin >> n >> m;

    map<int, set<int> > returns;
    
    int zips[MAX_CITIES];
    int min_zip = 10000000;
    int min_zip_index = -1;
    for (int i = 0; i < n; i++) {
      cin >> zips[i];

      if (min_zip > zips[i]) {
        min_zip = zips[i];
        min_zip_index = i;
      }
    }

    bool flights[MAX_CITIES][MAX_CITIES];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        flights[i][j] = false;
      }
    }
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      x--;
      y--;
      flights[x][y] = flights[y][x] = true;
    }

    // Depth first search
    vector<int> path;
    path.push_back(min_zip_index);
    ans.clear();
    found_path = false;
    dfs(min_zip_index, path, zips, flights, returns, n);

    printf("Case #%d: ", i_test+1);

    for (int i = 0; i < ans.size(); i++) {
      printf("%d", zips[ans[i]]);
    }
    printf("\n");
  }
}
