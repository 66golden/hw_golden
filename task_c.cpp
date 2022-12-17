#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
//
struct Tree {
  std::vector<int> arr;
  int ans;
  int value;

  void Get(int index, std::vector<int> finds, int tl, int tr) {
    if (tl == finds[0] && tr == finds[1]) {
      if (arr[index] >= value) {
        while (2 * index + 2 < int(arr.size())) {
          if (arr[2 * index + 1] >= value) {
            index = 2 * index + 1;
          } else if (arr[2 * index + 2] >= value) {
            index = 2 * index + 2;
          }
        }
        ans = std::min(ans, index);
      }
      return;
    }
    int tm = (tl + tr) / 2;
    if (finds[0] < tm) {
      std::vector<int> help1 = {finds[0], std::min(tm, finds[1])};
      Get(2 * index + 1, help1, tl, tm);
    }
    if (finds[1] > tm) {
      std::vector<int> help2 = {std::max(tm, finds[0]), finds[1]};
      Get(2 * index + 2, help2, tm, tr);
    }
  }

  void Set(int index, int value) {
    arr[index] = value;
    while (index > 0) {
      index = (index - 1) / 2;
      arr[index] = std::max(arr[2 * index + 1], arr[2 * index + 2]);
    }
  }
};

void Solve(Tree& tree, int m, int k, int n) {
  int tmp, i, j;
  for (int p = 0; p < m; p++) {
    std::cin >> tmp >> i >> j;
    if (tmp == 0) {
      tree.Set(int(pow(2, k)) + i - 2, j);
    } else {
      tree.ans = int(tree.arr.size());
      tree.value = j;
      std::vector<int> finds = {i - 1, n};
      tree.Get(0, finds, 0, int(pow(2, k)));
      if (tree.ans == int(tree.arr.size())) {
        std::cout << "-1" << '\n';
      } else {
        std::cout << tree.ans - int(pow(2, k)) + 2 << '\n';
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
  Tree tree;
  tree.arr.resize(size, 0);

  tmp = int(pow(2, k)) - 1;
  for (int i = tmp; i < tmp + n; i++) {
    std::cin >> tree.arr[i];
  }
  for (int i = k - 1; i >= 0; i--) {
    for (int l = int(pow(2, i)) - 1; l < int(pow(2, i + 1)) - 1; l++) {
      tree.arr[l] = std::max(tree.arr[2 * l + 1], tree.arr[2 * l + 2]);
    }
  }

  Solve(tree, m, k, n);
  return 0;
}
