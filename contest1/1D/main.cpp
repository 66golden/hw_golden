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
    switch (c) {
      case '+':
        std::cin >> x;
        deq2.push_back(x);
        break;
      case '*':
        std::cin >> x;
        deq2.push_front(x);
        break;
      case '-':
        std::cout << deq1.front() << '\n';
        deq1.pop_front();
        break;
    }
    if (deq1.size() != deq2.size()) {
      deq1.push_back(deq2.front());
      deq2.pop_front();
    }
  }
}
