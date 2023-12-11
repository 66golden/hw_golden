#include <algorithm>
#include <iostream>
#include <unordered_map>

const int kSqrtOfMax = 65536;

long long BinPow(long long base, long long exp, long long mod) {
  long long result = 1;
  if (base == 0) {
    return 0;
  }
  base %= mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * base % mod;
    }
    exp >>= 1;
    base = base * base % mod;
  }
  return result;
}

int GetOrd(long long base, long long mod) {
  int divisor = 1;
  bool found = false;
  for (; divisor * divisor < mod; ++divisor) {
    if ((mod - 1) % divisor == 0) {
      if (BinPow(base, divisor, mod) == 1) {
        found = true;
        break;
      }
    }
  }
  if (found) {
    return divisor;
  }
  for (int k = divisor - 1; k >= 1; --k) {
    if ((mod - 1) % k == 0) {
      if (BinPow(base, (mod - 1) / k, mod) == 1) {
        return (mod - 1) / k;
      }
    }
  }
  return -1;
}

void FindDiscreteLogarithm(long long mod, long long base, long long value) {
  std::unordered_map<int, int> sqr_map;
  long long step = BinPow(base, kSqrtOfMax, mod);
  long long accum = 1;
  int iter = 0;
  do {
    sqr_map[accum] = iter;
    accum = (accum * step) % mod;
    iter += kSqrtOfMax;
  } while (iter < mod - 1);
  long long inverse_base = BinPow(base, mod - 2, mod);
  iter = 0;
  while (iter < kSqrtOfMax) {
    auto itr = sqr_map.find(value);
    if (itr != sqr_map.end()) {
      std::cout << (itr->second + iter) % GetOrd(base, mod) << '\n';
      return;
    }
    value = (value * inverse_base) % mod;
    ++iter;
  }
  std::cout << "no solution" << '\n';
}

int main() {
  long long mod;
  long long base;
  long long value;
  while (std::cin >> mod >> base >> value) {
    if (mod == 1) {
      std::cout << "0" << '\n';
    } else {
      FindDiscreteLogarithm(mod, base, value);
    }
  }
}
