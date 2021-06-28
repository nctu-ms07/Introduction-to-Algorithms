#include <bits/stdc++.h>

using namespace std;

long *a;
long *tree;

long query(long target_left, long target_right, long node_index, long left, long right) {
  if (target_left <= left && right <= target_right) {
    return tree[node_index];
  }

  if (right < target_left || target_right < left) {
    return INT_MIN;
  }

  long mid = (left + right) / 2;

  return max(query(target_left, target_right, node_index * 2 + 1, left, mid),
             query(target_left, target_right, node_index * 2 + 2, mid + 1, right));
}

void build_tree(long node_index, long left, long right) {
  if (left == right) {
    tree[node_index] = a[left];
  } else {
    long mid = (left + right) / 2;
    build_tree(node_index * 2 + 1, left, mid);
    build_tree(node_index * 2 + 2, mid + 1, right);

    tree[node_index] = max(tree[node_index * 2 + 1], tree[node_index * 2 + 2]);
  }
}

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  long n, operation;
  cin >> n >> operation;
  a = new long[n];
  tree = new long[n << 2];

  for (long i = 0; i < n; i++) {
    cin >> a[i];
  }

  build_tree(0, 0, n - 1);

  long i, j;
  while (operation--) {
    cin >> i >> j;
    printf("%d\n", query(i, j, 0, 0, n - 1));
  }

  delete[] a;
  delete[] tree;

  return 0;
}