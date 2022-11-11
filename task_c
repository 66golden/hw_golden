#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct All {
  std::vector<int> arr;
  int ans;
  int value;
};

void Get(All& trash, int index, std::vector<int> finds, int tl, int tr) {
  if (tl == finds[0] && tr == finds[1]) {
    if (trash.arr[index] >= trash.value) {
      while (2 * index + 2 < int(trash.arr.size())) {
        if (trash.arr[2 * index + 1] >= trash.value) {
          index = 2 * index + 1;
        } else if (trash.arr[2 * index + 2] >= trash.value) {
          index = 2 * index + 2;
        }
      }
      trash.ans = std::min(trash.ans, index);
    }
    return;
  }
  int tm = (tl + tr) / 2;
  if (finds[0] < tm) {
    std::vector<int> help1 = {finds[0], std::min(tm, finds[1])};
    Get(trash, 2 * index + 1, help1, tl, tm);
  }
  if (finds[1] > tm) {
    std::vector<int> help2 = {std::max(tm, finds[0]), finds[1]};
    Get(trash, 2 * index + 2, help2, tm, tr);
  }
}

void Set(All& trash, int index, int value) {
  trash.arr[index] = value;
  while (index > 0) {
    index = (index - 1) / 2;
    trash.arr[index] =
        std::max(trash.arr[2 * index + 1], trash.arr[2 * index + 2]);
  }
}

void Solve(All& trash, int m, int k, int n) {
  int tmp, i, j;
  for (int p = 0; p < m; p++) {
    std::cin >> tmp >> i >> j;
    if (tmp == 0) {
      Set(trash, int(pow(2, k)) + i - 2, j);
    } else {
      trash.ans = int(trash.arr.size());
      trash.value = j;
      std::vector<int> finds = {i - 1, n};
      Get(trash, 0, finds, 0, int(pow(2, k)));
      if (trash.ans == int(trash.arr.size())) {
        std::cout << "-1" << '\n';
      } else {
        std::cout << trash.ans - int(pow(2, k)) + 2 << '\n';
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k = 0, size, tmp;
  std::cin >> n >> m;

  while (int(pow(2, k)) < n) {
    k++;
  }
  size = 2 * int(pow(2, k)) - 1;
  All trash;
  trash.arr.resize(size, 0);

  tmp = int(pow(2, k)) - 1;
  for (int i = tmp; i < tmp + n; i++) {
    std::cin >> trash.arr[i];
  }
  for (int i = k - 1; i >= 0; i--) {
    for (int l = int(pow(2, i)) - 1; l < int(pow(2, i + 1)) - 1; l++) {
      trash.arr[l] = std::max(trash.arr[2 * l + 1], trash.arr[2 * l + 2]);
    }
  }

  Solve(trash, m, k, n);
  return 0;
}
