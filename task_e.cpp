#include <iostream>

long long BinPow(long long value, long long exp, long long mod) {
  long long result = 1;
  if (value == 0) {
    return 0;
  }
  value %= mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = result * value % mod;
    }
    exp >>= 1;
    value = value * value % mod;
  }
  return result;
}

bool IsQuadraticResidue(long long value, long long mod) {
  if (value == 0) {
    return true;
  }
  return BinPow(value, (mod - 1) / 2, mod) == 1;
}

long long SqrtMod(long long value, long long mod) {
  if (value == 0) {
    return 0;
  }
  if (mod == 2) {
    return value;
  }
  if (!IsQuadraticResidue(value, mod)) {
    return -1;
  }
  if (mod % 4 == 3) {
    return BinPow(value, (mod + 1) / 4, mod);
  }
  long long exponent = 0;
  long long odd_part = mod - 1;
  while (odd_part % 2 == 0) {
    odd_part >>= 1;
    ++exponent;
  }
  long long non_residue = 2;
  while (IsQuadraticResidue(non_residue, mod)) {
    ++non_residue;
  }
  long long temp_base = BinPow(non_residue, odd_part, mod);
  long long sqrt_candidate = BinPow(value, (odd_part + 1) / 2, mod);
  long long mod_exp = BinPow(value, odd_part, mod);
  while (mod_exp != 1) {
    long long least_exp = 0;
    long long temp_mod_exp = mod_exp;
    while (temp_mod_exp != 1) {
      temp_mod_exp = (temp_mod_exp * temp_mod_exp) % mod;
      ++least_exp;
    }
    long long base_for_exponentiation = 1;
    if (exponent > least_exp) {
      base_for_exponentiation =
          BinPow(temp_base, 1LL << (exponent - least_exp - 1), mod);
    }
    sqrt_candidate = (sqrt_candidate * base_for_exponentiation) % mod;
    temp_base = (base_for_exponentiation * base_for_exponentiation) % mod;
    mod_exp = (mod_exp * temp_base) % mod;
    exponent = least_exp;
  }
  return sqrt_candidate;
}

int main() {
  int num;
  long long value;
  long long mod;
  std::cin >> num;
  while (num != 0) {
    --num;
    std::cin >> value >> mod;
    long long res = SqrtMod(value, mod);
    if (res == -1) {
      std::cout << "IMPOSSIBLE" << '\n';
    } else {
      std::cout << res << '\n';
    }
  }
}

