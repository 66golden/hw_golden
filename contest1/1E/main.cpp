#include <algorithm>
#include <iostream>
#include <string>

void Enqueue(long long*& brain, long long*& queue, int* bfirst, int* qfirst,
             const int* qlast) {
  long long n;
  std::cin >> n;
  brain[(*bfirst)] = n;
  (*bfirst)++;
  std::cout << "ok" << '\n';
  if (*qfirst == 0 || *qfirst - *qlast == 0) {
    queue[(*qfirst)] = n;
    (*qfirst)++;
  } else {
    while (queue[(*qfirst - 1)] > n) {
      queue[(*qfirst - 1)] = 0;
      (*qfirst)--;
    }
    queue[(*qfirst)] = n;
    (*qfirst)++;
  }
}

void Front(long long*& brain, const int* bfirst, const int* blast) {
  if (*bfirst - *blast == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << brain[(*blast)] << '\n';
  }
}

void Dequeue(long long*& brain, long long*& queue, const int* bfirst,
             int* blast, int* qlast) {
  if (*bfirst - *blast == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << brain[(*blast)] << '\n';
    if (queue[(*qlast)] == brain[(*blast)]) {
      queue[(*qlast)] = 0;
      (*qlast)++;
    }
    brain[(*blast)] = 0;
    (*blast)++;
  }
}

void Size(const int* bfirst, const int* blast) {
  std::cout << *bfirst - *blast << '\n';
}

void Clear(long long*& brain, long long*& queue, int* bfirst, int* blast,
           int* qfirst, int* qlast) {
  for (int i = *blast; i < *bfirst; i++) {
    brain[i] = 0;
  }
  for (int i = *qlast; i < *qfirst; i++) {
    queue[i] = 0;
  }
  *bfirst = 0;
  *blast = 0;
  *qfirst = 0;
  *qlast = 0;
  std::cout << "ok" << '\n';
}

void Min(long long*& queue, const int* bfirst, const int* blast,
         const int* qlast) {
  if (*bfirst - *blast == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << queue[(*qlast)] << '\n';
  }
}

int main() {
  int m, bfirst = 0, blast = 0, qfirst = 0, qlast = 0;
  std::string s;
  std::cin >> m;
  auto* brain = new long long[m];
  auto* queue = new long long[m];
  for (int i = 0; i < m; i++) {
    std::cin >> s;
    switch (s[0]) {
      case ('e'):
        Enqueue(brain, queue, &bfirst, &qfirst, &qlast);
        break;
      case ('d'):
        Dequeue(brain, queue, &bfirst, &blast, &qlast);
        break;
      case ('f'):
        Front(brain, &bfirst, &blast);
        break;
      case ('s'):
        Size(&bfirst, &blast);
        break;
      case ('c'):
        Clear(brain, queue, &bfirst, &blast, &qfirst, &qlast);
        break;
      case ('m'):
        Min(queue, &bfirst, &blast, &qlast);
    }
  }
  delete[] brain;
  delete[] queue;
}
