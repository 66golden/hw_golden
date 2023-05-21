#include <iostream>
#include <set>
#include <vector>

const int kInf = 1e9;

struct Edge {
  int length;
  int to;

  Edge(int length_old, int vert) {
    length = length_old;
    to = vert;
  }
};

class Graph {
 private:
  std::vector<std::vector<Edge>> edges_;
  std::vector<int> distance_;
  std::vector<bool> used_;

 public:
  Graph(std::vector<std::vector<Edge>>& edges_old, int n) {
    edges_ = std::move(edges_old);
    distance_ = std::vector<int>(n, kInf);
    used_ = std::vector<bool>(n, false);
  }

  void Dijkstra(int start) {
    distance_[start] = 0;
    std::set<std::pair<int, int>> queue;
    queue.insert({0, start});
    while (!queue.empty()) {
      int first_vert = queue.begin()->second;
      queue.erase(queue.begin());
      for (Edge edge : edges_[first_vert]) {
        if (distance_[first_vert] + edge.length < distance_[edge.to]) {
          queue.erase({distance_[edge.to], edge.to});
          distance_[edge.to] = distance_[first_vert] + edge.length;
          queue.insert({distance_[edge.to], edge.to});
        }
      }
    }
    for (auto x : distance_) {
      std::cout << x << " ";
    }
  }

  void Prim() {
    long long mst_weight = 0;
    std::set<std::pair<int, int>> queue;
    queue.insert({0, 0});
    while (!queue.empty()) {
      int first_vert = queue.begin()->second;
      if (used_[first_vert]) {
        queue.erase(queue.begin());
        continue;
      }
      used_[first_vert] = true;
      mst_weight += queue.begin()->first;
      queue.erase(queue.begin());
      for (Edge edge : edges_[first_vert]) {
        if (!used_[edge.to]) {
          queue.insert({edge.length, edge.to});
        }
      }
    }
    std::cout << mst_weight << '\n';
  }
};

int main() {
  int num_of_vert;
  int num_of_edge;
  int first_vert;
  int second_vert;
  int length;
  std::cin >> num_of_vert >> num_of_edge;
  std::vector<std::vector<Edge>> edges(num_of_vert);
  for (int j = 0; j < num_of_edge; j++) {
    std::cin >> first_vert >> second_vert >> length;
    edges[first_vert - 1].push_back(Edge(length, second_vert - 1));
    edges[second_vert - 1].push_back(Edge(length, first_vert - 1));
  }
  Graph graph{edges, num_of_vert};
  graph.Prim();
}
