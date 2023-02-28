#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, k;
  std::cin >> n >> k;
  if (n == 1) {
    std::cout << 0 << '\n';
    return 0;
  }
  if (k == 0) {
    std::cout << -1 << '\n';
    return 0;
  }
  std::vector<std::vector<int>> dp(k + 1);
  dp[0] = std::vector<int>(n + 1, 0);
  for (int i = 1; i < k + 1; i++) {
    for (int j = 0; j < n + 1; j++) {
      if (j == 0) {
        dp[i].push_back(0);
      } else if (i == 1) {
        dp[i].push_back(j);
      } else {
        dp[i].push_back(dp[i][j - 1] + dp[i - 1][j - 1] + 1);
      }
      if (dp[i][j] >= n) {
        break;
      }
    }
  }
  int x = 0;
  while (dp[k][x] < n - 1) {
    ++x;
  }
  std::cout << x << '\n';
}
