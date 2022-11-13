#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int Rmq(std::vector<std::vector<std::pair<int, int>>>& table, int l,
        int r) {  // полуинтервал [l; r)
  int t = std::__lg(r - l);
  int index_min = (table[t][l].first < table[t][r - (1 << t)].first
                       ? table[t][l].second
                       : table[t][r - (1 << t)].second);
  return index_min;
}

int main() {
  int n, q, k = 0, left, right, x, tmp;
  std::cin >> n >> q;

  while (int(pow(2, k)) <= n) {
    k++;
  }

  std::vector<std::vector<std::pair<int, int>>> table(
      k, std::vector<std::pair<int, int>>(n));

  for (int i = 0; i < n; i++) {
    std::cin >> x;
    table[0][i] = std::make_pair(x, i);
  }

  for (int j = 1; j < k; j++) {
    table[j].resize(n - int(pow(2, j)) + 1);
  }

  for (int j = 1; j < k; j++) {
    for (int i = 0; i + int(pow(2, j - 1)) < n; i++) {
      if (table[j - 1][i].first < table[j - 1][i + int(pow(2, j - 1))].first) {
        table[j][i] = table[j - 1][i];
      } else {
        table[j][i] = table[j - 1][i + int(pow(2, j - 1))];
      }
    }
  }

  for (int i = 0; i < q; i++) {
    std::cin >> left >> right;
    if (right - left == 1) {
      std::cout << std::max(table[0][left - 1].first, table[0][right - 1].first)
                << '\n';
    } else {
      tmp = Rmq(table, left - 1, right);
      if (tmp == left - 1) {
        std::cout << table[0][Rmq(table, tmp + 1, right)].first << '\n';
      } else if (tmp == right - 1) {
        std::cout << table[0][Rmq(table, left - 1, tmp)].first << '\n';
      } else {
        std::cout << std::min(table[0][Rmq(table, left - 1, tmp)].first,
                              table[0][Rmq(table, tmp + 1, right)].first)
                  << '\n';
      }
    }
  }
}
