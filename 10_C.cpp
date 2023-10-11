// no_concepts
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

const int kLinkNull = -1;

struct Node {
  std::unordered_map<char, int> next;
  int fail = kLinkNull;
  std::vector<int> output;
};

int BuildTrie(const std::vector<std::string>& words, std::vector<Node>& nodes) {
  nodes.push_back(Node());
  int root = 0;
  for (size_t i = 0; i < words.size(); ++i) {
    const std::string& word = words[i];
    int node = root;
    for (char c : word) {
      if (nodes[node].next.count(c) == 0) {
        nodes.push_back(Node());
        nodes[node].next[c] = nodes.size() - 1;
      }
      node = nodes[node].next[c];
    }
    nodes[node].output.push_back(i);
  }
  std::queue<int> queue;
  for (auto & [ ch, child ] : nodes[root].next) {
    nodes[child].fail = root;
    queue.push(child);
  }
  while (!queue.empty()) {
    int cur = queue.front();
    queue.pop();
    for (auto & [ ch, child ] : nodes[cur].next) {
      int fail = nodes[cur].fail;
      while (fail != kLinkNull && nodes[fail].next.count(ch) == 0) {
        fail = nodes[fail].fail;
      }
      nodes[child].fail = fail != kLinkNull ? nodes[fail].next[ch] : root;
      for (int id : nodes[nodes[child].fail].output) {
        nodes[child].output.push_back(id);
      }
      queue.push(child);
    }
  }
  return root;
}

void SearchWords(int root, const std::string& text,
                 const std::vector<std::string>& words,
                 const std::vector<Node>& nodes, int num) {
  std::vector<std::vector<int>> ans(num);
  int node = root;
  for (int i = 0; i < int(text.size()); ++i) {
    char c = text[i];
    while (node != kLinkNull && nodes[node].next.count(c) == 0) {
      node = nodes[node].fail;
    }
    node = node != kLinkNull
               ? (nodes[node].next.find(c) != nodes[node].next.end()
                      ? nodes[node].next.at(c)
                      : kLinkNull)
               : root;
    for (int id : nodes[node].output) {
      ans[id].push_back(i - words[id].size() + 1);
    }
  }
  for (int i = 0; i < num; ++i) {
    std::cout << ans[i].size() << ' ';
    for (int j : ans[i]) {
      std::cout << j + 1 << ' ';
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
  for (int i = 0; i < num; ++i) {
    std::cin >> words[i];
  }
  int root = BuildTrie(words, nodes);
  SearchWords(root, text, words, nodes, num);
}
