#include <bits/stdc++.h>

using namespace std;

int *data_array;
int *segment_tree;

int query(int target_left, int target_right, int node_index, int node_left, int node_right) {
  if (target_left <= node_left && node_right <= target_right) {
    return segment_tree[node_index];
  }

  if (node_right < target_left || target_right < node_left) {
    return 0;
  }

  int mid = (node_left + node_right) / 2;
  int left_child = query(target_left, target_right, 2 * node_index + 1, node_left, mid);
  int right_child = query(target_left, target_right, 2 * node_index + 2, mid + 1, node_right);

  return left_child + right_child;
}

void update(int index, int value, int node_index, int node_left, int node_right) {
  if (node_left == node_right) {
    segment_tree[node_index] = value;
  } else {
    int mid = (node_left + node_right) / 2;
    int node_left_child = 2 * node_index + 1;
    int node_right_child = 2 * node_index + 2;
    if (node_left <= index && index <= mid) { // ranged inside left child
      update(index, value, node_left_child, node_left, mid);
    }

    if (mid + 1 <= index && index <= node_right) { // ranged inside right child
      update(index, value, node_right_child, mid + 1, node_right);
    }

    segment_tree[node_index] = segment_tree[node_left_child] + segment_tree[node_right_child];
  }
}

void build_tree(int node_index, int node_left, int node_right) {
  if (node_left == node_right) {
    segment_tree[node_index] = data_array[node_left];
  } else {
    int mid = (node_left + node_right) / 2;
    int node_left_child = 2 * node_index + 1;
    int node_right_child = 2 * node_index + 2;
    build_tree(node_left_child, node_left, mid); //build left child
    build_tree(node_right_child, mid + 1, node_right); //build right child

    segment_tree[node_index] = segment_tree[node_left_child] + segment_tree[node_right_child];
  }
}

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  int data_size, operations;
  cin >> data_size >> operations;
  data_array = new int[data_size];
  segment_tree = new int[4 * data_size];
  for (int i = 0; i < data_size; i++) {
    cin >> data_array[i];
  }
  build_tree(0, 0, data_size - 1);
  int i, j, k;
  while (operations--) {
    cin >> i >> j >> k;
    if (i == 0) {
      update(j, k, 0, 0, data_size - 1);
    } else {
      if (k >= j) {
        cout << query(j, k, 0, 0, data_size - 1) << endl;
      } else {
        cout << query(0, k, 0, 0, data_size - 1) + query(j, data_size - 1, 0, 0, data_size - 1) << endl;
      }

    }
  }
  delete[] segment_tree;
  delete[] data_array;
  return 0;
}
