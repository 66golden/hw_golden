#include <iostream>
#include <string>
#include <vector>

std::vector<int> PrefFunc(const std::string& ss) {
  int nn = int(ss.size());
  std::vector<int> strings(nn);
  int jj = 0;
  for (int ii = 1; ii < nn; ++ii) {
    while (jj > 0 && ss[jj] != ss[ii]) {
      jj = strings[jj - 1];
    }
    if (ss[jj] == ss[ii]) {
      ++jj;
    }
    strings[ii] = jj;
  }
  return strings;
}

int main() {
  std::string ss;
  int ans = 0;
  std::cin >> ss;
  for (size_t i = 0; i < ss.size(); ++i) {
    std::string help = ss.substr(i);
    std::vector<int> pref_f = PrefFunc(help);
    int len = 1;
    for (auto x : pref_f) {
      int hh = len / (len - x);
      ans = std::max(ans, hh);
      len++;
    }
  }
  std::cout << ans;
}
