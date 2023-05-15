#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int main() {
  std::vector<std::list<long long>> hash_table(1000000);
  int n, value, hash_value;
  char c;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> c >> value;
    hash_value = int(std::hash<long long>{}(value) % 1000000);
    auto find_iter = std::find(hash_table[hash_value].begin(),
                               hash_table[hash_value].end(), value);
    switch (c) {
      case '+':
        if (find_iter == hash_table[hash_value].end()) {
          hash_table[hash_value].insert(hash_table[hash_value].begin(), 1,
                                        value);
        }
        break;
      case '-':
        if (find_iter != hash_table[hash_value].end()) {
          hash_table[hash_value].erase(find_iter);
        }
        break;
      case '?':
        if (find_iter == hash_table[hash_value].end()) {
          std::cout << "NO" << '\n';
        } else {
          std::cout << "YES" << '\n';
        }
        break;
    }
  }
}
