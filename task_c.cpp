#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Tree {
 private:
  std::vector<int> arr_;
  int height_ = 0;
  int ans_ = 0;
  int value_ = 0;

 public:
  Tree(std::vector<int>& arr_sup, int n) {
    height_ = 0;
    int size, tmp;
    while (int(pow(2, height_)) < n) {
      ++height_;
    }
    size = 2 * int(pow(2, height_)) - 1;
    arr_.resize(size, 0);
    tmp = int(pow(2, height_)) - 1;
    for (int i = tmp; i < tmp + n; i++) {
      arr_[i] = arr_sup[i - tmp];
    }
    for (int i = height_ - 1; i >= 0; i--) {
      for (int l = int(pow(2, i)) - 1; l < int(pow(2, i + 1)) - 1; l++) {
        arr_[l] = std::max(arr_[2 * l + 1], arr_[2 * l + 2]);
      }
    }
  }

  void Get(int index, int left_find, int right_find, int tl, int tr) {
    if (tl == left_find && tr == right_find) {
      if (arr_[index] >= value_) {
        while (2 * index + 2 < int(arr_.size())) {
          if (arr_[2 * index + 1] >= value_) {
            index = 2 * index + 1;
          } else if (arr_[2 * index + 2] >= value_) {
            index = 2 * index + 2;
          }
        }
        ans_ = std::min(ans_, index);
      }
      return;
    }
    int tm = (tl + tr) / 2;
    if (left_find < tm) {
      Get(2 * index + 1, left_find, std::min(tm, right_find), tl, tm);
    }
    if (right_find > tm) {
      Get(2 * index + 2, std::max(tm, left_find), right_find, tm, tr);
    }
  }

  void Set(int index, int key) {
    arr_[index] = key;
    while (index > 0) {
      index = (index - 1) / 2;
      arr_[index] = std::max(arr_[2 * index + 1], arr_[2 * index + 2]);
    }
  }

  void ReAnsVal(int j) {
    ans_ = int(arr_.size());
    value_ = j;
  }

  int Height() { return height_; }

  int Ans() { return ans_; }

  int Siz() { return int(arr_.size()); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> value(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> value[i];
  }

  Tree tree(value, n);

  int tmp, i, j;
  for (int p = 0; p < m; p++) {
    std::cin >> tmp >> i >> j;
    if (tmp == 0) {
      tree.Set(int(pow(2, tree.Height())) + i - 2, j);
    } else {
      tree.ReAnsVal(j);
      tree.Get(0, i - 1, n, 0, int(pow(2, tree.Height())));
      if (tree.Ans() == int(tree.Siz())) {
        std::cout << "-1" << '\n';
      } else {
        std::cout << tree.Ans() - int(pow(2, tree.Height())) + 2 << '\n';
      }
    }
  }

  return 0;
}
