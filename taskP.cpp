#include <algorithm>
#include <iostream>
#include <vector>

int Pow2(int n) { return 1 << n; }

int Bit(int mask, int pos) { return (mask >> pos) & 1; }

bool IsFit(std::vector<char>& pattern, int mask) {
  bool flag = true;
  for (int i = 0; i < int(pattern.size()); i++) {
    switch (pattern[i]) {
      case '+':
        flag = (Bit(mask, i) == 1);
        break;
      case '-':
        flag = (Bit(mask, i) == 0);
        break;
      case '.':
        break;
    }
    if (!flag) {
      return flag;
    }
  }
  return flag;
}

int Fixed(int first_number, int mask, int n) {
  int x, tmp = Bit(mask, 0);
  if (first_number == tmp) {
    for (int i = 1; i < n; i++) {
      x = Bit(mask, i);
      if (x == tmp) {
        return -1;
      }
      tmp = x;
    }
    return mask;
  }
  return (Pow2(n) - mask - 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int m, n, prev_mask;
  long long ans = 0;
  std::cin >> n >> m;
  std::vector<std::vector<char>> cages(m, std::vector<char>(n));
  std::vector<std::vector<long long>> dp(m, std::vector<long long>(Pow2(n), 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> cages[j][i];
    }
  }
  for (int mask = 0; mask < Pow2(n); mask++) {
    dp[0][mask] = (IsFit(cages[0], mask)) ? 1 : 0;
  }
  if (m == 1) {
    for (int mask = 0; mask < Pow2(n); mask++) {
      ans += dp[0][mask];
    }
    std::cout << ans;
    return 0;
  }
  for (int i = 1; i < m; i++) {
    for (int mask = 0; mask < Pow2(n); mask++) {
      if (IsFit(cages[i], mask)) {
        for (int k = 0; k < 2; k++) {
          prev_mask = Fixed(k, mask, n);
          if (prev_mask != -1 && IsFit(cages[i - 1], prev_mask)) {
            dp[i][mask] += dp[i - 1][prev_mask];
          }
        }
      }
    }
  }
  for (int mask = 0; mask < Pow2(n); mask++) {
    ans += dp[m - 1][mask];
    ans %= 1000000007;
  }
  std::cout << ans;
}
