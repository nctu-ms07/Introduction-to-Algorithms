#include <bits/stdc++.h>

using namespace std;

unordered_map<int, long> larger; // key: right_index, value: left > right count
unordered_map<int, long> smaller_or_equal; //key: left_index, value: left <= right count

void mergesort(vector<pair<int, int>> &source, int from, int to) {
  if (from < to) {
    int mid = (from + to) / 2;
    mergesort(source, from, mid);
    mergesort(source, mid + 1, to);
    //merge
    int left_index = 0, right_index = 0, index = from;
    vector<pair<int, int>> left_v(source.begin() + from, source.begin() + mid + 1);
    vector<pair<int, int>> right_v(source.begin() + mid + 1, source.begin() + to + 1);
    while (left_index < left_v.size() && right_index < right_v.size()) {
      if (left_v[left_index].second <= right_v[right_index].second) {
        source[index++] = left_v[left_index];
        // left <= right count : (right_v.size() - right_index)
        smaller_or_equal[left_v[left_index++].first] += (right_v.size() - right_index);
      } else {
        source[index++] = right_v[right_index];
        // left > right count : (left_v.size() - left_index);
        larger[right_v[right_index++].first] += (left_v.size() - left_index);
      }
    }

    while (right_index < right_v.size()) {
      source[index++] = right_v[right_index++];
    }

    while (left_index < left_v.size()) {
      source[index++] = left_v[left_index++];
    }

  }
  return;
}

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> input(n); //first: original index, second: value
  for (int i = 0; i < n; i++) {
    input[i].first = i;
    cin >> input[i].second;
  }

  mergesort(input, 0, n - 1);

  long invert_triplet = 0;
  for (int i = 1; i < n - 1; i++) {
    if (larger.count(i)) {
      invert_triplet += larger[i] * (n - (i + 1) - smaller_or_equal[i]);
    }
  }

  cout << invert_triplet;
  return 0;
}
