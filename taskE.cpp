#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Edge {
  int to;
  int index;
};

struct Graph {
  int num_of_vert = 0;
  std::vector<std::vector<Edge>> list_of_edge;
  std::vector<bool> used;
  std::vector<int> parent;
  std::vector<int> tin;
  std::vector<int> ret;
  std::set<int> bridges;
  int timer = 0;
  bool check = false;

  Graph(std::vector<std::vector<Edge>>& list_of_edge_old, int n) {
    num_of_vert = n;
    list_of_edge = std::move(list_of_edge_old);
    used = std::vector<bool>(n, false);
    parent = std::vector<int>(n);
    tin = std::vector<int>(n);
    ret = std::vector<int>(n);
  }

  void Dfs(int v, int p = -1) {
    tin[v] = timer++;
    parent[v] = p;
    ret[v] = tin[v];
    used[v] = true;
    for (Edge edge : list_of_edge[v]) {
      if (edge.to != parent[v]) {
        if (used[edge.to]) {
          ret[v] = std::min(ret[v], tin[edge.to]);
        } else {
          Dfs(edge.to, v);
          ret[v] = std::min(ret[v], ret[edge.to]);
        }
        if (ret[edge.to] > tin[v]) {
          check = false;
          for (auto other: list_of_edge[v]) {
            if (!check && other.to == edge.to) {
              check = true;
            } else if (check && other.to == edge.to) {
              check = false;
              break;
            }
          }
          if (check) {
            bridges.insert(edge.index);
          }
        }
      }
    }
  }

  void FindBridges() {
    for (int i = 0; i < num_of_vert; ++i) {
      if (!used[i]) {
        Dfs(i);
      }
    }
  }
};

int main() {
  int n, m, from, to;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> list_of_edge(n);
  for (int i = 0; i < m; i++) {
    std::cin >> from >> to;
    list_of_edge[from - 1].push_back({to - 1, i});
    list_of_edge[to - 1].push_back({from - 1, i});
  }
  Graph g(list_of_edge, n);
  g.FindBridges();
  std::cout << g.bridges.size() << '\n';
  for (auto x : g.bridges) {
    std::cout << x + 1 << '\n';
  }
}
