#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> CreateSuffixArray(std::string& str) {
  int str_length = static_cast<int>(str.length());
  std::vector<int> suffix_array(str_length);
  std::vector<int> equivalence_classes(str_length);
  std::vector<std::pair<char, int>> sorted_symbols(str_length);
  for (int i = 0; i < str_length; i++) {
    sorted_symbols[i] = {str[i], i};
  }
  sort(sorted_symbols.begin(), sorted_symbols.end());
  for (int i = 0; i < str_length; i++) {
    suffix_array[i] = sorted_symbols[i].second;
  }
  equivalence_classes[suffix_array[0]] = 0;
  for (int i = 1; i < str_length; i++) {
    equivalence_classes[suffix_array[i]] =
        equivalence_classes[suffix_array[i - 1]] +
        static_cast<int>(sorted_symbols[i].first !=
                         sorted_symbols[i - 1].first);
  }
  int iter = 0;
  while ((1 << iter) < str_length) {
    std::vector<std::pair<std::pair<int, int>, int>> tuples(str_length);
    for (int i = 0; i < str_length; i++) {
      tuples[i] = {{equivalence_classes[i],
                    equivalence_classes[(i + (1 << iter)) % str_length]},
                   i};
    }
    sort(tuples.begin(), tuples.end());
    for (int i = 0; i < str_length; i++) {
      suffix_array[i] = tuples[i].second;
    }
    equivalence_classes[suffix_array[0]] = 0;
    for (int i = 1; i < str_length; i++) {
      equivalence_classes[suffix_array[i]] =
          equivalence_classes[suffix_array[i - 1]] +
          static_cast<int>(tuples[i].first != tuples[i - 1].first);
    }
    iter++;
  }
  return suffix_array;
}

void SuffixArrayPrint(std::vector<int>& suffix_array, std::string& str) {
  std::string result;
  for (int pos : suffix_array) {
    if (pos != 0) {
      result += str[pos - 1];
    } else {
      result += str[str.size() - 1];
    }
  }
  std::cout << result;
}

int main() {
  std::string str;
  std::cin >> str;
  std::vector<int> suffix_array = CreateSuffixArray(str);
  SuffixArrayPrint(suffix_array, str);
}
