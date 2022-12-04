#include <iostream>

int Partition(int* a, int left, int right) {
  int cur = a[(left + right) / 2];
  int i = left, j = right;
  while (i <= j) {
    while (a[i] < cur) {
      i++;
    }
    while (a[j] > cur) {
      j--;
    }
    if (i >= j) {
      break;
    }
    std::swap(a[i++], a[j--]);
  }

  return j;
}

void Find(int* a, int left, int right, int k) {
  int cur;
  while (left < right) {
    cur = Partition(a, left, right);
    if (cur >= k) {
      right = cur;
    } else {
      left = cur + 1;
    }
  }

  std::cout << a[k] << '\n';
}

int main() {
  int n, k;
  std::cin >> n;
  auto* a = new int[n];
  std::cin >> k >> a[0] >> a[1];

  for (int i = 2; i < n; i++) {
    a[i] = (123 * a[i - 1] + 45 * a[i - 2]) % 10004321;
  }

  Find(a, 0, n - 1, k - 1);
  delete[] a;
  return 0;
}
