#include <bits/stdc++.h>

using namespace std;

int n, k;
long *p;

unordered_map<int, bool> b_search_cache;

int get_next_point_index(int target, int left, int right) {
  int mid = left + (right - left) / 2;

  if (p[mid] > target) {
    if (p[mid - 1] <= target) {
      return mid;
    } else {
      return get_next_point_index(target, left, mid - 1);
    }
  } else {
    return get_next_point_index(target, mid + 1, right);
  }
}

bool check(int interval_length) {
  if (b_search_cache.count(interval_length) == 0) {
    int current_point = p[0];
    int next_point_index = 0;
    int max_interval_count = k;
    while (max_interval_count--) {
      if (current_point + interval_length >= p[n - 1]) {
        b_search_cache[interval_length] = true;
        return true;
      } else {
        next_point_index = get_next_point_index(current_point + interval_length, next_point_index, n - 1);
        current_point = p[next_point_index];
      }
    }
    b_search_cache[interval_length] = false;
    return false;
  }

  return b_search_cache[interval_length];
}

int b_search(long left, long right) {
  int mid = left + (right - left) / 2;
  if (check(mid)) {
    if (!check(mid - 1)) {
      return mid;
    } else {
      return b_search(left, mid - 1);
    }
  } else {
    return b_search(mid + 1, right);
  }
}

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;

  p = new long[n];
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }

  sort(p, p + n);

  if (check(0)) {
    cout << 0;
  } else {
    cout << b_search(0, ((p[n - 1] - p[0]) + 1) / k);
  }

  delete[] p;

  return 0;
}
