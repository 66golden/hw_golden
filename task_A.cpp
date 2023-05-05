#include <iostream>
#include <set>
#include <vector>

const int kInf = 2009000999;

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

 public:
  Graph(std::vector<std::vector<Edge>>& edges_old, int n) {
    edges_ = std::move(edges_old);
    distance_ = std::vector<int>(n, kInf);
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
};

int main() {
  int num_of_graphs;
  int num_of_vert;
  int num_of_edge;
  int start;
  int first_vert;
  int second_vert;
  int length;
  std::cin >> num_of_graphs;
  for (int i = 0; i < num_of_graphs; ++i) {
    std::cin >> num_of_vert >> num_of_edge;
    std::vector<std::vector<Edge>> edges(num_of_vert);
    for (int j = 0; j < num_of_edge; j++) {
      std::cin >> first_vert >> second_vert >> length;
      edges[first_vert].push_back(Edge(length, second_vert));
      edges[second_vert].push_back(Edge(length, first_vert));
    }
    Graph graph{edges, num_of_vert};
    std::cin >> start;
    graph.Dijkstra(start);
    std::cout << '\n';
  }
}
