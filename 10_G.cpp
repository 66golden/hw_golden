// no_concepts
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

bool IsPalindrome(const std::string& str, int start, int end) {
  while (start < end) {
    if (str[start++] != str[end--]) {
      return false;
    }
  }
  return true;
}

std::vector<std::pair<int, int>> FindPalindrome(
    const std::vector<std::string>& words) {
  std::unordered_map<std::string, int> map;
  std::vector<std::pair<int, int>> result;
  int nn = int(words.size());

  for (int ii = 0; ii < nn; ++ii) {
    std::string tmp = words[ii];
    reverse(tmp.begin(), tmp.end());
    map[tmp] = ii;
  }

  if (map.count("") != 0u) {
    for (int ii = 0; ii < nn; ++ii) {
      if (ii != map[""] &&
          IsPalindrome(words[ii], 0, int(words[ii].length()) - 1)) {
        result.push_back({map[""], ii});
      }
    }
  }

  for (int ii = 0; ii < nn; ++ii) {
    for (int jj = 0; jj < int(words[ii].length()); ++jj) {
      std::string left = words[ii].substr(0, jj);
      std::string right = words[ii].substr(jj);
      if (map.count(left) != 0u && map[left] != ii &&
          IsPalindrome(right, 0, int(right.length()) - 1)) {
        result.push_back({ii, map[left]});
      }
      if (map.count(right) != 0u && map[right] != ii &&
          IsPalindrome(left, 0, int(left.length()) - 1)) {
        result.push_back({map[right], ii});
      }
    }
  }

  return result;
}

int main() {
  int nn;
  std::cin >> nn;
  std::vector<std::string> words;
  std::string tmp;
  for (int ii = 0; ii < nn; ++ii) {
    std::cin >> tmp;
    words.push_back(tmp);
  }
  std::vector<std::pair<int, int>> result = FindPalindrome(words);
  std::cout << result.size() << '\n';
  for (const auto& pair : result) {
    std::cout << pair.first + 1 << ' ' << pair.second + 1 << '\n';
  }
}
