// no_concepts
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

struct Node {
  std::unordered_map<char, int> next;
  int fail = -1;
  std::vector<int> output;
};

int BuildTrie(const std::vector<std::string>& words, std::vector<Node>& nodes) {
  nodes.push_back(Node());
  int root = 0;
  for (int ii = 0; ii < int(words.size()); ++ii) {
    const std::string& word = words[ii];
    int node = root;
    for (char cc : word) {
      if (nodes[node].next.count(cc) == 0) {
        nodes.push_back(Node());
        nodes[node].next[cc] = nodes.size() - 1;
      }
      node = nodes[node].next[cc];
    }
    nodes[node].output.push_back(ii);
  }
  std::queue<int> qq;
  for (auto & [ ch, child ] : nodes[root].next) {
    nodes[child].fail = root;
    qq.push(child);
  }
  while (!qq.empty()) {
    int cur = qq.front();
    qq.pop();
    for (auto & [ ch, child ] : nodes[cur].next) {
      int fail = nodes[cur].fail;
      while (fail != -1 && nodes[fail].next.count(ch) == 0) {
        fail = nodes[fail].fail;
      }
      nodes[child].fail = fail != -1 ? nodes[fail].next[ch] : root;
      for (int id : nodes[nodes[child].fail].output) {
        nodes[child].output.push_back(id);
      }
      qq.push(child);
    }
  }
  return root;
}

void SearchWords(int root, const std::string& text,
                 const std::vector<std::string>& words,
                 const std::vector<Node>& nodes, int num) {
  std::vector<std::vector<int>> ans(num);
  int node = root;
  for (int ii = 0; ii < int(text.size()); ++ii) {
    char cc = text[ii];
    while (node != -1 && nodes[node].next.count(cc) == 0) {
      node = nodes[node].fail;
    }
    node = node != -1 ? (nodes[node].next.find(cc) != nodes[node].next.end()
                             ? nodes[node].next.at(cc)
                             : -1)
                      : root;
    for (int id : nodes[node].output) {
      ans[id].push_back(ii - words[id].size() + 1);
    }
  }
  for (int ii = 0; ii < num; ++ii) {
    std::cout << ans[ii].size() << ' ';
    for (int jj : ans[ii]) {
      std::cout << jj + 1 << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::string text;
  int num;
  std::cin >> text;
  std::cin >> num;
  std::vector<std::string> words(num);
  std::vector<Node> nodes;
  for (int ii = 0; ii < num; ++ii) {
    std::cin >> words[ii];
  }
  int root = BuildTrie(words, nodes);
  SearchWords(root, text, words, nodes, num);
}
