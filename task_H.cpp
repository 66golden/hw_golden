#include <iostream>
#include <vector>

int Partition(std::vector<int>& arr, int start, int end) {
  int x = start;
  int pivot = arr[x];

  int counter = 0;
  for (int i = start; i <= end; i++) {
    if (arr[i] < pivot) {
      counter++;
    }
  }

  int pivot_index = start + counter;
  std::swap(arr[pivot_index], arr[x]);

  int i = start, j = end;

  while (true) {
    while (arr[i] < pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i >= j) {
      return j;
    }
    std::swap(arr[i++], arr[j--]);
  }

  return pivot_index;
}

void QS(std::vector<int>& arr, int start, int end) {
  if (start >= end) {
    return;
  }

  int p = Partition(arr, start, end);

  QS(arr, start, p);
  QS(arr, p + 1, end);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  QS(arr, 0, n - 1);

  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
}
