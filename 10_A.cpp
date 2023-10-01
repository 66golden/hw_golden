#include <iostream>
#include <string>
#include <vector>

size_t PrefFuncLast(const std::string& ss) {
  int nn = ss.size();
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
  return strings.back();
}

int main() {
  int nn;
  std::string help;
  std::string help_2;
  std::string ans;
  std::cin >> nn;
  std::cin >> ans;
  for (int ii = 1; ii < nn; ++ii) {
    std::cin >> help;
    help_2 = ans.substr(std::max(int(ans.size() - help.size()), 0));
    std::string ss = help + "!" + help_2;
    size_t ll = PrefFuncLast(ss);
    ans += help.substr(ll);
  }
  std::cout << ans << '\n';
}
