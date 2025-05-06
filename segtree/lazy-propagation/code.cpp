#include <vector>

template <typename T> struct segtree {
  int n;
  std::vector<T> arr, tree, lazy;

  T identity = 0;

  T combine(T a, T b) { return a + b; }

  segtree(int _n) {
    this->n = _n;
    this->arr.assign(_n, identity);
    this->tree.assign(4 * _n + 20, identity);
    this->lazy.resize(2 * _n + 20, identity);
  }

  void propagate(int v, int tl, int tr) {
    tree[v] += lazy[v] * (tr - tl + 1);
    if (tl != tr)
      lazy[2 * v + 1] += lazy[v], lazy[2 * v + 2] += lazy[v];
    else
      arr[tl] = tree[v];
    lazy[v] = 0;
  }

  void build(int v, int tl, int tr) {
    if (tl == tr) {
      tree[v] = arr[tl];
      return;
    }
    int tm = (tl + tr) >> 1;
    build(2 * v + 1, tl, tm);
    build(2 * v + 2, tm + 1, tr);
    tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
  }

  void update(int v, int tl, int tr, int l, int r, T val) {
    if (l <= tl && tr <= r) {
      lazy[v] += val;
      propagate(v, tl, tr);
      return;
    }
    if (tr < l || r < tl) {
      return;
    }
    int tm = (tl + tr) >> 1;
    update(2 * v + 1, tl, tm, l, r, val);
    update(2 * v + 2, tm + 1, tr, l, r, val);
    tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
  }

  T get(int v, int tl, int tr, int l, int r) {
    if (l <= tl && tr <= r) {
      propagate(v, tl, tr);
      return tree[v];
    }
    if (tr < l || r < tl) {
      return identity;
    }
    int tm = (tl + tr) >> 1;
    T lf = get(2 * v + 1, tl, tm, l, r);
    T rg = get(2 * v + 2, tm + 1, tr, l, r);
    return combine(lf, rg);
  }

  void build() { build(0, 0, n - 1); }

  void update(int l, int r, T val) { update(0, 0, n - 1, l, r, val); }

  void update(int id, T val) { update(id, id, val); }

  T get(int l, int r) { return get(0, 0, n - 1, l, r); }

  T get(int id) { return get(id, id); }
};
