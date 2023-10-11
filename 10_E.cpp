// no_concepts
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const int kNodeNull = -1;
const int kNodeSize = 10;

class Trie {
 private:
  struct Node {
    std::vector<int> to;
    bool term;
    int height;
    int subtree_term = 0;

    Node(int x = 0) : to(kNodeSize, kNodeNull), term(false), height(x) {}
  };

  std::vector<Node> trie_;
  std::vector<bool> visited_;
  std::unordered_map<int, int> ans_by_heights_;

 public:
  Trie() = default;

  void AddWord(const std::string& str) {
    if (trie_.empty()) {
      trie_.emplace_back();
    }
    int cur_vert = 0;
    int cur_height = 0;
    for (char c : str) {
      if (trie_[cur_vert].to[c - '0'] == kNodeNull) {
        trie_[cur_vert].to[c - '0'] = static_cast<int>(trie_.size());
        trie_.emplace_back(cur_height + 1);
      }
      cur_vert = trie_[cur_vert].to[c - '0'];
      ++cur_height;
    }
    trie_[cur_vert].term = true;
  }

  void Dfs(int cur_vert, int max_height, int fake_size) {
    visited_[cur_vert] = true;
    if (trie_[cur_vert].term) {
      ++trie_[cur_vert].subtree_term;
    }
    for (int i = 0; i < kNodeSize; i++) {
      int next_vert = trie_[cur_vert].to[i];
      if (next_vert != kNodeNull) {
        if (!visited_[next_vert]) {
          Dfs(next_vert, max_height, fake_size);
        }
        trie_[cur_vert].subtree_term += trie_[next_vert].subtree_term;
      }
    }
    if (trie_[cur_vert].subtree_term >= fake_size) {
      ++ans_by_heights_[trie_[cur_vert].height];
    }
  }

  void Solve(const std::vector<int>& request_array, int max_height,
             int fake_size) {
    visited_.assign(trie_.size(), false);
    Dfs(0, max_height, fake_size);
    for (int height : request_array) {
      std::cout << ans_by_heights_[height] << '\n';
    }
  }
};

std::string MakeGood(
    const std::string&
        str) {  //функция, которая строку a_1 a_2 ... a_n переводит в строку a_1
                //a_n a_2 a_{n-1} ... a_n a_1, длины вдвое большей, чем у
                //изначальной строки
  std::string ans;
  int len = static_cast<int>(str.length());
  ans.reserve(len * 2);
  for (int i = 0; i < len; i++) {
    ans += str[i];
    ans += str[len - i - 1];
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int num_of_people, fake_size, num_of_requests, num_of_identical_letters;
  std::cin >> num_of_people >> fake_size;
  std::vector<std::string> words;

  std::string tmp;
  for (int i = 0; i < num_of_people; ++i) {
    std::cin >> tmp;
    words.push_back(MakeGood(tmp));
  }

  Trie trie;
  for (const auto& word : words) {
    trie.AddWord(word);
  }

  std::cin >> num_of_requests;
  std::vector<int> request_array(num_of_requests);
  int max_num_of_identical_letters = 0;
  for (int i = 0; i < num_of_requests; ++i) {
    std::cin >> num_of_identical_letters;
    request_array[i] = num_of_identical_letters * 2;
    max_num_of_identical_letters =
        std::max(max_num_of_identical_letters, request_array[i]);
  }
  trie.Solve(request_array, max_num_of_identical_letters, fake_size);
}
