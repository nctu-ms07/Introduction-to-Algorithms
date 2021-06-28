#include <bits/stdc++.h>

using namespace std;

struct Point {
  int index, x, y, z;
  Point *next = nullptr;
};

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  Point points[n];
  Point *duplicated_points[n];
  int duplicated_points_size[n];
  int answer[n];

  for (int i = 0; i != n; i++) {
    points[i].index = i;
    cin >> points[i].x >> points[i].y >> points[i].z;

    answer[i] = n - 1;
    duplicated_points_size[i] = 0;
    duplicated_points[i] = nullptr;
  }

  // calculating duplicated x coordinate points
  for (int i = 0; i != n; i++) {
    duplicated_points_size[points[i].x]++;

    auto *insert = new Point;
    *insert = points[i];
    insert->next = duplicated_points[points[i].x];
    duplicated_points[points[i].x] = insert;
  }

  // minus out duplicated x coordinate points
  for (int i = 0, j = 0; i != n; i++) {
    while (duplicated_points[i] != nullptr) {
      Point *p = duplicated_points[i];
      answer[p->index] -= (duplicated_points_size[i] - 1);
      duplicated_points[i] = p->next;
      points[j++] = *p; //sorting points with x coordinate
      delete p;
    }
    duplicated_points_size[i] = 0;
  }

  // calculating duplicated y coordinate points
  for (int i = 0; i != n; i++) {
    duplicated_points_size[points[i].y]++;

    auto *insert = new Point;
    *insert = points[i];
    insert->next = duplicated_points[points[i].y];
    duplicated_points[points[i].y] = insert;
  }

  // minus out duplicated y coordinate points
  for (int i = 0, j = 0; i != n; i++) {
    while (duplicated_points[i] != nullptr) {
      Point *p = duplicated_points[i];
      answer[p->index] -= (duplicated_points_size[i] - 1);
      duplicated_points[i] = p->next;
      points[j++] = *p; //sorting points with y coordinate
      delete p;
    }
    duplicated_points_size[i] = 0;
  }

  // adding back points that have same x y coordinate
  for (int i = 0; i != n;) {
    int j = i + 1;
    while (j < n && points[i].y == points[j].y && points[i].x == points[j].x) {
      j++;
    }
    int same_coordinate_count = j - i - 1;
    while (i < j) {
      answer[points[i++].index] += same_coordinate_count;
    }
  }

  // calculating duplicated z coordinate points
  for (int i = 0; i != n; i++) {
    duplicated_points_size[points[i].z]++;

    auto *insert = new Point;
    *insert = points[i];
    insert->next = duplicated_points[points[i].z];
    duplicated_points[points[i].z] = insert;
  }

  // minus out duplicated z coordinate points
  for (int i = 0, j = 0; i != n; i++) {
    while (duplicated_points[i] != nullptr) {
      Point *p = duplicated_points[i];
      answer[p->index] -= (duplicated_points_size[i] - 1);
      duplicated_points[i] = p->next;
      points[j++] = *p; //sorting points with z coordinate
      delete p;
    }
    duplicated_points_size[i] = 0;
  }

  // adding back points that have same y z coordinate
  for (int i = 0; i != n;) {
    int j = i + 1;
    while (j < n && points[i].z == points[j].z && points[i].y == points[j].y) {
      j++;
    }
    int same_coordinate_count = j - i - 1;
    while (i < j) {
      answer[points[i++].index] += same_coordinate_count;
    }
  }

  // calculating duplicated x coordinate points
  for (int i = 0; i != n; i++) {
    duplicated_points_size[points[i].x]++;

    auto *insert = new Point;
    *insert = points[i];
    insert->next = duplicated_points[points[i].x];
    duplicated_points[points[i].x] = insert;
  }

  // sorting points with x coordinate
  for (int i = 0, j = 0; i != n; i++) {
    while (duplicated_points[i] != nullptr) {
      Point *p = duplicated_points[i];
      duplicated_points[i] = p->next;
      points[j++] = *p; //sorting points with x coordinate
      delete p;
    }
    duplicated_points_size[i] = 0;
  }

  // adding back points that have same x z coordinate
  for (int i = 0; i != n;) {
    int j = i + 1;
    while (j < n && points[i].x == points[j].x && points[i].z == points[j].z) {
      j++;
    }
    int same_coordinate_count = j - i - 1;
    while (i < j) {
      answer[points[i++].index] += same_coordinate_count;
    }
  }

  // minus out points that have same x y z coordinate
  for (int i = 0; i != n;) {
    int j = i + 1;
    while (j < n && points[i].x == points[j].x && points[i].z == points[j].z && points[i].y == points[j].y) {
      j++;
    }
    int same_coordinate_count = j - i - 1;
    while (i < j) {
      answer[points[i++].index] -= same_coordinate_count;
    }
  }


  // cout is so slow so we change to printf
  for (int i = 0; i != n; i++) {
//    cout << answer[i] << endl;
    printf("%d\n", answer[i]);
  }

  return 0;
}