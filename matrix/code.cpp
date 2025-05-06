#include <cassert>
#include <iostream>
#include <vector>

template <typename T> struct matrix {
  // const int mod = 1e9+7;
  std::vector<std::vector<T>> M;

  matrix<T>(const int n, const int m) {
    assert(n != 0 && m != 0);
    M.assign(n, std::vector<T>(m, 0));
  }

  matrix<T>(const std::vector<std::vector<T>> &A) {
    assert(A.size() != 0 && A[0].size() != 0);
    M = A;
  }

  matrix<T>(const std::vector<std::vector<T>> &&A) {
    assert(A.size() != 0 && A[0].size() != 0);
    M = std::move(A);
  }

  matrix<T> identity(int n) {
    matrix<T> A;
    A.M.assign(n, std::vector<T>(n, 0));
    for (int i = 0; i < n; i++) {
      A.M[i][i] = 1;
    }
    return A;
  }

  matrix<T> operator+(const matrix<T> &mat) {
    const std::vector<std::vector<T>> &N = mat.M;
    assert(M.size() == N.size() && M[0].size() == N[0].size());
    matrix<T> ret(M.size(), M[0].size());
    for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < M[0].size(); j++) {
        ret.M[i][j] = M[i][j] + N[i][j];
      }
    }
    return ret;
  }

  matrix<T> operator-(const matrix<T> &mat) {
    const std::vector<std::vector<T>> &N = mat.M;
    assert(M.size() == N.size() && M[0].size() == N[0].size());
    matrix<T> ret(M.size(), M[0].size());
    for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < M[0].size(); j++) {
        ret.M[i][j] = M[i][j] - N[i][j];
      }
    }
    return ret;
  }

  matrix<T> operator*(const int x) {
    matrix<T> ret(M.size(), M[0].size());
    for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < M[0].size(); j++) {
        ret.M[i][j] = M[i][j] * x;
      }
    }
    return ret;
  }

  matrix<T> operator*(const matrix<T> &mat) {
    const std::vector<std::vector<T>> &N = mat.M;
    assert(M[0].size() == N.size());
    matrix<T> ret(M.size(), N[0].size());
    for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < N[0].size(); j++) {
        for (int k = 0; k < M[0].size(); k++) {
          ret.M[i][j] += M[i][k] * N[k][j];
          // ret %= mod;
        }
      }
    }
    return ret;
  }

  matrix<T> pow(int x) {
    assert(M.size() == M[0].size());
    assert(x >= 0);
    matrix<T> ret = identity(M.size());
    matrix<T> tmp = *this;
    while (x) {
      if (x & 1)
        ret = ret * tmp;
      tmp = tmp * tmp;
      x >>= 1;
    }
    return ret;
  }

  T cofactor(int x, int y) {
    T sign = (x + y) % 2 == 1 ? -1 : 1;
    matrix<T> mat;
    for (int i = 0; i < M.size(); i++) {
      if (i == x)
        continue;
      mat.M.push_back({});
      for (int j = 0; j < M[0].size(); j++) {
        if (j == y)
          continue;
        mat.M.back().push_back(M[i][j]);
      }
    }
    return mat.determinant() * sign;
  }

  T determinant() {
    assert(M.size() == M[0].size());
    if (M.size() == 1) {
      return M[0][0];
    }
    if (M.size() == 2) {
      return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    }
    int ret = 0;
    for (int j = 0; j < M[0].size(); j++) {
      ret += M[0][j] * cofactor(0, j);
    }
    return ret;
  }

  // double data type requiered
  matrix<T> inverse() {
    assert(M.size() == M[0].size());
    matrix<T> ret(M.size(), M[0].size());
    const T det = determinant();
    for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < M[0].size(); j++) {
        ret[i][j] = cofactor(j, i) / det;
      }
    }
    return ret;
  }

  void print() {
    for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < M[0].size(); j++) {
        std::cout << M[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }
};
