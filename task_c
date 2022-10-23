#include <iostream>
#include <string>
#include <vector>

void SiftUp(std::vector<std::pair<int, long long>>& heap, int index) {
  int parent = (index - 1) / 2;
  while (index > 0 && heap[index].second < heap[parent].second) {
    std::swap(heap[index], heap[parent]);
    index = parent;
    parent = (index - 1) / 2;
  }
}

void SiftDown(std::vector<std::pair<int, long long>>& heap, int index) {
  int size = int(heap.size()), left_child, right_child;
  int parent = index, min_index = index;
  while (2 * parent + 1 < size) {
    left_child = 2 * parent + 1;
    right_child = 2 * parent + 2;
    if (heap[left_child].second < heap[parent].second) {
      min_index = left_child;
    }
    if (right_child < size &&
        heap[right_child].second < heap[left_child].second &&
        heap[right_child].second < heap[parent].second) {
      min_index = right_child;
    }
    if (min_index == parent) {
      break;
    }
    std::swap(heap[parent], heap[min_index]);
    parent = min_index;
  }
}

void Insert(std::vector<std::pair<int, long long>>& heap, int& counter) {
  counter++;
  long long x;
  std::cin >> x;
  heap.push_back(std::make_pair(counter, x));
  SiftUp(heap, int(heap.size()) - 1);
}

void GetMin(std::vector<std::pair<int, long long>>& heap, int& counter) {
  counter++;
  std::cout << heap[0].second << '\n';
}

void ExtractMin(std::vector<std::pair<int, long long>>& heap, int& counter) {
  counter++;
  std::swap(heap[0], heap[heap.size() - 1]);
  heap.pop_back();
  SiftDown(heap, 0);
}

void DecreaseKey(std::vector<std::pair<int, long long>>& heap, int& counter) {
  counter++;
  long long dif, req;
  std::cin >> req >> dif;
  for (int k = 0; k < int(heap.size()); k++) {
    if (heap[k].first == req) {
      heap[k].second -= dif;
      SiftUp(heap, k);
      break;
    }
  }
}

void Solve(std::vector<std::pair<int, long long>>& heap, int q, int& counter) {
  std::string s;
  for (int i = 0; i < q; i++) {
    std::cin >> s;
    switch (s[0]) {
      case ('i'):
        Insert(heap, counter);
        break;
      case ('g'):
        GetMin(heap, counter);
        break;
      case ('e'):
        ExtractMin(heap, counter);
        break;
      case ('d'):
        DecreaseKey(heap, counter);
        break;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q, counter = 0;
  std::cin >> q;
  std::vector<std::pair<int, long long>> heap;
  Solve(heap, q, counter);

  return 0;
}
