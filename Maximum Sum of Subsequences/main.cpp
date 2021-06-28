#include <bits/stdc++.h>

using namespace std;

struct Node {
  int answer = 0;
  int exclude_first = 0; //answer that excludes first element in range
  int exclude_last = 0;  //answer that excludes last element in range
  int exclude_first_and_last = 0;  //answer that excludes first and last elements in range
};

int *data_array;
Node *segment_tree;

Node query(int target_left, int target_right, int node_index, int node_left, int node_right) {
  if (target_left <= node_left && node_right <= target_right) {
    return segment_tree[node_index];
  }

  Node result;
  if (node_right < target_left || target_right < node_left) {
    return result;
  }
  int mid = (node_left + node_right) / 2;
  Node left_child = query(target_left, target_right, 2 * node_index + 1, node_left, mid);
  Node right_child = query(target_left, target_right, 2 * node_index + 2, mid + 1, node_right);

  // max(left child + right child without first element, left child without last element + right child)
  result.answer = max(left_child.answer + right_child.exclude_first, left_child.exclude_last + right_child.answer);

  result.exclude_first =
      max(left_child.exclude_first + right_child.exclude_first, left_child.exclude_first_and_last + right_child.answer);

  result.exclude_last =
      max(left_child.exclude_last + right_child.exclude_last, left_child.answer + right_child.exclude_first_and_last);

  result.exclude_first_and_last = max(left_child.exclude_first + right_child.exclude_first_and_last,
                                      left_child.exclude_first_and_last + right_child.exclude_last);
  return result;
}

void update(int index, int value, int node_index, int node_left, int node_right) {
  if (node_left == node_right) {
    segment_tree[node_index].answer = value;
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

    // max(left child + right child without first element, left child without last element + right child)
    segment_tree[node_index].answer =
        max(segment_tree[node_left_child].answer + segment_tree[node_right_child].exclude_first,
            segment_tree[node_left_child].exclude_last + segment_tree[node_right_child].answer);

    segment_tree[node_index].exclude_first =
        max(segment_tree[node_left_child].exclude_first + segment_tree[node_right_child].exclude_first,
            segment_tree[node_left_child].exclude_first_and_last + segment_tree[node_right_child].answer);

    segment_tree[node_index].exclude_last =
        max(segment_tree[node_left_child].answer + segment_tree[node_right_child].exclude_first_and_last,
            segment_tree[node_left_child].exclude_last + segment_tree[node_right_child].exclude_last);

    segment_tree[node_index].exclude_first_and_last =
        max(segment_tree[node_left_child].exclude_first + segment_tree[node_right_child].exclude_first_and_last,
            segment_tree[node_left_child].exclude_first_and_last + segment_tree[node_right_child].exclude_last);
  }
}

void build_tree(int node_index, int node_left, int node_right) {
  if (node_left == node_right) {
    segment_tree[node_index].answer = data_array[node_left];
    segment_tree[node_index].exclude_first = 0;
    segment_tree[node_index].exclude_last = 0;
    segment_tree[node_index].exclude_first_and_last = 0;
  } else {
    int mid = (node_left + node_right) / 2;
    int node_left_child = 2 * node_index + 1;
    int node_right_child = 2 * node_index + 2;
    build_tree(node_left_child, node_left, mid); //build left child
    build_tree(node_right_child, mid + 1, node_right); //build right child

    // max(left child + right child without first element, left child without last element + right child)
    segment_tree[node_index].answer =
        max(segment_tree[node_left_child].answer + segment_tree[node_right_child].exclude_first,
            segment_tree[node_left_child].exclude_last + segment_tree[node_right_child].answer);

    segment_tree[node_index].exclude_first =
        max(segment_tree[node_left_child].exclude_first + segment_tree[node_right_child].exclude_first,
            segment_tree[node_left_child].exclude_first_and_last + segment_tree[node_right_child].answer);

    segment_tree[node_index].exclude_last =
        max(segment_tree[node_left_child].answer + segment_tree[node_right_child].exclude_first_and_last,
            segment_tree[node_left_child].exclude_last + segment_tree[node_right_child].exclude_last);

    segment_tree[node_index].exclude_first_and_last =
        max(segment_tree[node_left_child].exclude_first + segment_tree[node_right_child].exclude_first_and_last,
            segment_tree[node_left_child].exclude_first_and_last + segment_tree[node_right_child].exclude_last);
  }
}

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  int data_size, operations;
  cin >> data_size >> operations;
  data_array = new int[data_size];
  segment_tree = new Node[4 * data_size];
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
      cout << query(j, k, 0, 0, data_size - 1).answer << endl;
    }
  }
  delete[] segment_tree;
  delete[] data_array;
  return 0;
}
