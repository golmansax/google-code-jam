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
#include <utility>

using namespace std;

struct tTrip {
  int o, e, p;
};

bool TripCmp(tTrip t1, tTrip t2) {
  return t1.o < t2.o;
}

map<long long, long long> orig, best;

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

void Compute(map<int, int> starts, map<int, int> ends) {
  // iterate and greedily grab low starts from high ends
  
  for (map<int, int>::reverse_iterator s_it = starts.rbegin(); 
      s_it != starts.rend(); s_it++) {
    // Get to lowest end
    map<int, int>::reverse_iterator e_it = ends.rbegin();
    int lowest = e_it->first;
    while (e_it != ends.rend() && e_it->first >= s_it->first) {
      lowest = e_it->first;
      e_it++;
    }

    map<int, int>::iterator e_up_it = ends.find(lowest);

    while (s_it->second > 0) {
      while (e_up_it->second == 0) {
        if (e_up_it == ends.end()) {
          // never should get here
          printf("starts\n");
          for (map<int, int>::iterator it = starts.begin(); 
              it != starts.end(); it++) {
            printf ("%d %d\n", it->first, it->second);
          }
          printf("ends\n");
          for (map<int, int>::iterator it = ends.begin(); 
              it != ends.end(); it++) {
            printf ("%d %d\n", it->first, it->second);
          }

          exit(0);
        }

        e_up_it++;
      }

      int n = MIN(s_it->second, e_up_it->second);
      best[e_up_it->first - s_it->first] += n;

      s_it->second -= n;
      e_up_it->second -= n;
    }
  }

/*
  map<int, int>::iterator s_it = starts.begin();
  map<int, int>::reverse_iterator e_it = ends.rbegin();
  for (map<int, int>::reverse_iterator it = ends.rbegin(); it != ends.rend(); it++) {
    printf ("%d %d\n", it->first, it->second);
  }

  while (e_it != ends.rend()) {
    int n = MIN(s_it->second, e_it->second);
    //printf("%d %d %d\n", s_it->first, e_it->first, n);
    
    best[e_it->first - s_it->first] += n;
    s_it->second -= n;
    if (s_it->second == 0) s_it++;

    e_it->second -= n;
    if (e_it->second == 0) e_it++;
  }
  */
}

unsigned long long GetAns(int n, map<long long, long long> diffs) {
  unsigned long long ans = 0;
  for (map<long long, long long>::iterator it = diffs.begin();
      it != diffs.end(); it++) {
    //printf("%lld %lld\n", it->first, it->second);
    unsigned long long diff = it->first;
    ans += (unsigned long long) it->second * (n * diff - (diff - 1) * (diff - 2) / 2);
  }
  return ans;
}

int main() {
  int n_tests;
  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; i_test++) {
    int n, m;
    cin >> n >> m;

    vector<tTrip> trips;
    trips.reserve(m);
    for (int i = 0; i < m; i++) {
      tTrip trip;

      cin >> trip.o >> trip.e >> trip.p;
      trips.push_back(trip);
    }
    sort(trips.begin(), trips.end(), TripCmp);

    // Determine groups (pair: start, end) (index);
    int start = -1,
        end = -1,
        idx = 0,
        st_idx = -1;

    map<int, int> starts, ends;
    orig.clear();
    best.clear();

    for (vector<tTrip>::iterator it = trips.begin(); it != trips.end(); it++) {
      if (start == -1) {
        st_idx = idx;
        start = it->o;
        end = it->e;
      }
      else if (it->o <= end) {
        // add it
        if (end < it->e) end = it->e;
      }
      else {
        // end it
        Compute(starts, ends);
        starts.clear();
        ends.clear();

        st_idx = idx;
        start = it->o;
        end = it->e;
      }
      starts[it->o] += it->p;
      ends[it->e] += it->p;

      orig[it->e - it->o] += it->p;

      idx++;
    }
    // end current
    Compute(starts, ends);

    unsigned long long ans = GetAns(n, orig) - GetAns(n, best);
    
    printf("Case #%d: %llu\n", i_test+1, ans);
  }
}
