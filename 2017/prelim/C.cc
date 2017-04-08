#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct row {
  long long left_index;
  long long right_index;

  long long length() const {
    return right_index - left_index + 1;
  }

  bool operator<(const row& a) const {
    if (length() == a.length()) {
      return left_index < a.left_index;
    }

    return length() < a.length();
  }
};

int main() {
  int n_cases;
  cin >> n_cases;

  for (int i_case = 0; i_case < n_cases; i_case++) {
    long long n, k;
    cin >> n >> k;

    vector<row> heap;
    heap.push_back({0, n - 1});
    push_heap(heap.begin(), heap.end());

    row current;
    for (int i = 0; i < k; i++) {
      pop_heap(heap.begin(), heap.end());
      current = *heap.rbegin();
      heap.pop_back();

      if (current.length() <= 1 || i == k - 1) {
        continue;
      }

      if (current.length() > 2) {
        // Add left
        long long left_dist = (current.length() - 1) / 2;

        heap.push_back({current.left_index, current.left_index + left_dist - 1});
        push_heap(heap.begin(), heap.end());
      }

      // Add right
      long long right_dist = current.length() / 2;
      heap.push_back({current.right_index - right_dist + 1, current.right_index});
      push_heap(heap.begin(), heap.end());
    }

    printf("Case #%d: %lld %lld\n", i_case + 1, current.length() / 2, (current.length() - 1) / 2);
  }

  return 0;
}
