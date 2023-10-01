// no_concepts
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  std::vector<int> arr;
  bool term;
  int height;
  int subtree_term = 0;

  Node(int x = 0) : arr(10, -1), term(false), height(x) {}
};

class Trie {
 private:
  std::vector<Node> trie_;
  std::vector<bool> visited_;
  std::unordered_map<int, int> um_;

 public:
  Trie() = default;

  void AddWord(const std::string& str) {
    if (trie_.empty()) {
      trie_.emplace_back();
    }
    int cur_vert = 0;
    int cur_height = 0;
    for (char ii : str) {
      if (trie_[cur_vert].arr[ii - '0'] == -1) {
        trie_[cur_vert].arr[ii - '0'] = int(trie_.size());
        trie_.emplace_back(cur_height + 1);
      }
      cur_vert = trie_[cur_vert].arr[ii - '0'];
      ++cur_height;
    }
    trie_[cur_vert].term = true;
  }

  void Dfs(int cur_vert, int max_height, int kk) {
    visited_[cur_vert] = true;
    if (trie_[cur_vert].term) {
      trie_[cur_vert].subtree_term += 1;
    }
    for (int ii = 0; ii < 10; ii++) {
      int next_vert = trie_[cur_vert].arr[ii];
      if (next_vert != -1) {
        if (!visited_[next_vert]) {
          Dfs(next_vert, max_height, kk);
        }
        trie_[cur_vert].subtree_term += trie_[next_vert].subtree_term;
      }
    }
    if (trie_[cur_vert].subtree_term >= kk) {
      um_[trie_[cur_vert].height] += 1;
    }
  }

  void Solve(const std::vector<int>& arr_ll, int max_height, int kk) {
    visited_.assign(trie_.size(), false);
    Dfs(0, max_height, kk);
    for (int height : arr_ll) {
      std::cout << um_[height] << '\n';
    }
  }
};

std::string MakeGood(const std::string& str) {
  std::string ans;
  int nn = int(str.length());
  ans.reserve(nn * 2);
  for (int ii = 0; ii < nn; ii++) {
    ans += str[ii];
    ans += str[nn - ii - 1];
  }
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int nn, kk, qq, ll;
  std::cin >> nn >> kk;
  std::vector<std::string> arr;

  std::string tmp;
  for (int ii = 0; ii < nn; ++ii) {
    std::cin >> tmp;
    arr.push_back(MakeGood(tmp));
  }

  Trie trie;
  for (const auto& word : arr) {
    trie.AddWord(word);
  }

  std::cin >> qq;
  std::vector<int> arr_ll(qq);
  int max_l = 0;
  for (int ii = 0; ii < qq; ++ii) {
    std::cin >> ll;
    arr_ll[ii] = ll * 2;
    max_l = std::max(max_l, arr_ll[ii]);
  }
  trie.Solve(arr_ll, max_l, kk);
}
