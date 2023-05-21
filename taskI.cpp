#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
    int L_;
    int R_;
    std::vector<std::vector<int>> edges_;
    std::vector<int> unmatched_left_vert_;
    std::vector<std::string> colour_;
    std::vector<int> ans_left_;
    std::vector<int> ans_right_;

    Graph(int L, int R, std::vector<std::vector<int>>& edges_left_to_right, std::vector<int>& max_match) {
        L_ = L;
        R_ = R;
        colour_ = std::vector<std::string>(L + R, "WHITE");
        edges_.reserve(L + R);
        for (int i = 0; i < L; i++) {
            if (max_match[i] != -1) {
                edges_[L + max_match[i]].push_back(i);
            } else {
                unmatched_left_vert_.push_back(i);
            }
        }
        for (int i = 0; i < L; i++) {
            for (int x : edges_left_to_right[i]) {
                if (std::find(edges_[L + x].begin(), edges_[L + x].end(), i) == edges_[L + x].end()) {
                    edges_[i].push_back(L + x);
                }
            }
        }
    }

    void Dfs(int v) {
        colour_[v] = "GREY";
        for(int to : edges_[v]) {
            if (colour_[to] == "WHITE") {
                Dfs(to);
            }
        }
        colour_[v] = "BLACK";
    }

    void Solve() {
        for (int vert : unmatched_left_vert_) {
            Dfs(vert);
        }
        for (int i = 0; i < L_; i++) {
            if (colour_[i] == "WHITE") {
                ans_left_.push_back(i);
            }
        }
        for (int i = L_; i < L_ + R_; i++) {
            if (colour_[i] == "BLACK") {
                ans_right_.push_back(i - L_);
            }
        }
        std::cout << ans_left_.size() + ans_right_.size() << '\n';
        std::cout << ans_left_.size() << ' ';
        for (int x : ans_left_) {
            std::cout << x + 1 << ' ';
        }
        std::cout << '\n';
        std::cout << ans_right_.size() << ' ';
        for (int x : ans_right_) {
            std::cout << x + 1 << ' ';
        }
    }
};

int main() {
    int L, R, n, vert;
    std::cin >> L >> R;
    std::vector<std::vector<int>> edges_left_to_right(L);
    std::vector<int> max_match(L, -1);
    std::vector<std::vector<int>> edges(L + R);
    std::vector<int> unmatched_left_vert;
    for (int i = 0; i < L; i++) {
        std::cin >> n;
        for (int j = 0; j < n; j++) {
            std::cin >> vert;
            edges_left_to_right[i].push_back(vert - 1);
        }
    }
    for (int i = 0; i < L; i++) {
        std::cin >> vert;
        max_match[i] = vert - 1;
    }
    Graph graph{L, R, edges_left_to_right, max_match};
    graph.Solve();
}
