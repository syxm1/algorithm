#include <vector>

template<typename T> struct fenwick {
  // 1-indexed
  size_t sz;
  std::vector<T> fen, arr;

  fenwick(size_t n) {
    this->sz = n + 1;
    fen.assign(sz, 0);
    arr.assign(sz, 0);
  }

  fenwick(std::vector<T> v) : fenwick(v.size()) {
    for (size_t i = 0; i < v.size(); i++) {
      arr[i + 1] = v[i];
      add(i, v[i]);
    }
  }

  void add(size_t i, T x) {
    i++;
    while (i < sz) {
      fen[i] += x;
      i += (i & (-i));
    }
  }

  void update(size_t i, T x) {
    add(i, x - arr[i]);
    arr[i+1] = x;
  }

  T pref(size_t r) {
    r++;
    T ret = 0;
    while (r > 0) {
      ret += fen[r];
      r -= (r & (-r));
    }
    return ret;
  }

  T sum(size_t l, size_t r) {
    return pref(r) - pref(l-1);
  }
};
