#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;
using std::fill_n;
using std::copy;
using std::begin;
using std::end;

struct Point {
  int y, x;
  Point(int y, int x) {
    this->y = y;
    this->x = x;
  }
};

struct Player {
  int time, y, x;
  Player(int time, int y, int x) {
    this->time = time;
    this->y = y;
    this->x = x;
  }
};

struct Enemy {
  int direction, y, x, y_next, x_next;
  Enemy(int direction, int y, int x) {
    this->direction = direction;
    this->y = y;
    this->x = x;
    this->y_next = y;
    this->x_next = x;
  }
};

int n, m, t;
int map[100][100];
int map_enemy[100][100];
vector<Enemy> enemies;
vector<Point> destinations;
int current_time = 0;
bool visited_map[100][100];

bool check_border(int y, int x) {
  if (y < 0 || y >= n) {
    return false;
  }

  if (x < 0 || x >= m) {
    return false;
  }

  return true;
}

void update_map() {
  fill_n(&visited_map[0][0], 100 * 100, false);

  for (Enemy &enemy : enemies) {
    map[enemy.y][enemy.x] = 1;
  }

  for (Enemy &enemy : enemies) {
    enemy.y = enemy.y_next;
    enemy.x = enemy.x_next;

    switch (enemy.direction) {
      case 4:
        if (check_border(enemy.y_next - 1, enemy.x_next) && map_enemy[enemy.y_next - 1][enemy.x_next] != 0) {
          enemy.y_next--;
        } else {
          enemy.direction++;
        }
        break;
      case 5:
        if (check_border(enemy.y_next, enemy.x_next + 1) && map_enemy[enemy.y_next][enemy.x_next + 1] != 0) {
          enemy.x_next++;
        } else {
          enemy.direction++;
        }
        break;
      case 6:
        if (check_border(enemy.y_next + 1, enemy.x_next) && map_enemy[enemy.y_next + 1][enemy.x_next] != 0) {
          enemy.y_next++;
        } else {
          enemy.direction++;
        }
        break;
      case 7:
        if (check_border(enemy.y_next, enemy.x_next - 1) && map_enemy[enemy.y_next][enemy.x_next - 1] != 0) {
          enemy.x_next--;
        } else {
          enemy.direction = 4;
        }
        break;
    }

    map[enemy.y][enemy.x] = 0;
    map[enemy.y_next][enemy.x_next] = 0;
  }
}

queue<Player> bfs_queue;

int main() {
  cin >> n >> m >> t;

  int input;
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      map[y][x] = 1;
      cin >> input;
      if (input == 0) {
        map[y][x] = 0;
      }
      if (input == 2) {
        bfs_queue.emplace(Player(current_time, y, x));
      }
      if (input == 3) {
        destinations.emplace_back(Point(y, x));
      }
      if (input == 4 || input == 5 || input == 6 || input == 7) {
        enemies.emplace_back(Enemy(input, y, x));
      }
    }
  }

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      map_enemy[i][j] = map[i][j];
    }
  }

  // set up enemy next location
  for (Enemy &enemy : enemies) {
    switch (enemy.direction) {
      case 4:
        if (check_border(enemy.y_next - 1, enemy.x_next) && map_enemy[enemy.y_next - 1][enemy.x_next] != 0) {
          enemy.y_next--;
        } else {
          enemy.direction++;
        }
        break;
      case 5:
        if (check_border(enemy.y_next, enemy.x_next + 1) && map_enemy[enemy.y_next][enemy.x_next + 1] != 0) {
          enemy.x_next++;
        } else {
          enemy.direction++;
        }
        break;
      case 6:
        if (check_border(enemy.y_next + 1, enemy.x_next) && map_enemy[enemy.y_next + 1][enemy.x_next] != 0) {
          enemy.y_next++;
        } else {
          enemy.direction++;
        }
        break;
      case 7:
        if (check_border(enemy.y_next, enemy.x_next - 1) && map_enemy[enemy.y_next][enemy.x_next - 1] != 0) {
          enemy.x_next--;
        } else {
          enemy.direction = 4;
        }
        break;
    }

    map[enemy.y][enemy.x] = 0;
    map[enemy.y_next][enemy.x_next] = 0;
  }

  fill_n(&visited_map[0][0], 100 * 100, false);

  while (!bfs_queue.empty()) {
    Player player = bfs_queue.front();
    bfs_queue.pop();

    for (Point d : destinations) {
      if (d.y == player.y && d.x == player.x) {
        cout << player.time;
        return 0;
      }
    }

    if (player.time != current_time) {
      if (++current_time > t) {
        break;
      }
      update_map();
    }

    if (visited_map[player.y][player.x]) {
      continue;
    }

    visited_map[player.y][player.x] = true;

    if (check_border(player.y, player.x) && map[player.y][player.x] != 0) {
      bfs_queue.emplace(Player(current_time + 1, player.y, player.x));
    }

    if (check_border(player.y + 1, player.x) && map[player.y + 1][player.x] != 0) {
      bfs_queue.emplace(Player(current_time + 1, player.y + 1, player.x));
    }

    if (check_border(player.y, player.x + 1) && map[player.y][player.x + 1] != 0) {
      bfs_queue.emplace(Player(current_time + 1, player.y, player.x + 1));
    }

    if (check_border(player.y - 1, player.x) && map[player.y - 1][player.x] != 0) {
      bfs_queue.emplace(Player(current_time + 1, player.y - 1, player.x));
    }

    if (check_border(player.y, player.x - 1) && map[player.y][player.x - 1] != 0) {
      bfs_queue.emplace(Player(current_time + 1, player.y, player.x - 1));
    }
  }

  cout << -1;

  return 0;
}
