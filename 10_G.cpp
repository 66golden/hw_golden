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
  std::unordered_map<std::string, int> reversed_string_indices;
  std::vector<std::pair<int, int>> result;
  int words_size = static_cast<int>(words.size());

  for (int i = 0; i < words_size; ++i) {
    std::string tmp = words[i];
    reverse(tmp.begin(), tmp.end());
    reversed_string_indices[tmp] = i;
  }

  if (reversed_string_indices.count("") != 0u) {
    for (int i = 0; i < words_size; ++i) {
      if (i != reversed_string_indices[""] &&
          IsPalindrome(words[i], 0, static_cast<int>(words[i].length()) - 1)) {
        result.push_back({reversed_string_indices[""], i});
      }
    }
  }

  for (int i = 0; i < words_size; ++i) {
    for (int j = 0; j < static_cast<int>(words[i].length()); ++j) {
      std::string left = words[i].substr(0, j);
      std::string right = words[i].substr(j);
      if (reversed_string_indices.count(left) != 0u &&
          reversed_string_indices[left] != i &&
          IsPalindrome(right, 0, static_cast<int>(right.length()) - 1)) {
        result.push_back({i, reversed_string_indices[left]});
      }
      if (reversed_string_indices.count(right) != 0u &&
          reversed_string_indices[right] != i &&
          IsPalindrome(left, 0, static_cast<int>(left.length()) - 1)) {
        result.push_back({reversed_string_indices[right], i});
      }
    }
  }

  return result;
}

int main() {
  int num_of_words;
  std::cin >> num_of_words;
  std::vector<std::string> words;
  std::string tmp;
  for (int i = 0; i < num_of_words; ++i) {
    std::cin >> tmp;
    words.push_back(tmp);
  }
  std::vector<std::pair<int, int>> result = FindPalindrome(words);
  std::cout << result.size() << '\n';
  for (const auto& pair : result) {
    std::cout << pair.first + 1 << ' ' << pair.second + 1 << '\n';
  }
}
