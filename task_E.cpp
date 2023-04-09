#include <iostream>
#include <vector>

const int kInt = 100000;

struct Edge {
  int from;
  int to;
  int length;

  Edge(int from_old, int to_old, int length_old) {
    from = from_old;
    to = to_old;
    length = length_old;
  }
};

class Graph {
 private:
  int num_of_vert_;
  std::vector<Edge> list_of_edge_;
  std::vector<long long> dist_;
  std::vector<int> parents_;

 public:
  Graph(std::vector<Edge>& list_of_edge_old, int n) {
    num_of_vert_ = n;
    list_of_edge_ = std::move(list_of_edge_old);
    dist_ = std::vector<long long>(n, kInt);
    dist_[0] = 0;
    parents_ = std::vector<int>(n, -1);
  }

  void FordBellman() {
    int vert = -1;
    for (int i = 0; i < num_of_vert_; i++) {
      vert = -1;
      for (auto& edge : list_of_edge_) {
        if (dist_[edge.to] > dist_[edge.from] + edge.length) {
          dist_[edge.to] = dist_[edge.from] + edge.length;
          vert = edge.to;
          parents_[edge.to] = edge.from;
        }
      }
    }
    if (vert == -1) {
      std::cout << "NO" << '\n';
    } else {
      for (int i = 0; i < num_of_vert_; i++) {
        vert = parents_[vert];
      }
      std::vector<int> path;
      int cur = vert;
      while (cur != vert || int(path.size()) <= 1) {
        path.push_back(cur);
        cur = parents_[cur];
      }
      path.push_back(cur);
      std::reverse(path.begin(), path.end());
      std::cout << "YES" << '\n' << path.size() << '\n';
      for (int x : path) {
        std::cout << x + 1 << ' ';
      }
    }
  }
};

int main() {
  int num_of_vert;
  int length;
  std::vector<Edge> list_of_edge;
  std::cin >> num_of_vert;
  for (int i = 0; i < num_of_vert; i++) {
    for (int j = 0; j < num_of_vert; j++) {
      std::cin >> length;
      if (length < kInt) {
        list_of_edge.push_back(Edge(i, j, length));
      }
    }
  }
  Graph graph{list_of_edge, num_of_vert};
  graph.FordBellman();
}
