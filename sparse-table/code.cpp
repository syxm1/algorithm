#include <vector>

const int mxN = 1e5+5;
std::vector<int> lg(mxN);

void get_log() {
  lg[1] = 0;
  for (int i = 2; i < mxN; i++) {
    lg[i] = lg[i/2] + 1;
  }
}

template<typename T> struct sparse {
  const size_t B = 20; // bit
  size_t n;
  std::vector<std::vector<T>> table;

  sparse(size_t sz) {
    this->n = sz;
  }

  sparse(std::vector<T> v) {
    this->n = v.size();
    table.assign(B, std::vector<T>(n));
    for (size_t i = 0; i < v.size(); i++) {
      table[0][i] = v[i];
    }
    compute();
  }

  void compute() {
    for (size_t i = 1; i < B; i++) {
      for (size_t j = 0; j + (1 << i) <= n; j++) {
        table[i][j] = min(table[i-1][j], table[i-1][j+(1<<(i-1))]);
      }
    }
  }

  T que(size_t l, size_t r) {
    int i = lg[r - l + 1];
    return min(table[i][l], table[i][r-(1<<i)+1]);
  }
};
