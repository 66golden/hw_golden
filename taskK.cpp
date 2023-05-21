#include <iostream>
#include <vector>

struct Node {
  int w = 0;
  int c = 0;
};

void Solve(std::vector<Node> arr, int n, int r) {
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(r + 1, 0));
  std::vector<std::vector<std::vector<int>>> obj_id(
      n + 1, std::vector<std::vector<int>>(r + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= r; j++) {
      if (j < arr[i - 1].w) {
        dp[i][j] = dp[i - 1][j];
        obj_id[i][j] = obj_id[i - 1][j];
      } else {
        if (dp[i - 1][j] > dp[i - 1][j - arr[i - 1].w] + arr[i - 1].c) {
          dp[i][j] = dp[i - 1][j];
          obj_id[i][j] = obj_id[i - 1][j];
        } else {
          dp[i][j] = dp[i - 1][j - arr[i - 1].w] + arr[i - 1].c;
          obj_id[i][j] = obj_id[i - 1][j - arr[i - 1].w];
          obj_id[i][j].push_back(i);
        }
      }
    }
  }
  for (auto x : obj_id[n][r]) {
    std::cout << x << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, r;
  std::cin >> n >> r;
  std::vector<Node> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i].w;
  }
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i].c;
  }
  Solve(arr, n, r);
}
