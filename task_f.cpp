#include <complex>
#include <iostream>
#include <vector>

const double kPi = acos(-1);

void FFT(std::vector<std::complex<double>>& coeffs, bool is_inverse) {
  int num_points = static_cast<int>(coeffs.size());
  if (num_points == 1) {
    return;
  }
  std::vector<std::complex<double>> even_coeffs(num_points / 2);
  std::vector<std::complex<double>> odd_coeffs(num_points / 2);
  for (int i = 0; 2 * i < num_points; i++) {
    even_coeffs[i] = coeffs[2 * i];
    odd_coeffs[i] = coeffs[2 * i + 1];
  }
  FFT(even_coeffs, is_inverse);
  FFT(odd_coeffs, is_inverse);
  double ang = 2 * kPi / num_points * (is_inverse ? -1 : 1);
  std::complex<double> twiddle_factor(1);
  std::complex<double> twiddle_base(cos(ang), sin(ang));
  for (int i = 0; 2 * i < num_points; i++) {
    coeffs[i] = even_coeffs[i] + twiddle_factor * odd_coeffs[i];
    coeffs[i + num_points / 2] =
        even_coeffs[i] - twiddle_factor * odd_coeffs[i];
    if (is_inverse) {
      coeffs[i] /= 2;
      coeffs[i + num_points / 2] /= 2;
    }
    twiddle_factor *= twiddle_base;
  }
}

void MultiplyPoly(std::vector<int>& poly_first, std::vector<int>& poly_second,
                  std::vector<int>& poly_res) {
  std::vector<std::complex<double>> first_coeffs_complex(poly_first.begin(),
                                                         poly_first.end());
  std::vector<std::complex<double>> second_coeffs_complex(poly_second.begin(),
                                                          poly_second.end());
  int nearest_power_of_two = 1;
  while (nearest_power_of_two <
         static_cast<int>(poly_first.size() + poly_second.size())) {
    nearest_power_of_two <<= 1;
  }
  first_coeffs_complex.resize(nearest_power_of_two);
  second_coeffs_complex.resize(nearest_power_of_two);
  FFT(first_coeffs_complex, false);
  FFT(second_coeffs_complex, false);
  for (int i = 0; i < nearest_power_of_two; i++) {
    first_coeffs_complex[i] *= second_coeffs_complex[i];
  }
  FFT(first_coeffs_complex, true);
  poly_res.resize(nearest_power_of_two);
  for (int i = 0; i < nearest_power_of_two; i++) {
    poly_res[i] = static_cast<int>(round(first_coeffs_complex[i].real()));
  }
}

int main() {
  int deg_first;
  int deg_second;
  std::cin >> deg_first;
  std::vector<int> poly_first(deg_first + 1);
  for (int i = 0; i <= deg_first; ++i) {
    std::cin >> poly_first[i];
  }
  std::cin >> deg_second;
  std::vector<int> poly_second(deg_second + 1);
  for (int i = 0; i <= deg_second; ++i) {
    std::cin >> poly_second[i];
  }
  std::vector<int> poly_res;
  MultiplyPoly(poly_first, poly_second, poly_res);
  std::cout << deg_first + deg_second << ' ';
  for (int i = 0; i <= deg_first + deg_second; ++i) {
    std::cout << poly_res[i] << ' ';
  }
}

