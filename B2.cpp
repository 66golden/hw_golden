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

int Find(int* a, int left, int right, int k) {
  int cur;
  while (left < right) {
    cur = Partition(a, left, right);
    if (cur >= k) {
      right = cur;
    } else {
      left = cur + 1;
    }
  }

  return a[k];
}

int main() {
  const int kX = 123, kY = 45, kZ = 10004321;
  int n, k;
  std::cin >> n;
  auto* a = new int[n];
  std::cin >> k >> a[0] >> a[1];

  for (int i = 2; i < n; i++) {
    a[i] = (kX * a[i - 1] + kY * a[i - 2]) % kZ;
  }

  std::cout << Find(a, 0, n - 1, k - 1) << '\n';
  delete[] a;
  return 0;
}
