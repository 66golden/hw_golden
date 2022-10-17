#include <algorithm>
#include <deque>
#include <iostream>

int main() {
  int n, x;
  char c;
  std::cin >> n;
  std::deque<int> deq1;
  std::deque<int> deq2;
  for (int i = 0; i < n; i++) {
    std::cin >> c;
    if (c == '+') {
      std::cin >> x;
      deq2.push_back(x);
    }
    if (c == '*') {
      std::cin >> x;
      deq2.push_front(x);
    }
    if (c == '-') {
      std::cout << deq1.front() << '\n';
      deq1.pop_front();
    }
    if (deq1.size() != deq2.size()) {
      deq1.push_back(deq2.front());
      deq2.pop_front();
    }
  }
}
