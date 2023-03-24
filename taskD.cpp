#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
  int num_of_vert = 0, counter = 0;
  std::vector<std::vector<int>> list_of_edge;
  std::vector<std::string> colour;
  std::vector<int> parent;
  std::vector<std::pair<int, int>> tin, tout;
  std::vector<int> ans;
  int timer = 0;
  bool is_dag = true;  //граф ациклический

  Graph(std::vector<std::vector<int>>& list_of_edge_old, int n) {
    num_of_vert = n;
    list_of_edge = std::move(list_of_edge_old);
    colour = std::vector<std::string>(n, "WHITE");
    parent = std::vector<int>(n);
    tin = std::vector<std::pair<int, int>>(n);
    tout = std::vector<std::pair<int, int>>(n);
    ans = std::vector<int>(n, 0);
  }

  void CheckIsDag(int v, int p = -1) {
    if (!is_dag) {
      return;
    }
    parent[v] = p;
    colour[v] = "GREY";
    for (int to : list_of_edge[v]) {
      if (!is_dag) {
        return;
      }
      if (colour[to] == "GREY") {
        is_dag = false;
      } else if (colour[to] == "WHITE") {
        CheckIsDag(to, v);
      }
    }
    colour[v] = "BLACK";
  }

  void Dfs(int v, int p = -1) {
    tin[v] = std::make_pair(timer++, v);
    parent[v] = p;
    colour[v] = "GREY";
    for (int to : list_of_edge[v]) {
      if (colour[to] == "WHITE") {
        Dfs(to, v);
      }
    }
    tout[v] = std::make_pair(timer++, v);
    colour[v] = "BLACK";
    ans[v] = counter;
  }

  void Reset() {
    timer = 0;
    tin = std::vector<std::pair<int, int>>(num_of_vert);
    tout = std::vector<std::pair<int, int>>(num_of_vert);
    colour = std::vector<std::string>(num_of_vert, "WHITE");
    parent = std::vector<int>(num_of_vert);
  }
};

int main() {
  int n, m, from, to;
  std::cin >> n >> m;
  std::vector<std::vector<int>> list_of_edge(n);
  std::vector<std::vector<int>> list_of_edge_reverse(n);
  for (int i = 0; i < m; i++) {
    std::cin >> from >> to;
    list_of_edge[from - 1].push_back(to - 1);
    list_of_edge_reverse[to - 1].push_back(from - 1);
  }
  Graph g(list_of_edge, n);
  Graph g_reverse(list_of_edge_reverse, n);
  for (int i = 0; i < n; i++) {
    if (g.colour[i] == "WHITE") {
      g.CheckIsDag(i);
      if (!g.is_dag) {
        break;
      }
    }
  }
  g.Reset();
  for (int i = 0; i < n; i++) {
    if (g.colour[i] == "WHITE") {
      g.Dfs(i);
    }
  }
  std::sort(g.tout.begin(), g.tout.end());
  std::vector<int> p(n);
  for (int i = n - 1; i >= 0; i--) {
    p[n - i - 1] = g.tout[i].second;
  }
  std::vector<int> ans(n, 0);
  for (int i : p) {
    if (g_reverse.colour[i] == "WHITE") {
      g_reverse.counter++;
      g_reverse.Dfs(i);
    }
  }
  std::cout << g_reverse.counter << '\n';
  for (int x : g_reverse.ans) {
    std::cout << x << ' ';
  }
}
