#include <bits/stdc++.h>

using namespace std;

unordered_map<long,bool> cache;

bool check(vector<int> &words, long max_column) {
  if(cache.count(max_column) == 0){
    long column = -1;
    int row = 1;
    for (auto word_size : words) {
      if (column + 1 + word_size > max_column) {
        column = -1;
        row++;
      }
      column += (1 + word_size);

      if (row > 24) {
        cache[max_column] = false;
        return false;
      }
    }
    cache[max_column] = true;
  }

  return cache[max_column];
}

int b_search(vector<int> &words, long left, long right) {
  long mid = left + ((right - left) / 2);

  if (!check(words, mid)) {
    return b_search(words, mid + 1, right);
  } else if (check(words, mid - 1)) {
    return b_search(words, left , mid - 1);
  } else {
    return mid;
  }
}

int main() {
  int n;
  cin >> n;
  string word;
  vector<int> words(n);
  int longest = 0;
  for (int i = 0; i < n; i++) {
    cin >> word;
    words[i] = word.length();
    longest = max(longest, words[i]);
  }
  if (n <= 24) {
    cout << longest;
  } else {
    cout << b_search(words, 0, 5000000000);
  }
  return 0;
}
