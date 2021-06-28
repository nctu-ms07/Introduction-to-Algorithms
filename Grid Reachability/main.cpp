#include <bits/stdc++.h>

using namespace std;

struct Coord {
  int x, y;

  explicit Coord(int x = 0, int y = 0) {
    this->x = x;
    this->y = y;
  }

  bool operator==(const Coord c) const {
    return (c.x == x && c.y == y);
  }

  bool operator!=(const Coord c) const {
    return !(c.x == x && c.y == y);
  }
};

struct Operation {
  int a, b, c, d;
  Operation(int a, int b, int c, int d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
  }
};

int n, m, k;
int maze[1000][1000];
bool visited[1000][1000];
queue<Coord> bfs_queue;

int move_x[] = {0, 0, -1, 1};
int move_y[] = {-1, 1, 0, 0};

Coord parent[1000][1000];
stack<Operation> ops;
stack<bool> ans;

bool check(int x, int y) {
  if (x >= m || x < 0) {
    return false;
  }

  if (y >= n || y < 0) {
    return false;
  }

  if (maze[y][x] != 1) {
    return false;
  }

  return true;
}

Coord findParent(Coord point) {
  Coord p;
  for (p = point; parent[p.y][p.x] != p; p = parent[p.y][p.x]);
  while (point != parent[point.y][point.x]) {
    Coord tmp = point;
    point = parent[point.y][point.x];
    parent[tmp.y][tmp.x] = p;
  }
  return point;
}

int main() {
  ifstream::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> maze[i][j];
      parent[i][j] = Coord(j, i);
      visited[i][j] = false;
    }
  }

  while (k--) {
    int a, b, c, d;
    cin >> a;
    if (a < 0) {
      cin >> c >> d;
      maze[c][d]--;
    } else {
      cin >> b >> c >> d;
    }
    ops.push(Operation(a, b, c, d));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (maze[i][j] <= 0 || visited[i][j]) {
        continue;
      }
      bfs_queue.push(Coord(j, i));
      while (!bfs_queue.empty()) {
        Coord point = bfs_queue.front();
        bfs_queue.pop();

        if (visited[point.y][point.x]) {
          continue;
        }

        visited[point.y][point.x] = true;
        parent[point.y][point.x] = Coord(j, i);

        for (int t = 0; t < 4; t++) {
          if (check(point.x + move_x[t], point.y + move_y[t])) {
            bfs_queue.emplace(Coord(point.x + move_x[t], point.y + move_y[t]));
          }
        }
      }
    }
  }

  while (!ops.empty()) {
    Operation op = ops.top();
    ops.pop();

    if (op.a < 0) {
      maze[op.c][op.d]++;

      if (maze[op.c][op.d] == 1) {
        for (int i = 0; i < 4; i++) {
          if (check(op.d + move_x[i], op.c + move_y[i])) {
            Coord origin_parent = findParent(Coord(op.d + move_x[i], op.c + move_y[i]));
            parent[origin_parent.y][origin_parent.x] = Coord(op.d, op.c);
          }
        }
      }
    } else {
      if (maze[op.a][op.b] <= 0 || maze[op.c][op.d] <= 0) {
        ans.push(false);
      } else {
        Coord from_parent = findParent(Coord(op.b, op.a));
        Coord to_parent = findParent(Coord(op.d, op.c));
        ans.push((from_parent == to_parent));
      }
    }
  }

  while (!ans.empty()) {
    if (ans.top()) {
      printf("1\n");
    } else {
      printf("0\n");
    }
    ans.pop();
  }

  return 0;
}
