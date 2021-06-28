#include <bits/stdc++.h>

using namespace std;

int main() {
  int data_size, s;
  cin >> data_size >> s;
  int *data_array;
  data_array = new int[data_size];
  for (int i = 0; i < data_size; i++) {
    cin >> data_array[i];
  }

  unordered_map<int, pair<int, int>> sum_map; // key: sum, value: <smaller_index, larger_index>
  bool found = false;
  int first_index, second_index, third_index, fourth_index;

  for (int pivot = 1; pivot < data_size - 2; pivot++) {
    for (int i = 0; i < pivot; i++) {
      int sum = data_array[i] + data_array[pivot];
      if (sum_map.count(sum) == 1) {
        pair<int, int> p = sum_map[sum];
        if (p.first > i || (p.first == i && p.second > pivot)) {
          sum_map[sum] = make_pair(i, pivot);
        }
      } else {
        sum_map[sum] = make_pair(i, pivot);
      }
    }

    for (int i = pivot + 2; i < data_size; i++) {
      int sum = data_array[pivot + 1] + data_array[i];
      if (sum_map.count(s - sum) == 1) {
        pair<int, int> p = sum_map[s - sum];
        if (!found) {
          first_index = p.first;
          second_index = p.second;
          third_index = pivot + 1;
          fourth_index = i;
          found = true;
        } else if (first_index > p.first || (first_index == p.first && second_index > p.second)
            || (first_index == p.first && second_index == p.second && third_index > pivot + 1)
            || (first_index == p.first && second_index == p.second && third_index == pivot + 1 && fourth_index > i)) {
          first_index = p.first;
          second_index = p.second;
          third_index = pivot + 1;
          fourth_index = i;
        }
      }
    }
  }

  if (found) {
    cout << first_index << " " << second_index << " " << third_index << " " << fourth_index;
  } else {
    cout << -1;
  }
  return 0;
}

