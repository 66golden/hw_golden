#include <algorithm>
#include <iostream>
#include <vector>

const long long kInf = 10000000000;

void Solve(std::vector<long long>& numbers, int n) {
  std::reverse(numbers.begin(), numbers.end());
  std::vector<std::pair<long long, int>> dp(n, std::make_pair(kInf, -1));
  std::vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    auto low =
        std::lower_bound(dp.begin(), dp.end(), std::make_pair(numbers[i], 0));
    int id_x = int(std::distance(dp.begin(), low));
    dp[id_x] = std::make_pair(numbers[i], i);
    pos[i] = (id_x == 0) ? -1 : dp[id_x - 1].second;
  }
  int i = n - 1;
  while (dp[i].first == kInf) {
    i--;
  }
  std::cout << i + 1 << '\n';
  std::vector<long long> ans;
  i = dp[i].second;
  while (i >= 0) {
    ans.push_back(i);
    i = pos[i];
  }
  for (int i = 0; i < int(ans.size()); i++) {
    std::cout << (n - ans[i]) << ' ';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<long long> numbers(n);
  for (int i = 0; i < n; i++) {
    std::cin >> numbers[i];
  }
  Solve(numbers, n);
}
