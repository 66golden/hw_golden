#include <cmath>
#include <iostream>
#include <vector>

void LSD(std::vector<long long>& arr, int n, int number) {
  int c = 0;
  long long x;
  std::vector<std::vector<long long>> arr_numbers(10);
  for (int i = 0; i < n; i++) {
    x = (long long)(arr[i] / (pow(10, number - 1)));
    arr_numbers[x % 10].push_back(arr[i]);
  }
  for (int i = 0; i < 10; i++) {
    for (int k = 0; k < int(arr_numbers[i].size()); k++) {
      arr[c] = arr_numbers[i][k];
      c++;
    }
  }
}

void Solve(std::vector<long long>& arr, int n, int max_num) {
  for (int i = 1; i <= max_num; i++) {
    LSD(arr, n, i);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, max_num = 0;
  long long max_value = 0;
  std::cin >> n;
  std::vector<long long> arr(n);

  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
    max_value = (max_value >= arr[i]) ? max_value : arr[i];
  }
  while (max_value != 0) {
    max_num++;
    max_value /= 10;
  }

  Solve(arr, n, max_num);

  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << '\n';
  }

  return 0;
}
